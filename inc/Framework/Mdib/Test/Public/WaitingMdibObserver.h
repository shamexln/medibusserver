#pragma once

#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/ScopeExit.h>
#include <chrono>
#include <mutex>

namespace DFL
{
namespace Mdib
{
namespace Test
{

/**
 * @brief MDIB observer with blocking waiting functionality.
 * @details This class supports observing an MDIB until a predicate is fulfilled.
 * It is possible that the MDIB already fulfills the predicate, since there were updates before.
 * @ingroup Mdib
 */
class WaitingMdibObserver: public MdibObserver, public std::enable_shared_from_this<WaitingMdibObserver>
{
    public:

        /**
         * @brief Factory method to ensure shared_ptr instantiation.
         */
        static DFL::NotNull<std::shared_ptr<WaitingMdibObserver>> create(DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> mdib)
        {
            // private constructor is not accessible from make_shared
            return DFL::asNotNull(std::shared_ptr<WaitingMdibObserver>(new WaitingMdibObserver(std::move(mdib))));
        }

        /**
         * @brief Blocks until given predicate is matched or the wait time is reached.
         * @return \c true in case of success.
         */
        bool waitFor(std::chrono::milliseconds waitTime,
                     std::function<bool(const DFL::Mdib::Mdib&)> predicate);

        /**
         * @brief Internal callback for MDIB changes
         */
        void onChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) override;

    private:
        explicit WaitingMdibObserver(DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> mdib):
                m_mdib(std::move(mdib))
        {
        }
        DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> m_mdib;
        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
};

inline bool WaitingMdibObserver::waitFor(std::chrono::milliseconds waitTime, std::function<bool(const DFL::Mdib::Mdib&)> predicate)
{
    m_mdib->registerObserver(shared_from_this());
    ScopeExit unregister([&](){
        m_mdib->unregisterObserver(shared_from_this());
    });

    std::unique_lock<std::mutex> lock(m_mutex);
    if (predicate(*m_mdib->latestMdib()))
    {
        return true;
    }
    // wait for changes (ignore spurious awakenings)
    return m_conditionVariable.wait_for(lock, waitTime, [&]() { return predicate(*m_mdib->latestMdib()); });
}

inline void WaitingMdibObserver::onChange(const NotNull<MdibSharedPtr>& /*mdib*/,
                                          const NotNull<ConstMdibChangeSetSharedPtr>& /*changes*/,
                                          DFL::Mdib::MdibChangeType /*changeType*/)
{
    m_conditionVariable.notify_all();
}

}
}
}
