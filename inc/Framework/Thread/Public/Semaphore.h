#pragma once

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Thread/Private/SemaphoreImpl.h>
#include <Framework/Thread/Private/ExpImp.h>
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
 * @brief A semaphore is a synchronization object used to manage access to a
 * limited resource from the outside.
 *
 * A semaphore has a counter that is constrained to be a non-negative integer
 * and two atomic operations. The allowable operations are acquire and release.
 * An acquire decrements the counter and a release increments the counter. If
 * an acquire is called on a semaphore with a counter equal to zero the call
 * will be blocked until the count gets to a non-zero value.
 *
 * In this example two threads want to write to a shared resource.
 * \snippet Thread/Test/IntegrationTest/TestSemaphoreIntegration.cpp DoxygenSnippet_Workers
 * The semaphore is used to control the access to the shared resource.
 * \snippet Thread/Test/IntegrationTest/TestSemaphoreIntegration.cpp DoxygenSnippet_Sync
 */
class DFL_THREAD_EXPIMP Semaphore: private Impl::SemaphoreImpl
{
    DFL_NOT_COPYABLE(Semaphore)

public:
    /**
     * @brief Constructs semaphore with an initial count.
     *
     * This really is just an \b initial count. If a semaphore is released
     * after construction it can be acquired initial count + 1 times.
     *
     * @code
     * Semaphore s(1); // counter == 1
     * s.release(); // counter == 2
     * s.release(); // counter == 3
     * s.acquire(); // counter == 2
     * s.acquire(); // counter == 1
     * s.acquire(); // counter == 0
     * s.acquire(); // this blocks
     * @endcode
     *
     * @param initialCount The start value of the internal counter of the semaphore.
     * @exception std::runtime_error Throws if semaphore could not be created.
     */
    explicit Semaphore(unsigned int initialCount);

    /**
     * @brief Decrements the counter of the semaphore.
     *
     * This call blocks if counter of semaphore is zero until the count gets to
     * a non-zero value.
     *
     * @exception std::runtime_error Throws if semaphore could not be acquired.
     */
    void acquire();

    /**
     * @brief Tries to acquire the semaphore for a sepecified duration.
     * @param timeoutDuration The duration to wait for the semaphore to become available.
     * @return True if semaphore could be acquired otherwise false.
     */
    bool tryAcquireFor(const Chrono::Milliseconds& timeoutDuration);

    /**
     * @brief Increments the counter of the semaphore.
     *
     * Another context trying to acquire this semaphore will be able to continue.
     *
     * @exception std::runtime_error Throws if semaphore could not be released.
     */
    void release();
};

}
}
/** @} */
