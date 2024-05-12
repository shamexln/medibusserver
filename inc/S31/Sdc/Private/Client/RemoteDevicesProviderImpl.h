#pragma once

#include <S31/Sdc/Private/Client/ClientStateMachineRegistry.h>
#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/DpwsSubscriptionManager.h>
#include <S31/Sdc/Private/Client/Endpoint/DpwsEndpoint.h>
#include <S31/Sdc/Private/Client/OnlineOfflineServiceLogger.h>
#include <S31/Sdc/Private/Client/StateMachine/ClientStateMachine.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Private/Discovery/IDpwsDiscoverySubject.h>
#include <S31/Sdc/Public/Client/ConnectionPriorityGroup.h>
#include <S31/Sdc/Public/Client/RemoteDevicesProvider.h>
#include <S31/Sdc/Public/Common/InstanceIdentifiersUtil.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/Uri.h>

#include <memory>
#include <mutex>

namespace S31::Sdc::Impl
{

/**
 * @brief Default implementation of \ref RemoteDevicesProvider.
 * @details Maintains connected remote devices
 */
class RemoteDevicesProviderImpl: public RemoteDevicesProvider
{
    public:
        RemoteDevicesProviderImpl(const std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue>& outgoingJobQueue,
                                  const std::weak_ptr<S31::Sdc::Impl::IScheduling>& scheduling,
                                  const std::weak_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject>& discoverySubject,
                                  const std::weak_ptr<S31::Sdc::Impl::DpwsSubscriptionManager>& dpwsSubscriptionManager,
                                  std::set<std::string> supportedUriSchemes,
                                  ConnectionPriorityGroup priorityGroup);

        ~RemoteDevicesProviderImpl() override;

        void connectToRemoteDevice(const EndpointReference& endpointReference) override;
        void connectToRemoteDevice(const EndpointReference& endpointReference,
                                   const MdibSubscriptionTypes& subscriptions) override;
        void connectToRemoteDevice(const EndpointReference& endpointReference, SubscriptionReports reports) override;
        void disconnectFromRemoteDevice(const EndpointReference& endpointReference) override;

        std::shared_ptr<RemoteDevice> waitForRemoteDevice(const EndpointReference& endpointReference, DFL::Chrono::Milliseconds waitTime) override;

        std::shared_ptr<RemoteDevice> remoteDevice(const EndpointReference& endpointReference) override;

        void disconnectFromRemoteDevice(const EndpointReference& endpointReference, const Utils::Error& error);

        void disconnectAll();

        void tearDownConnectedDevices();

        void registerObserver(const std::weak_ptr<RemoteDevicesObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<RemoteDevicesObserver>& observer) override;

    private:
        class Impl;
        DFL::NotNull<std::shared_ptr<Impl>> m_impl;

        std::shared_ptr<OnlineOfflineServiceLogger> m_onlineOfflineServiceLogger;
};

}
