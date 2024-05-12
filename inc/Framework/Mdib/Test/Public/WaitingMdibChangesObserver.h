#pragma once

#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Mdib/Public/SubdividedMdibObserver.h>
#include <condition_variable>
#include <memory>
#include <mutex>

namespace DFL
{
namespace Mdib
{
namespace Test
{

/**
 * @brief MDIB changes observer with blocking waiting functionality.
 * @details This class supports observing MDIB changes until a predicate is fulfilled.
 * After creation the observer all changesets are stored for analyses afterwards.
 * @ingroup Mdib
 */
class WaitingMdibChangesObserver: public SubdividedMdibObserver, public std::enable_shared_from_this<WaitingMdibChangesObserver>
{
    public:
        /**
         * @brief Factory method to ensure shared_ptr instantiation.
         */
        static DFL::NotNull<std::shared_ptr<WaitingMdibChangesObserver>> create(DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> mdib)
        {
            // private constructor is not accessible from make_shared
            auto observer = DFL::asNotNull(std::shared_ptr<WaitingMdibChangesObserver>(new WaitingMdibChangesObserver(std::move(mdib))));
            observer->m_mdib->registerSubdividedObserver(observer.get());
            return observer;
        }

        /**
         * @brief Blocks until given predicate is matched or the wait time is reached.
         * @return \c true in case of success.
         */
        template<class Rep, class Period>
        bool waitFor(std::chrono::duration<Rep, Period> waitTime,
                     std::function<bool(const NotNull<MdibSharedPtr>&, const NotNull<ConstMdibChangeSetSharedPtr>&)> predicate,
                     boost::optional<DFL::Mdib::MdibChangeType> changeType = boost::none);

        /**
         * @brief Blocks until given predicate is matched or the wait time is reached. Does not track the change.
         * @return \c true in case of success.
         */
        template<class Rep, class Period>
        bool waitForDontTrack(std::chrono::duration<Rep, Period> waitTime,
                              std::function<bool(const NotNull<MdibSharedPtr>&, const NotNull<ConstMdibChangeSetSharedPtr>&)> predicate,
                              boost::optional<DFL::Mdib::MdibChangeType> changeType = boost::none);
        /**
         * @brief Clears all previously received MDIB changes.
         */
        void clearTrackedChanges();

        /**
         * @brief Override to track MDIB changes.
         */
        void onDescriptionChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) override;
        /**
         * @brief Override to track MDIB changes.
         */
        void onAlertChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) override;
        /**
         * @brief Override to track MDIB changes.
         */
        void onComponentChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) override;
        /**
         * @brief Override to track MDIB changes.
         */
        void onContextChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) override;
        /**
         * @brief Override to track MDIB changes.
         */
        void onMetricChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) override;
        /**
         * @brief Override to track MDIB changes.
         */
        void onOperationChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) override;
        /**
         * @brief Override to track MDIB changes.
         */
        void onSampleArrayMetricChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) override;

    private:
        explicit WaitingMdibChangesObserver(DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> mdib):
                m_mdib(std::move(mdib))
        {
        }

        void onChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType);
        bool predicateMacthesReceivedChangesNoLock(std::function<bool(const NotNull<MdibSharedPtr>&, const NotNull<ConstMdibChangeSetSharedPtr>&)> predicate,
                                                   boost::optional<DFL::Mdib::MdibChangeType> reportType,
                                                   bool trackChanges);
        DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> m_mdib;
        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
        struct TrackedChange
        {
                TrackedChange(NotNull<MdibSharedPtr> m, NotNull<ConstMdibChangeSetSharedPtr> c, DFL::Mdib::MdibChangeType t):
                    mdib(std::move(m)),
                    changes(std::move(c)),
                    changeType(t)
                {
                }
                NotNull<MdibSharedPtr> mdib;
                NotNull<ConstMdibChangeSetSharedPtr> changes;
                DFL::Mdib::MdibChangeType changeType;
        };
        std::vector<TrackedChange> m_changes;

};

