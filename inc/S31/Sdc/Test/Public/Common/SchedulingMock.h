#pragma once

#include <S31/Sdc/Public/Common/Job.h>
#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequest.h>
#include <S31/Log/Public/Logger.h>

#include <deque>
#include <memory>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief Creates a scheduling mock that counts added jobs.
 * @ingroup S31SdcCommon
 */
class SchedulingMock: public S31::Sdc::Impl::IScheduling
{
    public:
        struct DelayedJob
        {
                std::unique_ptr<Job> job;
                DFL::Chrono::Milliseconds execDelay;
        };

        JobPtrs executeMainLoopUntilNextHttpRequests(DFL::Chrono::Milliseconds /*timeout*/, MaxResultCount /*count*/) override
        {
            if (m_httpJobQueue.empty())
            {
                return JobPtrs{};
            }
            auto job = std::move(m_httpJobQueue.front());
            m_httpJobQueue.pop_front();
            return JobPtrs(std::move(job));
        }

        void executeMainLoop(DFL::Chrono::Milliseconds /*timeout*/) override
        {
        }

        void abortMainLoopExecution() override
        {
        }

        void addOutgoingBlockingHttpRequest(
                DFL::NotNull<std::unique_ptr<S31::Sdc::Impl::OutgoingBlockingHttpRequest>> job) override
        {
            m_httpJobQueue.push_back(std::move(job.get()));
        }

        [[nodiscard]] std::size_t pendingJobSize() const override
        {
            return m_httpJobQueue.size() + m_pendingMainLoopTaskQueue.size() + m_pendingDelayedMainLoopTaskQueue.size();
        }

        void addMainLoopTask(std::unique_ptr<Job> job, DFL::Chrono::Milliseconds executingDelay) override
        {
            m_pendingDelayedMainLoopTaskQueue.push_back(DelayedJob{ std::move(job), executingDelay });
        }

        void addMainLoopTask(std::unique_ptr<Job> job) override
        {
            m_pendingMainLoopTaskQueue.push_back(std::move(job));
        }

        void resetJobs()
        {
            m_httpJobQueue.clear();
            m_pendingMainLoopTaskQueue.clear();
            m_pendingDelayedMainLoopTaskQueue.clear();
        }

        std::deque<std::unique_ptr<Job>>& pendingJobQueue()
        {
            return m_pendingMainLoopTaskQueue;
        }

        std::deque<DelayedJob>& pendingDelayedJobQueue()
        {
            return m_pendingDelayedMainLoopTaskQueue;
        }

    private:
        std::deque<std::unique_ptr<S31::Sdc::Impl::OutgoingBlockingHttpRequest>> m_httpJobQueue;
        std::deque<std::unique_ptr<Job>>                                         m_pendingMainLoopTaskQueue;
        std::deque<DelayedJob>                                                   m_pendingDelayedMainLoopTaskQueue;
};

} /* namespace S31 */
