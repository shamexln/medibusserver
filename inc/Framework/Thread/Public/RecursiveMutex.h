#pragma once

#include <Framework/Thread/Private/ExpImp.h>
#include <Framework/Thread/Private/RecursiveMutexImpl.h>

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
 * @brief A mutex (mutual exclusion) is a synchronization mechanism used to
 * control access to a shared resource in a multithreaded scenario.
 *
 * Mutexes are recursive, that is, the same mutex can be locked multiple times
 * by the same thread (but, of course, not by other threads). Using the
 * DFL::ScopedLock class is the preferred way to automatically lock and unlock
 * a mutex.
 *
 * @note For VxWorks priority inheritance is switched on.
 * Meaning if a low priority task has locked a mutex and a high priority
 * task is waiting for that same mutex, the operating system
 * raises the priority of the low prior task until the mutex is unlocked.
 */
class DFL_THREAD_EXPIMP RecursiveMutex: private Impl::RecursiveMutexImpl
{
    DFL_NOT_COPYABLE(RecursiveMutex)

public:
    /**
     * @brief Creates mutex.
     * @exception std::runtime_error Throws if mutex could not be created.
     */
    RecursiveMutex();

    /**
     * @brief Locks the mutex or blocks if mutex is locked by another thread.
     *
     * @exception std::runtime_error Throws if mutex could not be locked.
     * Most likely it is due to a timeout. Since WAIT_FOREVER is used in the
     * VxWorks implementation this should not throw.
     * On Win32 the timeout is defined by the registry value
     * HKEY_LOCAL_MACHINE/SYSTEM/CurrentControlSet/Control/Session Manager/CriticalSectionTimeout
     */
    void lock();

    /**
     * @brief Tries to lock the mutex and returns immediately.
     * @return True if the mutex was locked otherwise false.
     */
    bool tryLock();

    /**
     * @brief Tries to lock the mutex and returns immediately. Needed to use std::lock()
     * @return True if the mutex was locked otherwise false.
     */
    bool try_lock()
    {
        return tryLock();
    }

    /**
     * @brief Unlocks the mutex so it can be acquired by another thread.
     *
     * @exception std::runtime_error
     * On VxWorks throws if unlock is called on a nonlocked mutex or if the
     * context trying to unlock the mutex did not lock the mutex.
     * On Win32 it does not throw but if the context trying to unlock the mutex
     * did not lock the mutex an error occurs that muy cause another thread
     * using lock to wait indefinitely.
     */
    void unlock();
};

}
}
/** @} */
