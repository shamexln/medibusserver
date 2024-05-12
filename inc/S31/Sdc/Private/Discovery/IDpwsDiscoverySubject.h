#pragma once

#include <S31/Sdc/Private/Discovery/WS-Discovery/Scopes.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/LocalUdpEndpointPort.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeTargetType.h>

#include <Framework/Utils/Public/Uri.h>

#include <boost/optional/optional.hpp>

#include <memory>
#include <string>

namespace DFL::Net
{
class Uri;
}

namespace S31::Sdc
{
class EndpointReference;

namespace Impl
{
class IResolveMatchesCallback;
class IDpwsDiscoveryObserver;

/**
 * \brief Registration interface to observer DpwsDiscovery information.
 *
 * \ingroup S31SdcDiscovery
 */
class IDpwsDiscoverySubject
{
    public:
        virtual ~IDpwsDiscoverySubject() noexcept = default;

        virtual void probeForRemoteDevices(const WSDiscoveryScopes& scopes) = 0;
        virtual void directedProbe(ProbeTargetType targetType, const DFL::Net::Uri& address) = 0;
        virtual void resolveRemoteDevice(const S31::Sdc::EndpointReference& eprAddress, const std::shared_ptr<Sdc::Impl::IResolveMatchesCallback>& callback) = 0;

        virtual void registerDiscoveryObserver(std::shared_ptr<IDpwsDiscoveryObserver> rec) = 0;
        virtual void unregisterDiscoveryObserver(std::shared_ptr<IDpwsDiscoveryObserver> rec) = 0;

        virtual const boost::optional<DFL::Net::Uri>& discoveryProxyAddress() const = 0;
        virtual LocalUdpEndpointPort localUdpEndpointPort() const = 0;
};

}
}
