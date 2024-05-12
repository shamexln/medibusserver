#pragma once

#include <condition_variable>
#include <mutex>

namespace S31::Sdc::Test
{

/**
 * @brief Wrapper around condition variable to ensure that notify_all and wait don't miss each other
 *
 * @details This class attempts to simplify usage of a condition_variable to wait for some event
 * to occur.  It avoids two problems:
 *
 * 1) Due to thread scheduling, notify_all may run before wait is called.  In this case a wait will
 * have an unnecessary timeout delay, or if no timeout is given, will wait forever.
 *
 * This is handled by the predicate test. "Wait with predicate" is equivalent to:
 * while(!(pred()) { wait(lock); }
 * see: https://en.cppreference.com/w/cpp/thread/condition_variable/wait
 *
 * 2) A condition variable may wake-up spuriously, when the expected event has not yet actually occurred.
 *
 *
 * @note The predicate is synchronized with the condition variable mutex, to
 * ensure there is no race between the "cv.wait wake-up predicate test",
 * and notify setting the predicate.
 * see https://stackoverflow.com/a/36130475
 */
class ConditionVariableEvent
{
    public:
        void notify()
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_eventNotified = true;
            }
            m_cv.notify_all();
        }

        void wait()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [&]() -> bool
                {
                    return m_eventNotified;
                });
        }

        template<typename Rep, typename Period>
        void waitFor(std::chrono::duration<Rep, Period> timeout)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait_for(lock, timeout,
                [&]() -> bool
                {
                    return m_eventNotified;
                });
        }

    private:
        mutable std::mutex m_mutex;
        std::condition_variable m_cv;
        bool m_eventNotified{ false };
};

}
