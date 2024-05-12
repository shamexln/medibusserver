#pragma once

#include <S31/Safety/Public/Requirements.h>
#include <S31/Sdc/Private/Device/DualChannelFactoryManagerImpl.h>
#include <S31/Sdc/Public/Common/MdibSmartPtrTypes.h>
#include <S31/Sdc/Public/Device/LocalMdibAccess.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibObserver.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Default implementation of \ref S31::Sdc::LocalMdibAccess.
 * @ingroup S31SdcDevice
 */
class LocalMdibAccessImpl: public LocalMdibAccess
{
    public:
        LocalMdibAccessImpl(DFL::NotNull<DFL::Mdib::LocalMdibAccessUniquePtr> mdibAccess,
                            DFL::NotNull<std::unique_ptr<Safety::Requirements>> safetyRequirements);

        DFL::NotNull<DFL::Mdib::MdibSharedPtr> latestMdib() const override;

        void registerObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;

        void registerSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;

        void unregisterSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;

        DFL::Mdib::WriteResult writeAlertStates(const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeComponentStates(const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeContextStates(const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeMetricStates(const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeOperationStates(const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeSampleArrayMetricStates(const DFL::Mdib::MdibChangeSet& changes) override;

        DFL::Mdib::WriteResult writeDescription(const DFL::Mdib::MdibChangeSet& changes) override;

        const DFL::Mdib::MdibConstraints& constraints() const override;

        DFL::NotNull<MdibSharedPtr> latestSdcMdib() const override;

        DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>> dualChannelFactoryManager() const override;

        /**
         * @brief Overwrites the existing safety requirements.
         * @deprecated This is a temporary function that is subject to be removed soon.
         * @todo DGr remove injectSafetyRequirements() function and replace with \c "writeDescription(const DFL::Mdib::MdibChangeSet&, const S31::Sdc::SafetyRequirementsChangeSet&)"
         */
        void injectSafetyRequirements(DFL::NotNull<std::unique_ptr<Safety::Requirements>> safetyRequirements);

    private:
        class Impl;
        std::shared_ptr<Impl> m_impl;
};

}
