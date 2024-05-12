#pragma once

#include <S31/Sdc/Private/Client/DsoapClient/Jobs/GetMdibJob.h>
#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/DpwsSubscriptionManager.h>
#include <S31/Sdc/Private/Client/Endpoint/DpwsEndpoint.h>
#include <S31/Sdc/Private/Client/PortTypeExecutors.h>
#include <S31/Sdc/Private/Client/StateMachine/ClientStateMachine.h>
#include <S31/Sdc/Private/Client/StateMachine/GetContextStatesJob.h>
#include <S31/Sdc/Private/Client/WS-Eventing/IEventingClient.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/InstanceIdentifiersUtil.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
namespace Endpoint
{
class DpwsEndpoint;
}
namespace Csm
{

/**
 * @brief Factory to create jobs for the client state machine.
 * @details \note Opens the implementation for black box testing.
 * @ingroup S31SdcClient
 */
class JobFactory
{
    public:
        virtual ~JobFactory() = default;

        virtual DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> createGetMdibJob(const std::string& targetAddress,
                                                                                            const S31::Utils::OutcomeTypes::HandlerPtr<S31::Sdc::Impl::GetMdibJobResult>& handler,
                                                                                            const EndpointReference& eprAddress) const;

        virtual DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> createGetContextStatesJob(const std::string& targetAddress,
                                                                                                     const S31::Utils::OutcomeTypes::HandlerPtr<GetContextStatesJobResult>& handler) const;
};

/**
 * @brief Default implementation of the client state machine.
 * @ingroup S31SdcClient
 */
class ClientStateMachineImpl: public ClientStateMachine
{
    public:
        ClientStateMachineImpl(const ClientStateMachineImpl&) = delete;
        ClientStateMachineImpl(ClientStateMachineImpl&&) = delete;
        ClientStateMachineImpl& operator=(const ClientStateMachineImpl&) = delete;
        ClientStateMachineImpl& operator=(ClientStateMachineImpl&&) = delete;

        /**
         * @brief Constructor with default job factory.
         * @param endpointReference A verified endpoint reference the client state machine represents
         * @param metadata Device metadata that is transformed to DpwsMetadata and being available to users
         * @param credentials Credential information retrieved from the peer (RemoteDevice)
         * @param executors Executors that are used to access the device from remote.
         * @param dpwsEndpoint Ownership assignment of the \ref S31::Sdc::Impl::Endpoint::DpwsEndpoint that spans the context for remote access
         * @param expectedLocation Sets the expected associated location that is taken as a prerequisite for early exit.
         * @param scheduling Scheduling component to schedule notification jobs.
         * @param dpwsSubscriptionManager Subscription manager to start and stop subscriptions.
         *
         */
        ClientStateMachineImpl(const EndpointReference& endpointReference,
                               const DeviceMetadata& metadata,
                               const S31::Nomenclature::Credentials& credentials,
                               const std::map<ServiceId, Endpoint::HostedServiceExecutor>& executors,
                               DFL::NotNull<std::shared_ptr<Endpoint::DpwsEndpoint>> dpwsEndpoint,
                               const boost::optional<DFL::Mdib::InstanceIdentifier>& expectedLocation,
                               std::weak_ptr<S31::Sdc::Impl::IScheduling> scheduling,
                               std::weak_ptr<S31::Sdc::Impl::DpwsSubscriptionManager> dpwsSubscriptionManager);

        /**
         * @brief Constructor with custom job factory.
         * @param endpointReference A verified endpoint reference the client state machine represents
         * @param metadata Device metadata that is transformed to DpwsMetadata and being available to users
         * @param credentials Credential information retrieved from the peer (RemoteDevice)
         * @param executors Executors that are used to access the device from remote.
         * @param dpwsEndpoint Ownership assignment of the \ref S31::Sdc::Impl::Endpoint::DpwsEndpoint that spans the context for remote access
         * @param expectedLocation Sets the expected associated location that is taken as a prerequisite for early exit.
         * @param scheduling Scheduling component to schedule notification jobs.
         * @param dpwsSubscriptionManager Subscription manager to start and stop subscriptions.
         * @param jobFactory Custom job factory.
         */
        ClientStateMachineImpl(const EndpointReference& endpointReference,
                               const DeviceMetadata& metadata,
                               const S31::Nomenclature::Credentials& credentials,
                               const std::map<ServiceId, Endpoint::HostedServiceExecutor>& executors,
                               DFL::NotNull<std::shared_ptr<Endpoint::DpwsEndpoint>> dpwsEndpoint,
                               const boost::optional<DFL::Mdib::InstanceIdentifier>& expectedLocation,
                               std::weak_ptr<S31::Sdc::Impl::IScheduling> scheduling,
                               std::weak_ptr<S31::Sdc::Impl::DpwsSubscriptionManager> dpwsSubscriptionManager,
                               DFL::NotNull<std::unique_ptr<JobFactory>> jobFactory);

        ~ClientStateMachineImpl() override = default;

        void connect(const SoapActions& mdibChangeReports) override;

        void disconnect(const Utils::Error& error) override;

        void validate() override;

        void handleError(const Utils::Error& error) override;

        void registerObserver(const std::weak_ptr<ClientStateMachineObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<ClientStateMachineObserver>& observer) override;

        std::shared_ptr<RemoteDevice> remoteDevice() const override;

    private:
        class Impl;
        std::shared_ptr<Impl> m_impl;

        // ClientStateMachine is owner of a DPWS endpoint, hence the DpwsEndpoint
        // instance cannot outlive the client state machine
        DFL::NotNull<std::shared_ptr<Endpoint::DpwsEndpoint>> m_dpwsEndpoint;
};

}
}
