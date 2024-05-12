#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>
#include <Framework/Mdib/Private/MdibAccessHelper.h>
#include <Framework/Mdib/Private/PublisherHelper.h>
#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Mdib/Public/RemoteMdibAccess.h>
#include <Framework/Mdib/Public/SubdividedMdibObserver.h>
#include <Framework/Mdib/Public/WriteResult.h>

#include <Framework/Utils/Public/NotNull.h>

#include <mutex>
#include <optional>

namespace DFL::Mdib::Impl
{

/**
 * @brief MDIB access implementation that meets the \ref LocalMdibAccess, \ref RemoteMdibAccess, and DFL::Mdib::MdibAccess interface.
 * @ingroup Mdib
 */
template<class T_MdibDetails>
class MdibAccessImpl: public LocalMdibAccess, public RemoteMdibAccess
{
    public:
        MdibAccessImpl(const MdibTreeStore& initialMdib,
                       const MdibVersion& initialMdibVersion,
                       std::optional<Timestamp> timestamp,
                       const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
                       const boost::optional<MdStateVersion>& mdStateVersion,
                       MdibConstraints constraints,
                       PlugIn::Checkers&& checkers,
                       PlugIn::Modifiers&& modifiers);

        NotNull<MdibSharedPtr> latestMdib() const override;

        DFL::Mdib::WriteResult writeAlertStates(const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeComponentStates(const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeContextStates(const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeMetricStates(const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeOperationStates(const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeSampleArrayMetricStates(const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeDescription(const MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeAlertStates(VersionCounter mdibVersion, const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeComponentStates(VersionCounter mdibVersion, const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeContextStates(VersionCounter mdibVersion, const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeMetricStates(VersionCounter mdibVersion, const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeOperationStates(VersionCounter mdibVersion, const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeSampleArrayMetricStates(VersionCounter mdibVersion, const MdibChangeSet& changes) override;
        DFL::Mdib::WriteResult writeDescription(VersionCounter mdibVersion, const MdibChangeSet& changes) override;

        void registerObserver(const std::weak_ptr<MdibObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<MdibObserver>& observer) override;
        void registerSubdividedObserver(const std::weak_ptr<SubdividedMdibObserver>& observer) override;
        void unregisterSubdividedObserver(const std::weak_ptr<SubdividedMdibObserver>& observer) override;

        const MdibConstraints& constraints() const override;

    private:
        using TreeStoreResult = WriteResult;

        // Plug-ins
        PlugIn::Checkers m_changeSetCheckers;
        PlugIn::Modifiers m_changeSetModifiers;

        MdibConstraints m_constraints;

        /// @brief Lock is assigned during the whole MDIB write process.
        mutable std::mutex m_treeStoreMutex;
        MdibTreeStoreBuilder<T_MdibDetails> m_treeStoreBuilder;

        /// @brief Is hold as a member to not require access to m_mdib during write process.
        MdibVersion m_mdibVersion;
        boost::optional<MdDescriptionVersion> m_mdDescriptionVersion;
        boost::optional<MdStateVersion> m_mdStateVersion;


        /**
         * @brief Lock is only hold while atomically write and read (comprises no further lines of code).
         */
        class MutexedMdib
        {
        public:
            MutexedMdib(const Impl::MdibTreeStore& treeStore,
                        const MdibVersion& mdibVersion,
                        std::optional<Timestamp> timestamp,
                        const boost::optional<MdDescriptionVersion>&
                            mdDescriptionVersion,
                        const boost::optional<MdStateVersion>& mdStateVersion);
            NotNull<MdibSharedPtr> get() const;
            NotNull<MdibSharedPtr> set(
                const Impl::MdibTreeStore& treeStore,
                const MdibVersion& mdibVersion,
                std::optional<Timestamp> timestamp,
                const boost::optional<MdDescriptionVersion>&
                    mdDescriptionVersion,
                const boost::optional<MdStateVersion>& mdStateVersion);

        private:
            mutable std::mutex m_mutex;
            NotNull<MdibSharedPtr> m_mdib;
        } m_mutexedMdib;

        PublisherHelper m_publisherHelper;

        PlugIn::ModifiersAndCheckersResult applyModifiersAndCheckers(
            MdibChangeType changeType,
            const MdibChangeSet& changes,
            std::optional<Timestamp> time) const;

        DFL::Mdib::WriteResult writeAlertStates(
            std::unique_lock<std::mutex>& lock,
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion,
            const MdibChangeSet& changes);
        DFL::Mdib::WriteResult writeComponentStates(
            std::unique_lock<std::mutex>& lock,
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion,
            const MdibChangeSet& changes);
        DFL::Mdib::WriteResult writeContextStates(
            std::unique_lock<std::mutex>& lock,
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion,
            const MdibChangeSet& changes);
        DFL::Mdib::WriteResult writeMetricStates(
            std::unique_lock<std::mutex>& lock,
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion,
            const MdibChangeSet& changes);
        DFL::Mdib::WriteResult writeSampleArrayMetricStates(
            std::unique_lock<std::mutex>& lock,
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion,
            const MdibChangeSet& changes);
        DFL::Mdib::WriteResult writeOperationStates(
            std::unique_lock<std::mutex>& lock,
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion,
            const MdibChangeSet& changes);
        DFL::Mdib::WriteResult writeDescription(
            std::unique_lock<std::mutex>& lock,
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion,
            const MdibChangeSet& changes);

        void publishStateChanges(NotificationCall subdividedNotify,
                                 std::unique_lock<std::mutex>& lock,
                                 const NotNull<MdibSharedPtr>& mdib,
                                 const NotNull<ConstMdibChangeSetSharedPtr>& changes,
                                 MdibChangeType);

        void publishDescriptorChanges(std::unique_lock<std::mutex>& lock,
                                      const NotNull<MdibSharedPtr>& mdib,
                                      const NotNull<ConstMdibChangeSetSharedPtr>& changes);

        NotNull<MdibSharedPtr> setMdibTreeStoreInMutexedMdib(
            const MdibVersion& mdibVersion,
            std::optional<Timestamp> timestamp,
            const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
            const boost::optional<MdStateVersion>& mdStateVersion);
};

}
