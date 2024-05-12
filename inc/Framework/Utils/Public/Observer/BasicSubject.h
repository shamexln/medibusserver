#pragma once

#include <Framework/Utils/Public/Observer/Subject.h>

#include <algorithm>
#include <iterator>
#include <memory>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

namespace DFL
{
namespace Observer
{
/**
 * @brief Generic observable container to enable publish-subscribe for smart
 * pointers.
 *
 * @details This is a helper to use the observer design pattern with the
 * following features:
 *
 * - Observers here are typically instantiations of (arbitriary) abstract
 * classes ('interfaces')
 * - Observers can be registered/unregistered
 * - Observers are removed automatically if they go out of lifetime
 * - Customizable regarding thread-policy and invoking callbacks when notifying
 *
 * Internally the observers are hold as weak pointers.
 *
 * ## Example
 *
 * This observer is generally defined as a virtual abtract interface.
 * @snippet Utils/Sample/Sample.cpp ObserverInterface
 *
 * Derived from the observer interface there is somewhere an
 * implementation of an actual observer
 * @snippet Utils/Sample/Sample.cpp ObserverActual
 *
 * The class that holds all observers uses this class as a helper.
 * @snippet Utils/Sample/Sample.cpp ObservableClass
 *
 * ### Register observers
 * After the according instances have been created the observers can be
 * registered.
 * @snippet Utils/Sample/Sample.cpp ObserverRegistration
 *
 * On status changes the the according notification will be invoked.
 * @snippet Utils/Sample/Sample.cpp InvokeObservers
 *
 * ### Unregister observers
 * An observer can be unregisterd explicitly ...
 * @snippet Utils/Sample/Sample.cpp UnregisterObserver
 *
 * ... or implicit if the lifetime of a registered observer ends.
 * @snippet Utils/Sample/Sample.cpp ResetObserver
 *
 * ## Policies
 *
 * @tparam BasicLockable
 * The given type has to model the named requirement
 * [BasicLockable](https://en.cppreference.com/w/cpp/named_req/BasicLockable),
 * e.g. std::mutex, @ref DFL::Thread::RecursiveMutex, @ref DFL::Thread::NoLock.
 *
 * @tparam InvokePolicy
 * The invoke policy customizes the behavior when invoking the registered
 * observers. Currently there are @ref InvokeAndCatch and @ref Invoke
 * available. This allows to control, e.g. whether an exception from the invoked
 * foreign code breaks notifications or not.
 *
 * Here is an example of an invoke policy which logs exceptions during
 * notifications.
 * @snippet Utils/Sample/Sample.cpp LogExceptionMessage
 * @snippet Utils/Sample/Sample.cpp LogExceptionsDelegate
 *
 * @ingroup Utils
 */
template <class ObserverType, class BasicLockable, class InvokePolicy>
class BasicSubject : public Subject<ObserverType>
{
public:
    /**
     * @brief Register an observer.
     */
    void registerObserver(const std::weak_ptr<ObserverType>& observer) override;
    /**
     * @brief Unregister an observer.
     */
    void unregisterObserver(
        const std::weak_ptr<ObserverType>& observer) override;
    /**
     * @brief Send a notification to all observers.
     * @param func Since the observer subject does not know the details of the
     * observer interface, the user has to put an appropriate function callback
     * to the method, in which the observable subject passes the observer object
     * as the first parameter. The observable subject will then invoke the
     * callback on every observer.
     *
     * See the example.
     */
    template <class Func>
    void notify(Func&& func);
    /**
     * @brief   Returns \c true if no observers exist, otherwise \c false.
     * @details This method does not verify if observer weak pointers are valid.
     */

private:
    // Simple lock guard, to avoid dependency to <mutex>
    class LockGuard
    {
    public:
        explicit LockGuard(BasicLockable& lockable)
            : m_lockable{lockable}
        {
            m_lockable.lock();
        }

        ~LockGuard()
        {
            try
            {
                m_lockable.unlock();
            }
            catch (...)
            {
            }
        }

    private:
        BasicLockable& m_lockable;
    };

    std::vector<std::shared_ptr<ObserverType>> removeExpiredSubscriptions();

    mutable BasicLockable m_lockable{};
    std::set<std::weak_ptr<ObserverType>,
             std::owner_less<std::weak_ptr<ObserverType>>>
        m_observers{};
};

template <class ObserverType, class BasicLockable, class InvokePolicy>
inline void BasicSubject<ObserverType, BasicLockable, InvokePolicy>::
    registerObserver(const std::weak_ptr<ObserverType>& observer)
{
    LockGuard const guard{m_lockable};
    m_observers.insert(observer);
}

template <class ObserverType, class BasicLockable, class InvokePolicy>
inline void BasicSubject<ObserverType, BasicLockable, InvokePolicy>::
    unregisterObserver(const std::weak_ptr<ObserverType>& observer)
{
    LockGuard const guard{m_lockable};
    m_observers.erase(observer);
}

template <class ObserverType, class BasicLockable, class InvokePolicy>
template <class Func>
inline void BasicSubject<ObserverType, BasicLockable, InvokePolicy>::notify(
    Func&& func)
{
    for (const auto& observer : removeExpiredSubscriptions())
    {
        if (observer)
        {
            InvokePolicy::invoke(*observer, std::forward<Func>(func));
        }
    }
}

template <class ObserverType, class BasicLockable, class InvokePolicy>
inline std::vector<std::shared_ptr<ObserverType>> BasicSubject<
    ObserverType,
    BasicLockable,
    InvokePolicy>::removeExpiredSubscriptions()
{
    std::vector<std::shared_ptr<ObserverType>> lockedObservers{};

    {
        LockGuard const guard{m_lockable};
        lockedObservers.reserve(m_observers.size());
        std::transform(m_observers.cbegin(),
                       m_observers.cend(),
                       std::back_inserter(lockedObservers),
                       [](const auto& a) { return a.lock(); });

        decltype(m_observers) notExpired{};
        std::remove_copy_if(m_observers.cbegin(),
                            m_observers.cend(),
                            std::inserter(notExpired, notExpired.end()),
                            [](const auto& a) { return a.expired(); });
        notExpired.swap(m_observers);

        // You might be inclined to think that the following algorithm is
        // better:
        // 1. create a list of not expired weak_ptr
        // 2. call lock on each of them and get a list of only valid shared_ptr
        // 3. no need to check the shared_ptr in notification loop since none of
        // them was expired
        //
        // Unfortunately this does not work.
        // After having created a list of not expired weak_ptr the scheduler
        // might execute another thread. There a shared_ptr might get out of
        // scope. When the scheduler returns control to this thread a lock on
        // the according "not expired" weak_ptr will return nullptr.
        // During the notification loop a SEGFAULT will occur (at best).
        //
        // Here is the according issue:
        // https://jira.draeger.com/browse/PCSWORK-5353
    }

    return lockedObservers;
}
}
}
