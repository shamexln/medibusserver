#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequest.h>
#include <S31/Sdc/Private/Common/SoapContextPool.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StdContainerIo.h>

#include <memory>
#include <vector>

namespace S31::Sdc::Test
{

class OutgoingJobQueueMock : public S31::Sdc::Impl::IOutgoingJobQueue,
                             public std::enable_shared_from_this<OutgoingJobQueueMock>
{
    public:
        using Job = std::unique_ptr<S31::Sdc::Impl::OutgoingBlockingHttpRequest>;
        using Jobs = std::vector<Job>;

        OutgoingJobQueueMock()
            : m_soapContextPool(DFL::asNotNull(std::make_shared<Impl::SoapContextPool>()))
            , m_lastReturnedSoapPtr{std::move(m_soapContextPool->getSoapPtr().get())}
        {
        }

        explicit OutgoingJobQueueMock(const DFL::NotNull<std::shared_ptr<CoreConfiguration>>& config)
            : m_soapContextPool(DFL::asNotNull(std::make_shared<Impl::SoapContextPool>(config)))
            , m_lastReturnedSoapPtr{std::move(m_soapContextPool->getSoapPtr().get())}
        {
        }

        DFL::NotNull<std::shared_ptr<Impl::SoapContextPool>> soapContextPool() const
        {
            return m_soapContextPool;
        }

        void setMaxNumberOfIdleSoapContexts(unsigned int /*maxNumberOfIdleSoapContexts*/) override
        {
        }

        void setIdleTimeout(DFL::Chrono::Seconds /*idleTimeout*/) override
        {
        }

        void jobFinishedFor(const std::string& peerTransportAddr, DFL::NotNull<S31::Sdc::Impl::SoapPtr> soapPtr) override
        {
            S31_STREAM_INFO_LOGGER("Test", "job finished for peer address: ", peerTransportAddr);
            m_lastReturnedSoapPtr = std::move(soapPtr.get());
        }

        void jobFinishedFor(const std::string& peerTransportAddr) override
        {
            S31_STREAM_INFO_LOGGER("Test", "job finished for peer address: ", peerTransportAddr);
        }

        void addAsyncJob(DFL::NotNull<std::unique_ptr<S31::Sdc::Impl::OutgoingBlockingHttpRequest>> req) override
        {
            req->setSoapContextPool(m_soapContextPool.get());
            req->setJobQueue(shared_from_this());
            S31_STREAM_INFO_LOGGER("Test", "add async job: ", req->jobName(), ", peer address: ", req->getPeerTransportAddress());
            m_jobs.push_back(std::move(req.get()));
        }

        Jobs& jobs()
        {
            return m_jobs;
        }

        const Jobs& jobs() const
        {
            return m_jobs;
        }

        bool empty() const
        {
            return m_jobs.empty();
        }

        size_t size() const
        {
            return m_jobs.size();
        }

        void resetMock()
        {
            m_jobs = Jobs();
        }
        void executeOneJob()
        {
            if (!m_jobs.empty())
            {
                auto job = std::move(m_jobs.front());
                m_jobs.erase(m_jobs.begin());
                S31_STREAM_INFO_LOGGER("Test", "execute job name: ", job->jobName(), ", peer address: ", job->getPeerTransportAddress(), " ...");

                auto sharedJob = std::shared_ptr<Job::element_type>{std::move(job)};
                sharedJob->execute(sharedJob);
                S31_STREAM_INFO_LOGGER("Test", "execute job name: ", sharedJob->jobName(), ", peer address: ", sharedJob->getPeerTransportAddress(), " done.");
            }
        }

        Job popFirstJob()
        {
            if (!m_jobs.empty())
            {
                auto job = std::move(m_jobs.front());
                m_jobs.erase(m_jobs.begin());
                return job;
            }
            return {};
        }

        S31::Sdc::Impl::SoapPtr& lastReturnedSoapPtr()
        {
            return m_lastReturnedSoapPtr;
        }

    private:
        Jobs                                                 m_jobs;
        DFL::NotNull<std::shared_ptr<Impl::SoapContextPool>> m_soapContextPool;
        S31::Sdc::Impl::SoapPtr                              m_lastReturnedSoapPtr;
};
}
