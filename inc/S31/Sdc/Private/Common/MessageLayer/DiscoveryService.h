#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapDiscoveryBindingService.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <boost/optional/optional.hpp>

namespace S31::Sdc::Impl
{
class ClientDiscoveryRegistry;
class NetworkInterfaceManager;
class LocalDeviceRegistry;
class DpwsDevice;
class IOutgoingUdpResponder;

/**
 * \brief Implementation of WS-Discovery message dispatching and forwarding to listeners.
 *
 * \ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP DiscoveryService: private DiscoveryBindingService
{
        // gSOAP assign and copy do not work as expected (Coverity findings)
        DFL_NOT_COPYABLE(DiscoveryService)
    public:
        DiscoveryService(struct soap* soapHandle,
                         DFL::NotNull<std::shared_ptr<ClientDiscoveryRegistry>> callback,
                         std::weak_ptr<NetworkInterfaceManager> networkInterfaceManager,
                         DFL::NotNull<std::shared_ptr<LocalDeviceRegistry>> deviceRegistry,
                         std::weak_ptr<IOutgoingUdpResponder> udpResponder,
                         DFL::Chrono::Milliseconds appMaxDelay);

        int dispatch() override;
        int dispatch(struct soap* soapDispatch) override;

    private:
        // sub-classed functions from generated class
        DiscoveryBindingService* copy() override;
        int HelloOp(wsd11__HelloType*) override;
        int ByeOp(wsd11__ByeType*) override;
        int ProbeOp(wsd11__ProbeType*) override;
        int ProbeMatchOp(wsd11__ProbeMatchesType*) override;
        int ResolveOp(wsd11__ResolveType*) override;
        int ResolveMatchOp(wsd11__ResolveMatchesType*) override;

        DFL::NotNull<std::shared_ptr<ClientDiscoveryRegistry>> m_callback;
        std::weak_ptr<NetworkInterfaceManager> m_networkInterfaceManager;
        DFL::NotNull<std::shared_ptr<LocalDeviceRegistry>> m_deviceRegistry;
        std::weak_ptr<IOutgoingUdpResponder> m_udpResponder;
        DFL::Chrono::Milliseconds m_appMaxDelay;

        static boost::optional<std::string> getMessageId(struct soap* soap);

        /// \returns the device' interface or an empty shared_ptr
        std::shared_ptr<DpwsDevice> getDevice(const std::string& eprAddr) const;
        static boost::optional<std::string> getRelatesTo(struct soap *soap);
        static const char* getNonDefaultReplyTo(struct soap* soap);
        static std::string getUdpTargetUri(struct soap *soap);
};

}
