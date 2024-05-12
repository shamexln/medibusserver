#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/CallbackJob.h>
#include <S31/Sdc/Public/Common/IJobQueue.h>
#include <S31/Sdc/Public/Common/Job.h>

#include <condition_variable>
#include <mutex>
#include <thread>

namespace S31::Sdc::Test
{

/**
 * @ingroup S31SdcCommon
 */
class JobQueueMock: public IJobQueue
{
    public:
        JobPtrs executeMainLoopUntilNextAsyncJobs(DFL::Chrono::Milliseconds /*timeout*/, MaxResultCount /*maxResultCount*/) override
        {
            S31_STREAM_INFO_LOGGER("S31.Sdc", "JobQueueMock::executeMainLoopUntilNextAsyncJob()");
            executeCalled();
            std::this_thread::sleep_for(std::chrono::seconds{1});
            {
                std::lock_guard<std::mutex> lock(m_jobsMutex);
                if (!m_jobs.empty())
                {
                    auto job = m_jobs[0];
                    m_jobs.erase(m_jobs.begin());
                    std::unique_ptr<Job> cbJob = std::make_unique<S31::Sdc::Impl::CallbackJob>("dummy job", job);
                    return JobPtrs(std::move(cbJob));
                }
            }
            return JobPtrs{};
        }

        void executeMainLoop(DFL::Chrono::Milliseconds /*timeout*/) override
        {
            S31_STREAM_INFO_LOGGER("S31.Sdc", "JobQueueMock::executeMainLoop()");
            executeCalled();
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }

        void abortMainLoopExecution() override
        {
            S31_STREAM_INFO_LOGGER("S31.Sdc", "JobQueueMock::abortMainLoopExecution()");
            ++m_abortCount;
        }

        size_t getQSize() const override
        {
            S31_STREAM_INFO_LOGGER("S31.Sdc", "JobQueueMock::getQSize()");
            return 2U;
        }

        void addJob(std::function<void()> job)
        {
            std::lock_guard<std::mutex> lock(m_jobsMutex);
            S31_STREAM_INFO_LOGGER("S31.Sdc", "JobQueueMock::addJob()");
            m_jobs.push_back(std::move(job));
        }

        int executeCount() const
        {
            return m_executeCount;
        }
        int abortCount() const
        {
            return m_abortCount;
        }

        bool waitForExecuteCount(int count, std::chrono::seconds timeout)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            S31_STREAM_INFO_LOGGER("S31.Sdc", "JobQueueMock::waitForExecuteCount(", count, ", ...)");
            return m_conditionVariable.wait_for(lock, timeout, [&]{return m_executeCount >= count;});
        }
    private:
        void executeCalled()
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                S31_STREAM_INFO_LOGGER("S31.Sdc", "JobQueueMock::executeCalled()");
                ++m_executeCount;
            }
            m_conditionVariable.notify_all();
        }

        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
        int m_abortCount = 0;
        int m_executeCount = 0;

        std::mutex m_jobsMutex;
        std::vector<std::function<void()>> m_jobs;
};

}
