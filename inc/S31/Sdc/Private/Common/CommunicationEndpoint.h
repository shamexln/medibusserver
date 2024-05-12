#pragma once

#include <S31/Sdc/S31Only/DeviceDiscoveryTypes.h>
#include <S31/Sdc/Public/Common/CommunicationEndpoint.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/LocalUdpEndpointPort.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Uri.h>

#include <memory>
#include <string>

namespace S31
{
class CoreConfiguration;

namespace AsioDispatch
{
class Dispatcher;
}

namespace Sdc::Impl
{
class HttpClientRegistry;
class IDiscoveryClient;
class IEventingClient;
class DpwsDevice;
class INetworkConfigurationSubject;
class IScheduling;
class ISoapContextPool;
class IOutgoingJobQueue;

/**
 * @brief Entry point to create a DPWS device.
 * @details One instance of this class is required to create DPWS devices or clients.
 * Furthermore it supports infrastructural parts such as network configuration (interfaces to use, IP address changes, ...).
 *
 * After instantiation it is possible to add one or more so called @ref S31::Sdc::Impl::HostedService "HostedServices" to the DPWS device (the HostingService).
 * For each HostedService it is possible to create custom eventing plugin (e.g. for SDC @ref S31::Sdc::Impl::WSEventingPlugin) for event propagation.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP CommunicationEndpoint: public Sdc::CommunicationEndpoint
{
    public:
        CommunicationEndpoint(
                DFL::NotNull<std::shared_ptr<CoreConfiguration>>              config,
                DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>> asioDispatcher);
        ~CommunicationEndpoint() override;

        /**
         * @name Device
         */
        ///@{

        /**
         * @brief Creates a new DPWS device.
         * @param uuid The UUID for the new DPWS device, e.g., urn:uuid:39b98c25-e49c-4f34-91e5-acbdbce84bb1
         * @param initialDpwsMetadataVersion Initial WS-Discovery metadata version the device uses to start.
         * @param discoveryTypes specific discovery types for the Device, e.g. SDC or ADT Service
         */
        DFL::NotNull<std::shared_ptr<DpwsDevice>> createDeviceWithUUID(const std::string& uuid, S31::Sdc::MetadataVersion initialDpwsMetadataVersion, DeviceDiscoveryTypes discoveryTypes);

        /**
         * @brief Removes the specified DPWS device.
         */
        void removeDeviceWithUUID(const std::string& uuid);

        ///@}


        /**
         * @name Client
         */
        ///@{

        /**
         * @brief Provides the WS-Discovery client instance of this communication endpoint.
         */
        DFL::NotNull<std::shared_ptr<IDiscoveryClient>> discoveryClient() const;

        /**
         * @brief Provides the WS-Eventing client instance of this communication endpoint.
         */
        DFL::NotNull<std::shared_ptr<IEventingClient>> eventingClient() const;

        /**
         * @brief Provides the Mdib job queue processor.
         */
        DFL::NotNull<std::shared_ptr<IOutgoingJobQueue>> outgoingJobQueue() const;

        ///@}

        /**
         * @name Infrastructure
         */
        ///@{

        DFL::NotNull<std::shared_ptr<INetworkConfigurationSubject>> networkConfigurationListener() const;

        DFL::NotNull<std::shared_ptr<IScheduling>> scheduling() const;
        
        DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>> dispatcher() const;

        DFL::NotNull<std::shared_ptr<ISoapContextPool>> soapContextPool() const;

        DFL::NotNull<std::shared_ptr<HttpClientRegistry>> httpClientRegistry() const;

        boost::optional<DFL::Net::Uri> discoveryProxyAddress() const;

        ///@}

        /**
         * @brief Provide the unicast UDP port at which discovery messages are processed.
         * @details For communication with a discovery proxy, messages must include a UDP
         * endpoint address at which Hello and Resolve messages are processed.
         */
        LocalUdpEndpointPort udpIPv4DiscoveryPort() const;

        void registerObserver(const std::weak_ptr<SdcMessageObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<SdcMessageObserver>& observer) override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
};

}
}
