#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/SocketLayer/SocketController.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Format/Public/StdErrorCodeIo.h>
#include <Framework/Utils/Public/Error.h>

namespace S31::Sdc::Impl::Test
{

class SocketControllerForTest : public SocketController
{
    public:
        SocketControllerForTest(std::weak_ptr<NetworkInterfaceFilter> networkInterfaces,
                                std::weak_ptr<IWebService> webService,
                                std::weak_ptr<SoapContextPool> soapPool,
#if defined(S31_SUPPORT_DISABLE_SSL)
                                bool useSslCommunication,
#endif
                                std::uint8_t udpMulticastTtl = CoreConfiguration::DefaultUdpMulticastTtl,
                                int httpPort = CoreConfiguration::PORTNUMBER_ANY,
                                int udpPort = CoreConfiguration::PORTNUMBER_ANY)
        :
                SocketController(std::move(networkInterfaces), std::move(webService), std::move(soapPool),
#if defined(S31_SUPPORT_DISABLE_SSL)
                    useSslCommunication,
#endif
                    udpMulticastTtl, httpPort, udpPort)
        {
        }

        SOAP_SOCKET GetDiscoveryIPv4Socket()
        {
            return m_discoveryIPv4Socket;
        }

        bool SetUpUdpSocket()
        {
            bindUdpIpv4DiscoveryMulticastSocket();

            int option;
#ifdef WIN32
            option = IP_HOPLIMIT;
#else
            option = IP_TTL;
#endif
            int on = 1;
            DFL::Error::resetLastSocket();
            int retval = ::setsockopt(m_discoveryIPv4Socket, IPPROTO_IP, option, reinterpret_cast<char*>(&on), sizeof(on));
            if (retval < 0)
            {
                S31_STREAM_ERROR_LOGGER("Test", "setsockopt() failed :", DFL::Error::lastSocket());
                return false;
            }

            return true;
        }

        bool waitForNextDiscoveryMessage(DFL::Chrono::Seconds seconds)
        {
            struct timeval tv = {0, 0};
            fd_set fd;
            FD_ZERO(&fd);  // NOLINT(clang-diagnostic-old-style-cast, clang-analyzer-security.insecureAPI.bzero)

            tv.tv_sec = static_cast<long>(seconds.count());
            SocketUtils::wrapperFD_SET(m_discoveryIPv4Socket, &fd);

            auto retval = select(static_cast<int>(m_discoveryIPv4Socket) + 1, &fd, nullptr, nullptr, &tv);

            return retval == 1;
        }
};

}
