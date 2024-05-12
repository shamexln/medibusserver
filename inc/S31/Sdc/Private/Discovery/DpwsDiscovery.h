#pragma once

#include <S31/Sdc/Private/Discovery/IDpwsDiscoverySubject.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IDiscoveryClient.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/LocalUdpEndpointPort.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/QName.h>

#include <memory>
#include <mutex>

namespace S31::Sdc::Impl
{
class INetworkConfigurationSubject;
class INetworkConfigurationObserver;
class IScheduling;
class IDpwsDiscoveryObserver;

struct DeviceDiscoveryTypeTag{};

/**
 * @brief Defines a WS-Discovery type.
 * @details
 * To be used as default value in any Probe.
 *
 * @ingroup S31SdcDiscovery
 */
using DiscoveryType = DFL::StrongTypedef<DFL::QName, DeviceDiscoveryTypeTag>;

/**
 * @brief Main processor for WS-Discovery handling in S31.Core.
 * @details
 * It combines WS-Discovery handling as well as network configuration
 * changes and simplifies the interface to just found and lost devices
 * (@ref S31::Sdc::Impl::IDpwsDiscoveryObserver).
 *
 * This needs a @ref IScheduling to be able to do periodic probes in case a
 * discovery proxy is used.
 *
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP DpwsDiscovery : public IDpwsDiscoverySubject
{
    public:
        DpwsDiscovery(DFL::NotNull<std::shared_ptr<Sdc::Impl::IDiscoveryClient>> discovery,
                      DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::INetworkConfigurationSubject>> netConfSubject,
                      std::shared_ptr<Sdc::Impl::IScheduling> scheduling,
                      DiscoveryType discoveryType,
                      const boost::optional<DFL::Net::Uri>& discoveryProxyAddress, // NOLINT(modernize-pass-by-value)
                      DFL::Chrono::Seconds periodicProbeIntervalForDiscoveryProxy,
                      LocalUdpEndpointPort localUdpEndpointPort);

        void start();
        void stop();

        void probeForRemoteDevices(const WSDiscoveryScopes& scopes) override;
        void directedProbe(ProbeTargetType targetType, const DFL::Net::Uri& address) override;
        void resolveRemoteDevice(const S31::Sdc::EndpointReference& eprAddress, const std::shared_ptr<Sdc::Impl::IResolveMatchesCallback>& callback) override;

        void registerDiscoveryObserver(std::shared_ptr<IDpwsDiscoveryObserver> rec) override;
        void unregisterDiscoveryObserver(std::shared_ptr<IDpwsDiscoveryObserver> rec) override;

        const boost::optional<DFL::Net::Uri>& discoveryProxyAddress() const override;
        LocalUdpEndpointPort localUdpEndpointPort() const override;

    private:
        class DpwsDiscoveryImpl;
        class NetConfChangeObserver;

        std::mutex m_mutex;
        bool m_running = false;
        DFL::NotNull<std::shared_ptr<DpwsDiscoveryImpl>> m_impl;
        DFL::NotNull<std::shared_ptr<Sdc::Impl::IDiscoveryClient>> m_discoveryClient;
        DFL::NotNull<std::shared_ptr<Sdc::Impl::INetworkConfigurationSubject>> m_networkConfigurationSubject;
        std::shared_ptr<Sdc::Impl::INetworkConfigurationObserver> m_networkConfigurationObserver;
        std::shared_ptr<Sdc::Impl::IScheduling> m_scheduling;
};

}
