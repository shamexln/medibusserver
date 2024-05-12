#pragma once

#include <S31/Base/S31Only/Exception.h>
#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Localization/S31Only/Common/LocalizedTextFilter.h>
#include <S31/Localization/S31Only/Common/LocalizedTextReferenceHelper.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Client/Localization/ErrorDefinitions.h>
#include <S31/Sdc/Private/Client/Localization/LocalizedTextsExecutorHelper.h>
#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/Utils/Public/Outcome.h>

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Utils/Public/LanguageTag.h>

#include <boost/optional/optional.hpp>

#include <functional>
#include <memory>
#include <mutex>

namespace S31::Sdc::Impl::LocalizationImpl
{

/**
 * @brief Handles requests of given @ref S31::Localization::LocalizedTextReferences from a device.
 * @details Gets references, slices them into different filters, and manages the according jobs to request the texts.
 *
 * ### Errors in Jobs
 * If a job results in an error, the @ref LocalizedTextExecutor notifies the error to the user. On the other hand
 * due to the use of @ref S31::Sdc::Impl::Endpoint::Executor "Endpoint::Executor" recovering from errors is limited. The later
 * will drop target URLs that are connected to a job error (and retry). So in case of error all URLs will be deleted
 * from the @ref S31::Sdc::Impl::Endpoint::Executor "Endpoint::Executor". Only jobs that are already in the job queue are
 * having chance to succeed (i.e. all open transactions). New transactions will fail.
 *
 * @ingroup S31SdcClient
 */
template <class LocalizedTextJob>
class LocalizedTextExecutor:
        public std::enable_shared_from_this<LocalizedTextExecutor<LocalizedTextJob>>,
        public Utils::OutcomeConsumer<LocalizedTextExecutor<LocalizedTextJob>, Sdc::Impl::GetLocalizedTextJobResult>
{
    public:
        using Job = LocalizedTextJob;
        using JobId = Execution::JobId;
        using TransactionId = Execution::TransactionId;
        using Url = Sdc::Impl::Endpoint::Url;
        using Handler = Utils::OutcomeTypes::HandlerPtr<Sdc::Impl::GetLocalizedTextJobResult>;
        using OutcomeType = typename Utils::OutcomeConsumer<LocalizedTextExecutor<LocalizedTextJob>, Sdc::Impl::GetLocalizedTextJobResult>::OutcomeType;

        using ResultAvailableCallback = std::function<void(TransactionId, S31::Localization::LocalizedTextReferences&&, DFL::Mdib::LocalizedTexts&&)>;
        using TransactionCompleteCallback = std::function<void(TransactionId, const boost::optional<Utils::Error>&)>;

        /**
         * @brief Constructor
         * @param mdibVersion MDIB version for sequence change detection.
         * @param executor The executor containing the the service addresses.
         * @param resultsAvailable User provided callback for receiving requested texts. Called for a part of the texts
         *    of the according transaction.
         * @param complete User provided callback to signal a completed transaction. Called after the last part of texts
         *    were received or of one of the jobs ended with an error.
         */
        LocalizedTextExecutor(const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
                              S31::Sdc::Impl::Endpoint::Executor executor,
                              ResultAvailableCallback resultsAvailable,
                              TransactionCompleteCallback complete);

        /**
         * @brief Start a transaction to get the texts for given references from the remote device.
         * @param references The references
         * @param language desired language of the texts
         * @return transaction Id, to align with the callbacks for texts and completion
         */
        boost::optional<TransactionId> execute(S31::Localization::LocalizedTextReferences &&references,
                                               const DFL::Locale::LanguageTag& language);

    private:
        struct JobDataNeededForSubmit
        {
                JobId id;
                Handler handler;
                Execution::CreateJobCallback createJobCallback;
        };

        void handleOutcome(
                typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
                typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId,
                typename LocalizedTextExecutor<LocalizedTextJob>::OutcomeType& outcome);

        /// Splits the given job into 2 smaller ones and put them into the transaction and job queue
        boost::optional<Utils::Error> splitAndResubmit(
                typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
                typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId);

        void submitTransaction(typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId);
        void submitTransaction(std::vector<typename LocalizedTextExecutor<LocalizedTextJob>::JobDataNeededForSubmit>& data,
                               typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId);

        void setCallbacks(Execution::JobData& jobData,
                typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
                typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId);

        std::unique_ptr<Sdc::Impl::OutgoingBlockingHttpRequest> createJob(
                typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
                typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId,
                const typename LocalizedTextExecutor<LocalizedTextJob>::Url& target,
                const typename LocalizedTextExecutor<LocalizedTextJob>::Handler& handle);

        DFL::Mdib::MdibVersion m_mdibVersion;
        S31::Sdc::Impl::Endpoint::Executor m_executor;
        ResultAvailableCallback m_resultAvailableCallback;
        TransactionCompleteCallback m_transactionCompleteCallback;
        std::mutex m_mutex;
        Execution::Transactions m_transactions;
};


template <class LocalizedTextJob>
inline LocalizedTextExecutor<LocalizedTextJob>::LocalizedTextExecutor(
        const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
        Sdc::Impl::Endpoint::Executor executor,
        ResultAvailableCallback resultsAvailable,
        TransactionCompleteCallback complete):
    m_mdibVersion(mdibVersion),
    m_executor(std::move(executor)),
    m_resultAvailableCallback(std::move(resultsAvailable)),
    m_transactionCompleteCallback(std::move(complete))
{
}

template<class LocalizedTextJob>
inline boost::optional<typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId> LocalizedTextExecutor<LocalizedTextJob>::execute(
        S31::Localization::LocalizedTextReferences&& references, const DFL::Locale::LanguageTag& language)
{
    S31_STREAM_TRACE_LOGGER("Localization","Execute 'get texts' for ", references.size(), " references");
    if (references.empty())
    {
        return boost::none;
    }

    using namespace Execution;

    auto transactionId = TransactionId();
    Transaction transaction{};
    transaction.language = language;
    auto filterRefs = makeFilters(references, language);

    for (auto&& fr : filterRefs)
    {
        JobData jdata;
        const auto& jobId = jdata.id;
        jdata.references = std::move(fr.references);
        jdata.filter = std::move(fr.filter);
        setCallbacks(jdata, transactionId, jobId);
        transaction.jobs[jobId] = std::move(jdata);
    }

    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        m_transactions.add(transactionId, std::move(transaction));
    }
    submitTransaction(transactionId);