template<class Rep, class Period>
bool WaitingMdibChangesObserver::waitFor(
        std::chrono::duration<Rep, Period> waitTime,
        std::function<bool(const NotNull<MdibSharedPtr> &, const NotNull<ConstMdibChangeSetSharedPtr> &)> predicate,
        boost::optional<DFL::Mdib::MdibChangeType> changeType)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    // check previous received MDIB changes
    if (predicateMacthesReceivedChangesNoLock(predicate, changeType, true))
    {
        return true;
    }
    // wait for changes (ignore spurious awakenings)
    return m_conditionVariable.wait_for(lock, waitTime, [&]() { return predicateMacthesReceivedChangesNoLock(predicate, changeType, true); });
}

template<class Rep, class Period>
bool WaitingMdibChangesObserver::waitForDontTrack(
        std::chrono::duration<Rep, Period> waitTime,
        std::function<bool(const NotNull<MdibSharedPtr> &, const NotNull<ConstMdibChangeSetSharedPtr> &)> predicate,
        boost::optional<DFL::Mdib::MdibChangeType> changeType)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    // check previous received MDIB changes
    if (predicateMacthesReceivedChangesNoLock(predicate, changeType, false))
    {
        return true;
    }
    // wait for changes (ignore spurious awakenings)
    return m_conditionVariable.wait_for(lock, waitTime, [&]() { return predicateMacthesReceivedChangesNoLock(predicate, changeType, false); });
}

inline void WaitingMdibChangesObserver::clearTrackedChanges()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_changes.clear();
}

inline void WaitingMdibChangesObserver::onChange(
        const NotNull<MdibSharedPtr>& mdib,
        const NotNull<ConstMdibChangeSetSharedPtr>& changes,
        DFL::Mdib::MdibChangeType changeType)
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_changes.push_back(TrackedChange(mdib, changes, changeType));
    }
    m_conditionVariable.notify_all();
}

inline void WaitingMdibChangesObserver::onDescriptionChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes)
{
    onChange(mdib, changes, DFL::Mdib::MdibChangeType::Description);
}

inline void WaitingMdibChangesObserver::onAlertChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes)
{
    onChange(mdib, changes, DFL::Mdib::MdibChangeType::AlertStates);
}

inline void WaitingMdibChangesObserver::onComponentChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes)
{
    onChange(mdib, changes, DFL::Mdib::MdibChangeType::ComponentStates);
}

inline void WaitingMdibChangesObserver::onContextChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes)
{
    onChange(mdib, changes, DFL::Mdib::MdibChangeType::ContextStates);
}

inline void WaitingMdibChangesObserver::onMetricChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes)
{
    onChange(mdib, changes, DFL::Mdib::MdibChangeType::MetricStates);
}

inline void WaitingMdibChangesObserver::onOperationChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes)
{
    onChange(mdib, changes, DFL::Mdib::MdibChangeType::OperationStates);
}

inline void WaitingMdibChangesObserver::onSampleArrayMetricChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes)
{
    onChange(mdib, changes, DFL::Mdib::MdibChangeType::WaveformStream);
}

inline bool WaitingMdibChangesObserver::predicateMacthesReceivedChangesNoLock(
        std::function<bool(const NotNull<MdibSharedPtr> &, const NotNull<ConstMdibChangeSetSharedPtr> &)> predicate,
        boost::optional<DFL::Mdib::MdibChangeType> changeType,
        bool trackChanges)
{
    for (auto change = m_changes.begin(); change != m_changes.end(); ++change)
    {
        if (changeType && changeType != change->changeType)
        {
            // Different change type shall not match
            continue;
        }
        if (predicate(change->mdib, change->changes))
        {
            if (!trackChanges)
            {
                m_changes.erase(change);
            }
            return true;
        }
    }
    return false;
}

}
}
}
