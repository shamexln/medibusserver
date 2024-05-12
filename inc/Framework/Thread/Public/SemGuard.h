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
 * @brief Automatically acquires and releases a semaphore.
 *
 * The constructor acquires ownership of semaphore and acquires it. The destructor
 * releases the semaphore. If guard is constructed with \c adaptLock it is assumed
 * that the given semaphore is already acquired. Then acquire is not called in the
 * constructor but the destructor still releases the semaphore.
 *
 * @tparam BasicSem This concept is fulfilled if type has a \c acquire()
 *                       and \c release() member function.
 */
template<typename BasicSem>
class SemGuard
{
    DFL_NOT_COPYABLE(SemGuard)
public:
    /**
     * @brief Stores semaphore and acquires it.
     * @param semaphore Semaphore to be acquired.
     * @exception Any exception thrown by calling \c acquire().
     */
    explicit SemGuard(BasicSem& semaphore);

    /**
     * @brief Stores semaphore without acquiring it.
     * @param semaphore Semaphore to be owned by acquire guard.
     * @param adopt Tag indicating that acquire should not be called on
     *                         given semaphore.
     */
    SemGuard(BasicSem& semaphore, const AdoptLock& adopt);

    /**
     * @brief Releases semaphore.
     */
    ~SemGuard();

private:
    BasicSem& m_semaphore;
};

template<typename BasicSem>
inline SemGuard<BasicSem>::SemGuard(BasicSem& semaphore) :
    m_semaphore(semaphore)
{
    m_semaphore.acquire();
}

template<typename BasicSem>
inline SemGuard<BasicSem>::SemGuard(BasicSem& semaphore, const AdoptLock&) :
    m_semaphore(semaphore)
{
}

template<typename BasicSem>
inline SemGuard<BasicSem>::~SemGuard()
{
    try
    {
        m_semaphore.release();
    }
    catch (...)
    {
        // swallow any exception
    }
}

}
}
/** @} */