    return transactionId;
}


template<class LocalizedTextJob>
inline void LocalizedTextExecutor<LocalizedTextJob>::handleOutcome(
        typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
        typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId,
        typename LocalizedTextExecutor<LocalizedTextJob>::OutcomeType& outcome)
{
    if (outcome.hasError())
    {
        auto mappedError = outcome.error();
        if (outcome.error().template is<Sdc::Impl::Errors::PayloadTooLarge>())
        {
            auto splitError = splitAndResubmit(transactionId, jobId);
            if (!splitError)
            {
                return; // will retry with smaller requests
            }
            mappedError = Utils::makeError(Sdc::Impl::Errors::PayloadTooLargeHandlingError{}, "Handling of too large payload failed. (");
            mappedError.messageStream() << splitError->message() << ")";
        }

        m_transactionCompleteCallback(transactionId, mappedError);
        std::lock_guard<std::mutex> const guard(m_mutex);
        m_transactions.deleteTransaction(transactionId);
        return;
    }

    auto result = outcome.result();
    if (!result)
    {
        S31_THROW_EXCEPTION_WITH_ERROR(Sdc::Impl::Errors::IncomingDataNotUnderstood{}, "No result in LocalizedTextExecutor<LocalizedTextJob>::handleOutcome()");
    }

    {
        if (result->mdibVersion.isOtherSequenceOf(m_mdibVersion))
        {
            auto error = Utils::makeError(Sdc::Impl::Errors::MdibSequenceIdMismatch{}, "MDIB SequenceId mismatch");
            m_transactionCompleteCallback(transactionId, error);
            std::lock_guard<std::mutex> const guard(m_mutex);
            m_transactions.deleteTransaction(transactionId);
            return;
        }
    }

    {
        std::unique_lock<std::mutex> lock(m_mutex);
        auto* jobDataPtr = m_transactions.jobData(transactionId, jobId);
        if (!jobDataPtr)
        {
            auto error = S31::Utils::makeError(Errors::OutcomeNotAssignableToJob{}, "No job for received outcome");
            lock.unlock();
            m_transactionCompleteCallback(transactionId, error);
            return;
        }

        auto jobData = m_transactions.extractJobData(transactionId, jobId);
        lock.unlock();
        S31_STREAM_TRACE_LOGGER("Localization", "Got ", result->texts.size(), " texts for ", jobData.references.size(), " references");
        m_resultAvailableCallback(transactionId, std::move(jobData.references), std::move(result->texts));
    }

    {
        std::unique_lock<std::mutex> lock(m_mutex);
        auto* transactionPtr = m_transactions.transaction(transactionId);
        if (!transactionPtr)
        {
            auto error = S31::Utils::makeError(Errors::OutcomeNotAssignableToTransaction{}, "No transaction for received outcome");
            lock.unlock();
            m_transactionCompleteCallback(transactionId, error);
            return;
        }

        if (transactionPtr->jobs.empty())
        {
            m_transactions.deleteTransaction(transactionId);
            lock.unlock();
            m_transactionCompleteCallback(transactionId, boost::none);
        }
    }
}

