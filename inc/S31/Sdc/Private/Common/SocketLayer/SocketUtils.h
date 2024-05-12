#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Common/SocketLayer/SocketEndpoint.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceFilter.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Net/Public/Adapter/Infos.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Constant for invalid socket handles.
 *
 * \ingroup S31SdcCommonSocket
 */
const SOAP_SOCKET INVALID_SOCKET_CONST = static_cast<SOAP_SOCKET>(-1);

/**
 * @brief Helper function for network sockets.
 *
 * \ingroup S31SdcCommonSocket
 */
class S31_CORE_EXPIMP SocketUtils
{

    public:

        /**
         * Joins the given multicast group on the socket.
         * \returns the setsockopt return value for joining the multicast group
         */
        static int joinMulticastGroup(SOAP_SOCKET sockfd, const struct sockaddr_storage* addr,
                                      const DFL::Net::Adapter::Infos& interfaces);

        static int leaveMulticastGroup(SOAP_SOCKET sockfd, const struct sockaddr_storage* addr,
                                       const DFL::Net::Adapter::Infos& interfaces);

        /**
         * Set interface index for outgoing multicast messages.
         */
        static int setIPv4MulticastInterface(
                SOAP_SOCKET ipv4Socket, DFL::Net::Adapter::Info::Index interfaceIndex, const std::string& ipAddress);

        /**
         * Sets the socket option to receive interface information.
         *
         * \returns the setsockopt return value
         */
        static int enableIPv4ReceiveInterfaceInformation(SOAP_SOCKET ipv4Socket);

        /**
         * @brief Set the IP multicast TTL value
         * @param socket Socket to use for set socket option.
         * @param udpMulticastTtl Multicast TTL value (255 is maximum)
         * @return On success, zero is returned.
         */
        static int setMulticastTtl(SOAP_SOCKET socket, std::uint8_t udpMulticastTtl);

        static std::uint8_t getMulticastTtl(SOAP_SOCKET socket);

        static int activateTtlRetrieval(SOAP_SOCKET socket);

        static SocketEndpoint getCurrentLocalAddressOfSocket(SOAP_SOCKET sockfd);
        static SocketEndpoint getRemoteAddressOfSocket(SOAP_SOCKET sockfd);
        static SocketEndpoint getAddressOfSockAddr(const struct sockaddr* addr, socklen_t addrlen, std::string_view callContext);

        static void wrapperFD_SET(SOAP_SOCKET socket, fd_set* fd);

        /**
         * @brief Closes a socket with OS specific function.
         */
        static int closeSocket(SOAP_SOCKET socket);
};

inline void SocketUtils::wrapperFD_SET(SOAP_SOCKET socket, fd_set* fd)
{
    FD_SET(socket, fd); // NOLINT(clang-diagnostic-old-style-cast)
}

}
