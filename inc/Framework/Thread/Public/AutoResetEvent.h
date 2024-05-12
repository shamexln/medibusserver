#pragma once

#include <Framework/Thread/Private/AutoResetEventImpl.h>
#include <Framework/Thread/Private/ExpImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

/**
 * @ingroup Thread
 * @{
 */
namespace DFL
{
namespace Thread
{
/**
 * @brief Tag type indicating the blocking strategy.
 */
struct DFL_THREAD_EXPIMP InitiallyBlocking
{
};

/**
 * @brief Instance of tag type used to specify the blocking strategy.
 *
 * @see DFL::Thread::AutoResetEvent(InitiallyBlocking)
 * @ingroup Thread
 */
extern DFL_THREAD_EXPIMP const InitiallyBlocking initiallyBlocking;

/**
 * @brief An Event is a synchronization object that allows one thread to signal
 * one other threads that a certain event has happened.
 *
 * Usually, one thread signals an event, while one or more other threads
 * wait for an event to become signalled.
 *
 * @note
 * Under VxWorks the thread with the highest priority is released
 * if the event is signalled. This is not the case for windows.
 * The OS decides which thread is released and it does not have to be
 * the one with the highest priority.
 */
class DFL_THREAD_EXPIMP AutoResetEvent: private Impl::AutoResetEventImpl
{
    DFL_NOT_COPYABLE(AutoResetEvent)

public:
    /**
     * @brief Initializes the event with initial state signalled.
     *
     * The first thread that calls wait won't be blocked.
     * But any further thread calling wait will be blocked.
     */
    AutoResetEvent();

    /**
     * @brief Initializes the event with initial state unsignalled.
     *
     * Any thread calling wait will be blocked.
     */
    explicit AutoResetEvent(InitiallyBlocking);

    /**
     * @brief Waits for the event to become signalled.
     *
     * If the event is already signalled the function returns immediately.
     * If not, the calling thread will be blocked.
     */
    void wait();

    /**
     * @brief Blocks caller at maximum for for the given amount of time.
     *
     * If the event is already signalled the function returns immediately.
     *
     * @param timeoutDuration Maximum of time to be waited for the event becoming signalled.
     * @return True if the event became signalled within the specified time interval
     * otherwise false.
     */
    bool tryWaitFor(const Chrono::Milliseconds& timeoutDuration);

    /**
     * @brief Signals the event.
     *
     * One thread waiting for the event can resume execution.
     */
    void set();
};

}
}
/** @} */
