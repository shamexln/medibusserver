#pragma once

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Uri.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IResolveMatchesCallback.h>
#include <S31/Sdc/Private/Discovery/IDpwsDiscoverySubject.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <boost/optional/optional.hpp>
#include <memory>

namespace S31::Sdc::Impl::Test
{

/**
 * Helper class for the tracking of dpws device discovery
 */
class DpwsDiscoverySpy: public IDpwsDiscoverySubject
{
    public:
        void registerDiscoveryObserver(std::shared_ptr<IDpwsDiscoveryObserver> rec) override;

        void unregisterDiscoveryObserver(std::shared_ptr<IDpwsDiscoveryObserver> rec) override;

        void probeForRemoteDevices(const WSDiscoveryScopes& scopes) override;

        void directedProbe(ProbeTargetType targetType, const DFL::Net::Uri& address) override;

        std::shared_ptr<IDpwsDiscoveryObserver> getDiscoveryObserver() const;

        void resolveRemoteDevice(const S31::Sdc::EndpointReference& eprAddress, const std::shared_ptr<Sdc::Impl::IResolveMatchesCallback>& callback) override;

        const boost::optional<DFL::Net::Uri>& discoveryProxyAddress() const override;

        LocalUdpEndpointPort localUdpEndpointPort() const override;

        bool hasResolveTriggered() const;

        DFL::Locale::Utf8 getResolveUrn() const;

        void resetResults();

        const std::shared_ptr<Sdc::Impl::IResolveMatchesCallback>& resolveMatchesCallback();

        void injectDiscoveryProxy(const DFL::Net::Uri& address);

    private:
        std::shared_ptr<IDpwsDiscoveryObserver> m_observer;
        std::shared_ptr<Sdc::Impl::IResolveMatchesCallback> m_resolveCallback;
        bool m_triggeredResolve = false;
        DFL::Locale::Utf8 m_resolveUrn;
        boost::optional<DFL::Net::Uri> m_discoveryProxy;
};

}