template<class LocalizedTextJob>
inline boost::optional<Utils::Error> LocalizedTextExecutor<LocalizedTextJob>::splitAndResubmit(
        typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
        typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId)
{
    S31_STREAM_TRACE_LOGGER("Localization", "Split job");

    JobId const jobId1;
    JobId const jobId2;
    Execution::JobData oldJob;
    DFL::Locale::LanguageTag language;

    const std::string failure = "Slicing of localization get text job failed. ";

    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        oldJob = m_transactions.extractJobData(transactionId, jobId);
        auto* transaction = m_transactions.transaction(transactionId);
        if (!transaction)
        {
            return Utils::makeError(Errors::JobNotSliceable{}, failure + "(unknown transaction)");
        }

        // prevent that the transaction can become empty (the old job is extracted already)
        Execution::JobData placeholder;
        placeholder.id = jobId1;
        transaction->jobs[jobId1] = placeholder;
        placeholder.id = jobId2;
        transaction->jobs[jobId2] = placeholder;

        language = transaction->language;
    }

    auto slices = sliceReferences(std::move(oldJob.references));
    if (!slices)
    {
        return Utils::makeError(Errors::JobNotSliceable{}, failure + "(could not slice)");
    }

    Execution::JobData jobData1;
    Execution::JobData jobData2;
    jobData1.id = jobId1;
    jobData2.id = jobId2;

    auto filterRefs1 = makeFilters(slices->first, language);
    auto filterRefs2 = makeFilters(slices->second, language);

    if (filterRefs1.size() != 1 || filterRefs2.size() != 1)
    {
        // each slice has to be representable with exactly one filter (because the old job was also)
        return Utils::makeError(Errors::JobNotSliceable{}, failure + "(could not make filter)");
    }

    jobData1.references = std::move(filterRefs1[0].references);
    jobData1.filter = std::move(filterRefs1[0].filter);

    jobData2.references = std::move(filterRefs2[0].references);
    jobData2.filter = std::move(filterRefs2[0].filter);

    setCallbacks(jobData1, transactionId, jobData1.id);
    setCallbacks(jobData2, transactionId, jobData2.id);

    std::vector<JobDataNeededForSubmit> dataForSubmit;
    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        auto* transaction = m_transactions.transaction(transactionId);
        if (!transaction)
        {
            return Utils::makeError(Errors::JobNotSliceable{}, failure + "(unknown transaction (2))");
        }

        transaction->jobs[jobId1] = jobData1;
        transaction->jobs[jobId2] = jobData2;

        JobDataNeededForSubmit const data1{jobData1.id, jobData1.handler, jobData1.createJobCallback};
        JobDataNeededForSubmit const data2{jobData2.id, jobData2.handler, jobData2.createJobCallback};

        dataForSubmit.push_back(data1);
        dataForSubmit.push_back(data2);
    }

    submitTransaction(dataForSubmit, transactionId);
    return boost::none;
}

