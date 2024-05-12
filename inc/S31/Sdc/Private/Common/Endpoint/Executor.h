#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/Endpoint/EndpointUrl.h>
#include <S31/Sdc/Private/Common/Endpoint/ResettableUrlList.h>
#include <S31/Sdc/Private/Common/Endpoint/UrlList.h>
#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Utils/Public/Outcome.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/UriIo.h>

#include <memory>
#include <string>
#include <utility>

namespace S31::Sdc::Impl::Endpoint
{

/**
 * @brief Callback function definition to create outgoing blocking HTTP jobs of a certain type.
 * @details Accepts first a URL, the one that is intended to be used by the endpoint to send
 *          a request to. The second argument is the ultimate response receiver of the first successful
 *          HTTP request.
 * @ingroup S31SdcCommon
 */
template<class T_Result>
using CreateJobCallback = std::function<std::unique_ptr<OutgoingBlockingHttpRequest>(const Url&, const S31::Utils::OutcomeTypes::HandlerPtr<T_Result>&)>;

/**
 * @brief Shared ownership pointer for a callback context.
 * @ingroup S31SdcCommon
 */
using HandlerPtr = S31::Utils::OutcomeTypes::UntypedHandlerPtr;

/**
 * @brief Retry counter for a specific URL.
 * @ingroup S31SdcCommon
 */
using RetryCount = DFL::StrongTypedef<unsigned int, struct RetryCountTag, DFL::Skill::Streamable>;

/**
 * @brief Manages reception of job responses and retries to send requests on failure.
 * @details The endpoint operator receives results from outgoing blocking HTTP requests and retries sending until
 *          successful delivery or until no more URLs to test against are available.
 * @ingroup S31SdcCommon
 */
template<class T_Result>
class Operator:
        public S31::Utils::UntypedOutcomeHandler,
        public std::enable_shared_from_this<Operator<T_Result>>,
        public S31::Utils::OutcomeConsumer<Operator<T_Result>, T_Result>
{
    public:
        Operator(CreateJobCallback<T_Result> createJob,
                 S31::Utils::OutcomeTypes::HandlerPtr<T_Result> interceptedOutcomeHandler,
                 RetryCount retryCount,
                 DFL::NotNull<std::shared_ptr<UrlList>> urlList,
                 std::weak_ptr<IOutgoingJobQueue> jobQueue) :
                m_createJob(std::move(createJob)),
                m_interceptedOutcomeHandler(std::move(interceptedOutcomeHandler)),
                m_retryCount(retryCount),
                m_currentRetryCount(retryCount.get()),
                m_intermediateHandler(),
                m_urlList(std::move(urlList)),
                m_jobQueue(std::move(jobQueue))
        {
        }

        /**
         * @brief Creates a job and tries to execute it with the given URL.
         */
        void tryUrl(const Url& url)
        {
            S31_STREAM_TRACE_LOGGER("Sdc.Client", "Executing job on Url ", url);
            if (auto jobQueue = m_jobQueue.lock())
            {
                // Safe usage of this
                // Rationale: 'this' is captured by the outcome as a shared pointer. So even if the shared
                // m_intermediateHandler is overwritten recursively, the calling instance still holds the memory
                m_intermediateHandler = S31::Utils::OutcomeConsumer<Operator<T_Result>, T_Result>::makeOutcomeHandler([this, url](S31::Utils::Outcome<T_Result> & outcome)
                {
                    // Either success or an error that is not worth to retry
                    if (!outcome.hasError()
                        || outcome.error().template isOneOf<
                              Errors::PayloadTooLarge,
                              Errors::PayloadTooLargeHandlingError>())
                    {
                        m_interceptedOutcomeHandler->endedWithOutcome(outcome);
                        return;
                    }


                    // Try on same URL again if retry count is not empty
                    if (this->m_currentRetryCount > 0)
                    {
                        S31_STREAM_WARN_LOGGER_LIMITED("Sdc.Client", "Executing job failed, start retry. Error was: ", outcome.errorMessage());
                        this->m_currentRetryCount--;
                        this->tryUrl(url);
                        return;
                    }
                    // Reset retry counter since next URL is going to be requested
                    this->m_currentRetryCount = m_retryCount.get();

                    // The endpoint operator's simple assumption: any error is network related,
                    // hence try next URL unless no more URLs are available
                    this->reportBrokenUrl(url);
                    if (auto nextUrl = this->nextUrl())
                    {
                        this->tryUrl(*nextUrl);
                        return;
                    }

                    S31_STREAM_WARN_LOGGER_LIMITED(
                            "Sdc.Client",
                            "Executing job on ",
                            url,
                            " failed, no retry and no alternative URL available. Error was: ",
                            outcome.errorMessage());
                    // no more retries, no more alternative Urls, so report the error
                    m_interceptedOutcomeHandler->endedWithOutcome(outcome);
                });

                if (auto job = m_createJob(url, m_intermediateHandler))
                {
                    jobQueue->addAsyncJob(DFL::asNotNull(std::move(job)));
                }
            }
        }

        /**
         * @brief Consults the URL list to check if there is a URL available.
         * @return The next URL with the highest priority from the pool if available, otherwise \c boost::none.
         */
        [[nodiscard]] boost::optional<Url> nextUrl() const
        {
            return m_urlList->nextAvailableUrl();
        }

        /**
         * @brief Reports a URL as broken, i.e., as temporarily or permanently not accessible.
         */
        void reportBrokenUrl(const Url& url)
        {
            S31_STREAM_WARN_LOGGER_LIMITED("Sdc.Client", "Remove URL ", url, " due to persistent failure");
            m_urlList->removeUrl(url);
        }

    private:
        CreateJobCallback<T_Result> m_createJob;
        S31::Utils::OutcomeTypes::HandlerPtr<T_Result> m_interceptedOutcomeHandler;

        const RetryCount m_retryCount;
        unsigned int m_currentRetryCount;

        S31::Utils::OutcomeTypes::HandlerPtr<T_Result> m_intermediateHandler;

        DFL::NotNull<std::shared_ptr<UrlList>> m_urlList;
        std::weak_ptr<IOutgoingJobQueue> m_jobQueue;
};

/**
 * @brief Provides functionality to repeat sending of outgoing blocking HTTP requests to several URLs.
 * @details The endpoint is an abstraction of a receiver of network requests, in particular HTTP requests.
 *          It can be used, e.g., for any DPWS message transmission to
 *
 *          - devices (hosting services),
 *          - hosted services,
 *          - subscription managers,
 *          - notify-to endpoints, and
 *          - subscription-end endpoints.
 *
 *          The endpoint accepts a job creator function and a callback handler that is used to forward responses to.
 *          Internally, the endpoint loops through a prioritized list of URLs, enqueues a job accordingly and
 *          invokes the given callback handler once one of the jobs succeeds or the last existing job fails.
 *
 *          The following sequence diagram shows the core functionality of the endpoint:
 *
 *          @startuml
 *          !include S31Sdc-EndpointSequenceDiagram.iuml
 *          @enduml
 * @ingroup S31SdcCommon
 */
class Executor
{
    public:
        /**
         * @brief Constructor with empty URL list and job queue.
         */
        Executor() :
                m_urlList(DFL::asNotNull(std::make_shared<ResettableUrlList>())),
                m_retryCount(RetryCount{0})
        {
        }

