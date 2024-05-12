#pragma once

#include <S31/Safety/Public/Requirements.h>
#include <S31/Sdc/Public/Common/MdibAccess.h>

#include <Framework/Mdib/Public/RemoteMdibAccess.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Default implementation of \ref S31::Sdc::MdibAccess plus satisfaction of \ref DFL::Mdib::RemoteMdibAccess.
 * @ingroup S31SdcClient
 */
class RemoteMdibAccess : public DFL::Mdib::RemoteMdibAccess, public S31::Sdc::MdibAccess
{
    public:
        explicit RemoteMdibAccess(DFL::NotNull<DFL::Mdib::RemoteMdibAccessUniquePtr> mdibAccess);

        RemoteMdibAccess(DFL::NotNull<DFL::Mdib::RemoteMdibAccessUniquePtr> mdibAccess, DFL::NotNull<std::unique_ptr<Safety::Requirements>> safetyRequirements);

        DFL::NotNull<DFL::Mdib::MdibSharedPtr> latestMdib() const override;

        void registerObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;

        void registerSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;

        void unregisterSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;

        DFL::Mdib::WriteResult writeAlertStates(DFL::Mdib::VersionCounter mdibVersion, const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeComponentStates(DFL::Mdib::VersionCounter mdibVersion, const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeContextStates(DFL::Mdib::VersionCounter mdibVersion, const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeMetricStates(DFL::Mdib::VersionCounter mdibVersion, const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeOperationStates(DFL::Mdib::VersionCounter mdibVersion, const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeSampleArrayMetricStates(DFL::Mdib::VersionCounter mdibVersion, const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeDescription(DFL::Mdib::VersionCounter mdibVersion, const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::NotNull<MdibSharedPtr> latestSdcMdib() const override;

    private:
        class Impl;
        std::shared_ptr<Impl> m_impl;
};

}
