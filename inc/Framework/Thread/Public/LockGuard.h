#pragma once

#include <Framework/Thread/Public/AdoptLock.h>
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
 * @brief Automatically locks and unlocks a mutex.
 *
 * The constructor acquires ownership of mutex and locks it. The destructor
 * unlocks the mutex. If guard is constructed with \c adaptLock it is assumed
 * that the given mutex is already locked. Then lock is not called in the
 * constructor but the destructor still unlocks the mutex.
 *
 * @tparam BasicLockable This concept is fulfilled if type has a \c lock()
 *                       and \c unlock() member function.
 */
template<typename BasicLockable>
class LockGuard
{
    DFL_NOT_COPYABLE(LockGuard)
public:
    /**
     * @brief Stores mutex and locks it.
     * @param mutex Mutex to be locked.
     * @exception Any exception thrown by calling \c lock().
     */
    explicit LockGuard(BasicLockable& mutex);

    /**
     * @brief Stores mutex without locking it.
     * @param mutex Mutex to be owned by lockguard.
     * @param adoptLockedMutex Tag indicating that lock should not be called on
     *                         given mutex.
     */
    LockGuard(BasicLockable& mutex, const AdoptLock& adoptLockedMutex);

    /**
     * @brief Unlocks mutex.
     */
    ~LockGuard();

private:
    BasicLockable& m_mutex;
};

template<typename BasicLockable>
inline LockGuard<BasicLockable>::LockGuard(BasicLockable& mutex) :
    m_mutex(mutex)
{
    m_mutex.lock();
}

template<typename BasicLockable>
inline LockGuard<BasicLockable>::LockGuard(BasicLockable& mutex, const AdoptLock&) :
    m_mutex(mutex)
{
}

template<typename BasicLockable>
inline LockGuard<BasicLockable>::~LockGuard()
{
    try
    {
        m_mutex.unlock();
    }
    catch (...)
    {
        // swallow any exception
    }
}

}
}
/** @} */
