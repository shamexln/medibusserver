#pragma once

#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeTargetType.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/LocalUdpEndpointPort.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeHttpJobResult.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/Scopes.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Utils/Public/Outcome.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/Uri.h>

#include <memory>
#include <string>
#include <vector>

namespace S31::Sdc
{

class EndpointReference;

namespace Impl
{

class IHelloByeObserver;
class IResolveMatchesCallback;
class IProbeMatchesCallback;
class Probe;

/**
 * \brief WS-Discovery client function: hello/bye, probe, resolve (directed)
 *
 * \details
 * For all registered listener a weak reference is stored.
 * Thus the user has to take care, that the callback object will not be destroyed.
 *
 * \ingroup S31SdcWsDiscovery
 */
class IDiscoveryClient:
        public Utils::OutcomeConsumer<IDiscoveryClient, DirectedProbeJobResults>,
        public std::enable_shared_from_this<IDiscoveryClient>
{
    public:
        using HandlerPtr = typename Utils::OutcomeConsumer<IDiscoveryClient, DirectedProbeJobResults>::HandlerPtr;

        virtual ~IDiscoveryClient() = default;

        /**
         * @name Hello/Bye
         *
         * More information about Hello and Bye messages can be found in
         * <a href="http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html#_Toc234231820">WS-Discovery section&nbsp;4</a>.
         */
        ///@{
        /**
         * Method to register for Hello and Bye messages (implicit discovery).
         *
         * It is not required to unregister the listener.
         */
        virtual void registerListener(const std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver>& listener) = 0;

        /**
         * \brief A listener may unregister (but not has to) for Hello and Bye messages.
         *
         * \details Pending Hello and Bye messages may still be delivered in concurrent threads.
         */
        virtual void unregisterListener(const std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver>& listener) = 0;

        ///@}

        /**
         * @name Resolve
         *
         * More information about resolving the transport address of a device can be found in
         * <a href="http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html#_Toc234231838">WS-Discovery section&nbsp;6</a>.
         */
        ///@{
        /// Send a WS-Discovery Resolve message on all allowed multicast interfaces (non-blocking).
        /// \param[in] eprAddress The Endpoint Reference Address (typically a UUID) of the device for which transport addresses (xAddresses) are required.
        /// \param[in] callback Listener that is called asynchronously with the result
        virtual void resolve(
                const S31::Sdc::EndpointReference& eprAddress,
                const std::shared_ptr<S31::Sdc::Impl::IResolveMatchesCallback>& callback) = 0;

        /**
         * The passed listener will be removed for all pending resolve requests.
         */
        virtual void removeResolveListener(const std::shared_ptr<S31::Sdc::Impl::IResolveMatchesCallback>& callback) = 0;

        ///@}

        /**
         * @name Probe
         *
         * More information about probing for devices is available in
         * <a href="http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html#_Toc234231829">WS-Discovery section&nbsp;5</a>.
         */
        ///@{

        /**
         * Initialize a probe (explicit search) for DPWS devices.
         *
         * @param query     The query to restrict the result set
         * @param callback  Listener for the results
         */
        virtual void probe(
                const Probe& query,
                const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& callback) = 0;

        /**
         * Initialize a delayed probe (explicit search) for DPWS devices.
         *
         * @param query     The query to restrict the result set
         * @param callback  Listener for the results
         * @param delay     The duration the messages shall be delayed.
         */
        virtual void delayedProbe(
                const Probe& query,
                const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& callback,
                DFL::Chrono::Milliseconds delay) = 0;

        /**
         * The passed listener will be removed for all pending probes.
         */
        virtual void removeProbeListener(const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& callback) = 0;

        /** Asynchronous directed probe (according to DPWS)
         *
         * \param[in] targetType The type of target, either DiscoveryProxy or target service
         * \param[in] address Address to send directed probe request
         * \param[in] localUdpEndpointPort Local port of UDP unicast endpoint, must be provided when sending to a DiscoveryProxy
         * \param[in] callback Listener that is called asynchronously with the result
         * \param[in] scopes optional WS discovery scopes
         */
        virtual void directedProbe(
                ProbeTargetType targetType,
                const DFL::Net::Uri& address,
                LocalUdpEndpointPort localUdpEndpointPort,
                const CallbackFunction& callback,
                const WSDiscoveryScopes& scopes) = 0;

        ///@}
};

}
}
