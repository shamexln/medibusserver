#pragma once

#include <S31/Sdc/Private/Common/IWebService.h>

#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <memory>
#include <mutex>

namespace S31
{
class CoreConfiguration;
namespace Sdc::Impl
{

class IWebService;
class ClientDiscoveryRegistry;
class NetworkInterfaceManager;
class LocalDeviceRegistry;
class IOutgoingUdpResponder;

/**
 * Dispatches a soap request (from network) to the appropriate sink.
 *
 * \ingroup S31SdcCommonWebServices
 */
class SoapHandler: public IWebService
{
    public:
        SoapHandler(DFL::NotNull<std::shared_ptr<ClientDiscoveryRegistry>> clientDiscoveryRegistry,
                    DFL::NotNull<std::shared_ptr<NetworkInterfaceManager>> networkInterfaceManager,
                    DFL::NotNull<std::shared_ptr<LocalDeviceRegistry>> deviceRegistry,
                    DFL::NotNull<std::shared_ptr<CoreConfiguration>> configuration,
                    std::weak_ptr<IOutgoingUdpResponder> udpResponder);
        ~SoapHandler() override;

        /// dispatch implements the DPWS specific dispatching logic of our DPWS architecture
        /// \returns gSOAP error code without sending SOAP faults.
        /// Caller has to take care of sending SOAP fault messages.
        int dispatch(struct soap* soapHandle) override;

        /**
         * Register an extra web service under a specific directory.
         * E.g., is used by the WS-Eventing client for the event sink.
         */
        void registerForDirectory(const std::string& dirname, const std::shared_ptr<S31::Sdc::Impl::IWebService>& callback);
        void unregisterForDirectory(const std::string& dirname, const std::shared_ptr<S31::Sdc::Impl::IWebService>& callback);

    private:
        int dispatchHttp(struct soap* soapHandle);
        int dispatchUdp(struct soap* soapHandle) const;

        std::multimap<std::string, std::weak_ptr<S31::Sdc::Impl::IWebService>> m_registeredDispatcher;
        std::mutex m_mutex;

        DFL::NotNull<std::shared_ptr<ClientDiscoveryRegistry>> m_clientDiscoveryRegistry;
        DFL::NotNull<std::shared_ptr<NetworkInterfaceManager>> m_networkInterfaceManager;
        DFL::NotNull<std::shared_ptr<LocalDeviceRegistry>> m_deviceRegistry;
        DFL::NotNull<std::shared_ptr<CoreConfiguration>> m_configuration;
        std::weak_ptr<IOutgoingUdpResponder> m_udpResponder;

};

}
}