        /**
         * @brief Constructor.
         * @param urlList A list that provides requesting available URLs and removing of non-reachable URLs.
         * @param jobQueue Job queue in order to process \ref S31::Sdc::Impl::OutgoingBlockingHttpRequest "HTTP requests".
         */
        Executor(DFL::NotNull<std::shared_ptr<UrlList>> urlList,
                 std::weak_ptr<IOutgoingJobQueue> jobQueue) :
                m_urlList(std::move(urlList)),
                m_retryCount(RetryCount{0}),
                m_jobQueue(std::move(jobQueue))
        {
        }

        /**
         * @brief Constructor with retry count.
         * @param urlList A list that provides requesting available URLs and removing of non-reachable URLs.
         * @param retryCount Defines the amount of retries per requested URL.
         * @param jobQueue Job queue in order to process \ref S31::Sdc::Impl::OutgoingBlockingHttpRequest "HTTP requests".
         */
        Executor(DFL::NotNull<std::shared_ptr<UrlList>> urlList,
                 RetryCount retryCount,
                 std::weak_ptr<IOutgoingJobQueue> jobQueue) :
                m_urlList(std::move(urlList)),
                m_retryCount(retryCount),
                m_jobQueue(std::move(jobQueue))
        {
        }

        /**
         * @brief Tries to deliver the given outgoing blocking HTTP request to the first available URL.
         * @param handlerPtr Receiver callback handler that get notified either the first successful job result or the last unsuccessful job result.
         * @param createJob Callback to enable the endpoint to create outgoing blocking HTTP request jobs.
         * @return A handler pointer that needs to be kept by the user until not interested in the job result anymore.
         *         \attention Returns \c nullptr if there was no URL available.
         */
        template<class T_Result>
        HandlerPtr submit(S31::Utils::OutcomeTypes::HandlerPtr<T_Result> handlerPtr, CreateJobCallback<T_Result> createJob) const
        {
            return submit(handlerPtr, m_retryCount, createJob);
        }

        /**
         * @brief Tries to deliver the given outgoing blocking HTTP request to the first available URL.
         * @param handlerPtr Receiver callback handler that get notified either the first successful job result or the last unsuccessful job result.
         * @param retryCount Overwrites retry count for this single submission.
         * @param createJob Callback to enable the endpoint to create outgoing blocking HTTP request jobs.
         * @return A handler pointer that needs to be kept by the user until not interested in the job result anymore.
         *         \attention Returns \c nullptr if there was no URL available.
         */
        template<class T_Result>
        HandlerPtr submit(S31::Utils::OutcomeTypes::HandlerPtr<T_Result> handlerPtr,
                          RetryCount retryCount,
                          CreateJobCallback<T_Result> createJob) const
        {
            auto firstUrl = m_urlList->nextAvailableUrl();
            if (!firstUrl)
            {
                return nullptr;
            }

            auto endpointOperator = std::make_shared<Operator<T_Result>>(createJob, handlerPtr, retryCount, m_urlList, m_jobQueue);
            endpointOperator->tryUrl(*firstUrl);

            return HandlerPtr(std::move(endpointOperator));
        }

        /**
         * @brief Clear URL list held by executor.
         */
        void clearUrlList()
        {
            m_urlList->clear();
        }

    private:
        DFL::NotNull<std::shared_ptr<UrlList>> m_urlList;
        RetryCount m_retryCount;
        std::weak_ptr<IOutgoingJobQueue> m_jobQueue;
};

}