template<class LocalizedTextJob>
inline void LocalizedTextExecutor<LocalizedTextJob>::submitTransaction(
        typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId)
{
    std::vector<JobDataNeededForSubmit> dataForSubmit;

    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        auto* transaction = m_transactions.transaction(transactionId);
        if (!transaction)
        {
            return;
        }
        const auto& td = transaction->jobs;
        using Td = std::map<JobId, Execution::JobData>;
        std::transform(td.begin(), td.end(), std::back_inserter(dataForSubmit), [&](const Td::value_type& d)
        {
            return JobDataNeededForSubmit{d.second.id, d.second.handler, d.second.createJobCallback};
        });
    }

    submitTransaction(dataForSubmit, transactionId);
}

template<class LocalizedTextJob>
void LocalizedTextExecutor<LocalizedTextJob>::submitTransaction(
        std::vector<typename LocalizedTextExecutor<LocalizedTextJob>::JobDataNeededForSubmit>& data,
        typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId)
{
    for (auto& jd : data)
    {
        auto executorHandler = m_executor.submit<Sdc::Impl::GetLocalizedTextJobResult>(jd.handler, jd.createJobCallback);

        std::lock_guard<std::mutex> const guard(m_mutex);
        if (auto jobDataPtr = m_transactions.jobData(transactionId, jd.id))
        {
            jobDataPtr->executorHandler = executorHandler;
        }
    }
}

template<class LocalizedTextJob>
inline void LocalizedTextExecutor<LocalizedTextJob>::setCallbacks(
        Execution::JobData& jobData,
        typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
        typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId)
{
    jobData.handler = this->makeOutcomeHandler(
                [transactionId, jobId, this](OutcomeType& outcome)
    {
        this->handleOutcome(transactionId, jobId, outcome);
    });

    std::weak_ptr<LocalizedTextExecutor> const weakThis = this->shared_from_this();

    jobData.createJobCallback = [transactionId, jobId, weakThis] (const Url& target, const Handler& handler)
    {
        if (auto lockedThis = weakThis.lock())
        {
            return lockedThis->createJob(transactionId, jobId, target, handler);
        }
        return std::unique_ptr<Sdc::Impl::OutgoingBlockingHttpRequest>(nullptr);
    };
}

template<class LocalizedTextJob>
inline std::unique_ptr<Sdc::Impl::OutgoingBlockingHttpRequest> LocalizedTextExecutor<LocalizedTextJob>::createJob(
        typename LocalizedTextExecutor<LocalizedTextJob>::TransactionId transactionId,
        typename LocalizedTextExecutor<LocalizedTextJob>::JobId jobId,
        const typename LocalizedTextExecutor<LocalizedTextJob>::Url& target,
        const typename LocalizedTextExecutor<LocalizedTextJob>::Handler& handler)
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    auto* job = m_transactions.jobData(transactionId, jobId);
    if (!job)
    {
        return nullptr;
    }

    return std::make_unique<Job>(handler, target, job->filter);
}

}
