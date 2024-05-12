#pragma once

#include <Framework/Utils/Public/NotNull.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IDiscoveryClient.h>
#include <S31/Sdc/Private/Common/OutcomeConsumerProxy.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/DirectedProbe.h>
#include <S31/S31CoreExImp.h>

#include <mutex>

namespace S31::Sdc::Impl
{

class ClientDiscoveryRegistry;
class IOutgoingSender;
class IOutgoingJobQueue;
class ISoapContextPool;

/**
 * \brief WS-Discovery client implementation of \ref S31::Sdc::Impl::IDiscoveryClient.
 *
 * \ingroup S31SdcWsDiscovery
 */
class S31_CORE_EXPIMP Discovery : public IDiscoveryClient
{
    public:
        Discovery(DFL::NotNull<std::shared_ptr<ClientDiscoveryRegistry>> registry,
                  DFL::NotNull<std::shared_ptr<IOutgoingSender>> outgoingSender,
                  const std::shared_ptr<IOutgoingJobQueue>& outgoingJobQueue,
                  DFL::NotNull<std::shared_ptr<ISoapContextPool>> soapPool);
        ~Discovery() override;

        void registerListener(const std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver>& listener) override;

        void unregisterListener(const std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver>& listener) override;

        void resolve(
                const EndpointReference& eprAddress,
                const std::shared_ptr<IResolveMatchesCallback>& callback) override;

        void removeResolveListener(const std::shared_ptr<S31::Sdc::Impl::IResolveMatchesCallback>& callback) override;

        void probe(const Probe& probe,
                   const std::shared_ptr<IProbeMatchesCallback>& callback) override;

        void delayedProbe(const Probe& probe,
                          const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& callback,
                          DFL::Chrono::Milliseconds delay) override;

        void removeProbeListener(const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& callback) override;

        void directedProbe(ProbeTargetType targetType,
                           const DFL::Net::Uri& discoveryProxyAddress,
                           LocalUdpEndpointPort localUdpEndpointPort,
                           const CallbackFunction& callback,
                           const WSDiscoveryScopes& scopes) override;

    private:
        void removeOldProbeRequests();

        DFL::NotNull<std::shared_ptr<ClientDiscoveryRegistry>> m_registry;
        DFL::NotNull<std::shared_ptr<IOutgoingSender>> m_multicastSender;
        std::weak_ptr<IOutgoingJobQueue> m_outgoingJobQueue;
        DFL::NotNull<std::shared_ptr<ISoapContextPool>> m_soapPool;
        std::vector<std::shared_ptr<DirectedProbe>> m_directedProbeRequests;
        std::mutex m_mutex;
};

}
