#pragma once

#include <S31/Base/S31Only/NtStringView.h>

#include <Framework/Net/Public/Adapter/Infos.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <cstdint>
#include <string_view>

namespace S31::Sdc::Impl
{
struct SendToAddressTag {};
using SendToAddress = DFL::StrongTypedef<NtStringView, SendToAddressTag, DFL::Skill::Streamable>;

struct SendToPortTag {};
using SendToPort = DFL::StrongTypedef<std::uint16_t, SendToPortTag, DFL::Skill::Streamable>;

/**
 * Access to UDP socket for outgoing WS-Discovery messages.
 *
 * @ingroup S31SdcCommonSocket
 */
class IUdpSocketAccess
{
    public:
        /**
         * @brief Send a message on the multicast outbound Udp socket.
         * @param message View of the message to send.
         * @param destination The Ip address of the destination
         * @param port The Udp port of the destination.
         * @param adapter The local network adapter from which to send.
         * @return Number of bytes written to the socket.
         */
        virtual std::size_t sendMessageTo(
                std::string_view               message,
                SendToAddress                  destination,
                SendToPort                     port,
                const DFL::Net::Adapter::Info& adapter) = 0;

        /// @brief Default destructor
        virtual ~IUdpSocketAccess() noexcept = default;
};

}
