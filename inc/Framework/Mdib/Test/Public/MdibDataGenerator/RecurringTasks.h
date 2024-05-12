#pragma once

#include <condition_variable>
#include <map>
#include <memory>
#include <thread>
#include <chrono>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/TimePoint.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Utils/Public/ScopeExit.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/CommonTypes.h>

namespace DFL
{
namespace Mdib
{
namespace Test
{

/**
 * @brief A task that is executed again & again.
 */
class RecurringTask
{
    public:
        /// Destructor.
        virtual ~RecurringTask() = default;

        /**
         * @brief Execute the task.
         * @return The time point for the next execution.
         */
        virtual ExecutionTimepoint execute() = 0;
};

using WeakRecurringTask = std::weak_ptr<RecurringTask>;

/**
 * @brief Container for recurring tasks & executor.
 * @details Spawns a thread for executions if there are tasks.
 */
class RecurringTasksScheduler
{
    public:
        ~RecurringTasksScheduler();

        /**
         * @brief Add a task that will be executed for the first time at given time point.
         * @details If the task is deleted, then it's removed from the task container.
         */
        void add(WeakRecurringTask task, ExecutionTimepoint firstExecutionAt);

    private:
        std::thread m_worker;
        bool m_running = false;
        bool m_stop = false;
        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
        std::multimap<ExecutionTimepoint, WeakRecurringTask> m_futureExecutions;

        void workerThreadFunction();

};

inline RecurringTasksScheduler::~RecurringTasksScheduler()
{
    if (m_running)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_stop = true;
            m_conditionVariable.notify_all();
        }
    }
    if (m_worker.joinable())
    {
        m_worker.join();
    }
}

inline void RecurringTasksScheduler::add(WeakRecurringTask task, ExecutionTimepoint firstExecutionAt)
{
    bool startThread = false;
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_futureExecutions.insert(std::make_pair(firstExecutionAt, std::move(task)));
        if (!m_running)
        {
            startThread = true;
        }
        else
        {
            m_conditionVariable.notify_all();
        }
    }

    if (startThread)
    {
        m_worker = std::thread([this]()
        {
            this->workerThreadFunction();
        });
    }
}

inline void RecurringTasksScheduler::workerThreadFunction()
{
    ScopeExit onExit([this]()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_running = false;
    });

    while (true)
    {
        std::shared_ptr<RecurringTask> nextTask;
        // get first/next element and wait until execution time
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_running = true;

            if (m_futureExecutions.empty() || m_stop)
            {
                return;
            }

            const auto oldSize = m_futureExecutions.size();
            auto somebodyAddedATaskOrStopRequested = [oldSize, this]()
            {
                return oldSize < this->m_futureExecutions.size() || m_stop;
            };

            const auto nextTime = m_futureExecutions.begin()->first;
            const auto now = DFL::Chrono::SteadyClock::now();
            if (nextTime - now > DFL::Chrono::Milliseconds(1))
            {
                 const auto waitTimeToNextTime =
                         std::chrono::nanoseconds(
                             DFL::Chrono::duration_cast<DFL::Chrono::Nanoseconds>(nextTime - now).count());

                if (m_conditionVariable.wait_for(lock, waitTimeToNextTime, somebodyAddedATaskOrStopRequested))
                {
                    continue;
                }
            }

            nextTask = m_futureExecutions.begin()->second.lock();
            m_futureExecutions.erase(m_futureExecutions.begin());
        }

        if (!nextTask)
        {
            continue;
        }

        const auto nextTime = nextTask->execute();

        std::unique_lock<std::mutex> lock(m_mutex);
        m_futureExecutions.insert(std::make_pair(nextTime, nextTask));
    }
}


}
}
}
