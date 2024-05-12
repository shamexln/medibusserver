#pragma once

#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/DpwsSubscriptionManager.h>
#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Public/Client/Client.h>
#include <S31/Sdc/Public/Client/ConnectionPriorityGroup.h>
#include <S31/Sdc/Public/Common/IDispatcher.h>
#include <S31/Sdc/Public/Discovery/DiscoveryObserver.h>

namespace S31::Sdc::Impl
{
class CommunicationEndpoint;
class RemoteDevicesProviderImpl;
class IDpwsDiscoverySubject;
class DiscoveryProvider;

#if defined(S31_SUPPORT_DISABLE_SSL)
/**
 * @brief Strong typedef to disable SSL usage.
 * @ingroup S31SdcClient
 */
typedef DFL::StrongTypedef<bool, struct DisableSslUsageTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable> DisableSslUsage;
#endif

/**
 * @copydoc S31::Sdc::Client
 * @ingroup S31SdcClient
 */
class BicepsClient: public Client
{
    public:
        BicepsClient(DFL::NotNull<std::shared_ptr<IDispatcher>> dispatcher,
                     DFL::NotNull<std::shared_ptr<CommunicationEndpoint>> communicationEndpoint,
                     DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::DiscoveryProvider>> discoveryProvider,
#if defined(S31_SUPPORT_DISABLE_SSL)
                     DisableSslUsage disableSslUsage,
#endif
                     ConnectionPriorityGroup priorityGroup);

        ~BicepsClient() noexcept override;

        std::shared_ptr<Sdc::DiscoveryProvider> discoveryProvider() const override;

        std::shared_ptr<RemoteDevicesProvider> remoteDevicesProvider() const override;

    private:
        void init();

        DFL::NotNull<std::shared_ptr<CommunicationEndpoint>> m_communicationEndpoint;
        DFL::NotNull<std::shared_ptr<IDispatcher>> m_dispatcher;
        std::shared_ptr<S31::Sdc::DiscoveryProvider> m_discoveryProvider;
        std::shared_ptr<DpwsSubscriptionManager> m_dpwsSubscriptionManager;
        std::shared_ptr<RemoteDevicesProviderImpl> m_remoteDevicesProvider;
};

}
