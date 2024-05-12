#pragma once

#include <S31/Sdc/Private/Common/Scheduling/TimerTask.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>

#include <map>
#include <memory>
#include <mutex>
#include <string>

namespace S31::Sdc
{
class Job;
namespace Impl
{

/**
 * @brief Thread-safe queue for a \ref Job that shall be started with a delay time.
 * @details The queue is sorted, so that next task is given when queried.
 *
 * @deprecated To be removed if old scheduling does no longer execute timed (mainloop) tasks
 *
 * @ingroup S31SdcCommonScheduling
 */
class S31_CORE_EXPIMP TimerTaskQueue
{
    public:
        bool empty() const;

        size_t size() const;

        void addTask(std::unique_ptr<Job> task, DFL::Chrono::SteadyClock::TimePoint startTime);

        std::unique_ptr<Job> getNextTaskIfPending();

        DFL::Chrono::Milliseconds getDelayForNextPendingTask() const;

        /// Name of the jobs, for logging and debugging.
        std::string taskNames() const;
    private:
        std::multimap<DFL::Chrono::SteadyClock::TimePoint, TimerTask> m_queue;
        mutable std::mutex m_queueMutex;
};

}
}
