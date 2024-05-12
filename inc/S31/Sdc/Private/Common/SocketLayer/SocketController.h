#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Common/INetworkConfigurationObserver.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/Sdc/Private/Common/SocketLayer/Blocker.h>
#include <S31/Sdc/Private/Common/SocketLayer/ISocketSelect.h>
#include <S31/Sdc/Private/Common/SocketLayer/IUdpSocketAccess.h>
#include <S31/Sdc/Private/Common/SocketLayer/QualityOfService.h>
#include <S31/Sdc/Private/Common/SocketLayer/SocketSignal.h>
#include <S31/Sdc/Private/Common/SocketLayer/UdpDatagramRate.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <mutex>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace S31::Sdc::Impl
{

class IPAddress;
class NetworkInterfaceFilter;
class IncomingHttpRequest;
class IWebService;
class SoapContextPool;
class MessageIDHandler;
class SocketStore;

/**
 * @brief Handles BSD socket.
 * @details Global sockets are for WS-Discovery multicast, HTTP, and UDP.
 * @ingroup S31SdcCommonSocket
 */
class S31_CORE_EXPIMP SocketController : public IUdpSocketAccess, public ISocketSelect, public INetworkConfigurationObserver
{
        DFL_NOT_COPYABLE(SocketController)
    public:
        SocketController(
                std::weak_ptr<NetworkInterfaceFilter> networkInterfaces,
                std::weak_ptr<IWebService>            webService,
                std::weak_ptr<SoapContextPool>        soapPool,
#if defined(S31_SUPPORT_DISABLE_SSL)
                bool useSslCommunication,
#endif
                std::uint8_t udpMulticastTtl = CoreConfiguration::DefaultUdpMulticastTtl,
                int          httpPort        = CoreConfiguration::PORTNUMBER_ANY,
                int          udpPort         = CoreConfiguration::PORTNUMBER_ANY);
        ~SocketController() override;

        /**
         * Waits on all network sockets for all DPWS instances.
         */
        IncomingHttpRequestPtrs acceptSocketsWithHttp(DFL::Chrono::Milliseconds timeout, MaxResultCount maxResultCount) override;
        void acceptSocketsWithoutHttp(DFL::Chrono::Milliseconds timeout) override;

        void abortAcceptSockets() override;

        /// @name Used IPv4 ports
        /// @brief Get the used port numbers for receiving HTTP/HTTPS request and UDP responses if binding of socket was successful.
        ///
        /// This should be the port numbers configured in constructor's parameters.
        /// If the port number in the constructor was AnyPort the functions return the actually chosen port numbers.
        /// If an error occurred during socket binding these functions return 0.
        /// @{
        std::uint16_t httpIPv4Port();
        std::uint16_t udpIPv4Port();
        /// @}

        void idleTimeout(DFL::Chrono::Seconds idleTimeout);
        void maxIdleSockets(unsigned int maxIdleSockets);

        /// @brief Implementation of @ref S31::Sdc::Impl::IUdpSocketAccess interface
        std::size_t sendMessageTo(
                std::string_view               message,
                SendToAddress                  destination,
                SendToPort                     port,
                const DFL::Net::Adapter::Info& adapter) override;

        /**
         * @brief Callback for changed network interface.
         * @details (Re-)subscribes to multicast group.
         * To allow plugging network cable in after start or media loss.
         */
        void onChange() override;

    protected:
        /// binds the global network sockets for WS-Discovery and HTTP requests
        void bindSockets();

        void addAbortSocket(SOAP_SOCKET& fd_max, fd_set& set1, fd_set& set2);

        void joinIpv4Multicast();
        void rejoinIpv4Multicast();

        enum class MulticastJoinBehaviour
        {
            LeaveBeforeJoin,
            OnlyJoin
        };
        void joinIpv4Multicast(MulticastJoinBehaviour reJoin);


        enum class WithOrWithoutHttpSockets
        {
            WithHttpIncomingSockets,
            WithoutHttpIncomingSockets
        };

        IncomingHttpRequestPtrs acceptSockets(DFL::Chrono::Milliseconds timeout, WithOrWithoutHttpSockets withOrWithoutHttp, MaxResultCount maxResultCount);

        static void addSocket(SOAP_SOCKET sock, SOAP_SOCKET& fd_max, fd_set& set1, fd_set& set2);

        std::set<std::string> m_remoteMulticastSenderIpAddresses;
        std::mutex m_remoteMulticastSenderIpAddressesMutex;

        bool m_bound = false;
        std::mutex m_bindSocketMutex;
        void closeSockets();
        void bindUdpSockets();
        void bindUdpIpv4DiscoveryMulticastSocket();
        void bindUdpIpv4DiscoveryOutSocket();

        // signaling socket to abort a blocking select() call
        std::shared_ptr<SocketSignal> m_socketSignal;

        SOAP_SOCKET m_httpIPv4Socket;
        std::uint16_t m_httpIPv4Port{0U};
        SOAP_SOCKET m_discoveryIPv4Socket;
        SOAP_SOCKET m_udpIPv4OutSocket;
        std::uint16_t m_udpIPv4Port{0U};
        std::mutex m_udpIPv4OutMutex; ///< mutex for m_udpIPv4OutSocket
        QualityOfService m_httpListenerQos;

        std::weak_ptr<NetworkInterfaceFilter> m_networkInterfaceFilter;
        std::weak_ptr<IWebService> m_webService;
        std::weak_ptr<SoapContextPool> m_soapPool;

        std::unique_ptr<MessageIDHandler> m_recentlyUsedMsgIDs; // for duplicate message detection for SOAP-over-UDP
        std::shared_ptr<SocketStore> m_socketStore;
        std::uint8_t m_udpMulticastTtl;
#if defined(S31_SUPPORT_DISABLE_SSL)
        bool m_useSslCommunication;
#endif
        int m_httpPort;
        int m_udpPort;
    private:

        bool isOwnIpAddress(const std::string& ipAddr) const;
        void checkReceivedMulticastMessage(struct soap* soapHandle);

        void handleUdpSocket(DFL::NotNull<SoapPtr>&& soapUdpPtr);

        /// Returns the socket option SO_EXCLUSIVEADDRUSE (SWindows) or 0 (other OSs)
        static int listeningSockOpt() ;

        UdpDatagramRate m_udpDatagramRate;
        Blocker m_globalTcpListeningSocketBlocker;
};

}
