#pragma once

#include <S31/Localization/Public/Device/LocalizedTextStore.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/SubdividedMdibObserver.h>

namespace S31::Sdc::Impl
{
class ILocalEventing;

/**
 * Observes Mdib for WS-Discovery meta data changes and updates the local device
 *
 * \ingroup S31SdcDevice
 */
class MetaDataChangesObserver: public DFL::Mdib::SubdividedMdibObserver
{
    public:
        explicit MetaDataChangesObserver(const DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::ILocalEventing>>& localEventing,
                                         const DFL::Mdib::Mdib& initialMdib,
                                         std::shared_ptr<Localization::Device::LocalizedTextStore> textStore);

        void onDescriptionChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onContextChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;

        inline void onAlertChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& /*changes*/) override
        {
        }

        // onComponentChange only contains state information. Mds/MetaData is contained in the descriptor.
        inline void onComponentChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& /*changes*/) override
        {
        }

        inline void onMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& /*changes*/) override
        {
        }

        inline void onOperationChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& /*changes*/) override
        {
        }

        inline void onSampleArrayMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& /*changes*/) override
        {
        }

    private:
        std::weak_ptr<S31::Sdc::Impl::ILocalEventing> m_localEventing;
        std::shared_ptr<Localization::Device::LocalizedTextStore> m_localizedTextStore;

        void updateDpwsDiscoveryScopes(const DFL::Mdib::Mdib& mdib, const DFL::Mdib::MdibChangeSet& changes) const;
};

}
