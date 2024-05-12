#pragma once

#include <S31/Sdc/Private/Common/ISoapContextPool.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeTargetType.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/Scopes.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <boost/optional/optional.hpp>

#include <memory>
#include <optional>
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
using DeviceTypes = QNameList;
using DeviceScopes = std::vector<std::string>;
using XAddrs = std::vector<DFL::Net::Uri>;
using Uuid = std::string;
using UdpEndpoint = boost::optional<DFL::Net::Uri>;

struct AppSequenceMessageNumberTag;

/**
 * @brief The MessageNumber from WS-Discovery's AppSequence.
 *
 * WS-Discovery 1.1:
 * > Identifies a message within the context of a sequence identifier and an instance identifier.
 * > MUST be incremented by a positive value (>= 1) for each message sent. Transport-level retransmission MUST preserve this value.
 *
 * @ingroup S31SdcDevice
 */
using AppSequenceMessageNumber = DFL::StrongTypedef<std::uint32_t, struct AppSequenceMessageNumberTag, DFL::Skill::TotallyOrdered, DFL::Skill::Incrementable, DFL::Skill::Streamable>;

struct DeviceInformation
{
    DeviceTypes types;
    DeviceScopes scopes;
    XAddrs xaddrs;
    MetadataVersion metadataversion;
    Uuid uuid;
    AppSequenceMessageNumber appSequence;
    UdpEndpoint udpEndpoint;
};

using DiscoveryProxyAddress = DFL::Net::Uri;

/**
 * @brief Creates various WS-Discovery messages (like @c Hello and @c Bye).
 * @details
 * Depending if unicast or multicast messages are sent, the messages carry different information.
 *
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP CreateDiscoveryMessages
{
    public:

        /**
         * @brief Convenience function to generate unicast hello messages.
         * @param soapPool generates raw soap messages.
         * @param deviceInformation tuple of data to populate the message.
         * @param discoveryProxyAddress contains the address of the discovery proxy.
         * @return string of the generated soap message.
         */
        static std::string unicastHelloMessage(
                const std::weak_ptr<ISoapContextPool>& soapPool,
                const DeviceInformation& deviceInformation,
                const DiscoveryProxyAddress& discoveryProxyAddress);

        /**
         * @brief Convenience function to generate multicast hello messages.
         * @param soapPool generates raw soap messages
         * @param deviceInformation tuple of data to populate the message.
         * @return string of the generated soap message.
         */
        static std::string multicastHelloMessage(
                const std::weak_ptr<ISoapContextPool>& soapPool,
                const DeviceInformation& deviceInformation);

        /**
         * @brief Convenience function to generate appropriate unicast bye messages.
         * @param soapPool generates raw soap messages.
         * @param deviceInformation tuple of data to populate the message.
         * @param discoveryProxyAddress contains the address of the discovery proxy.
         * @return string of the generated soap message
         */
        static std::string unicastByeMessage(
                const std::weak_ptr<ISoapContextPool>& soapPool,
                const DeviceInformation& deviceInformation,
                const DiscoveryProxyAddress& discoveryProxyAddress);

        /**
         * @brief Convenience function to generate appropriate multicast bye messages.
         * @param soapPool generates raw soap messages.
         * @param deviceInformation tuple of data to populate the message.
         * @return string of the generated soap message
         */
        static std::string multicastByeMessage(
                const std::weak_ptr<ISoapContextPool>& soapPool,
                const DeviceInformation& deviceInformation);
        /**
         * @brief Convenience function to generate appropriate unicast probe messages.
         * @param soapPool generates raw soap messages.
         * @param targetType Type of target being probed, either a DiscoveryProxy or a TargetService (device).
         * @param address Contains the address of the target
         * @param udpEndpointAddress The UDP unicast endpoint where a DiscoveryProxy will send hello messages.
         * @param scopes Optional discovery scopes.
         * @return string of the generated soap message
         */
        static std::string unicastProbeMessage(const std::weak_ptr<ISoapContextPool>& soapPool,
                ProbeTargetType targetType,
                const DFL::Net::Uri& address,
                const boost::optional<DFL::Net::Uri>& udpEndpointAddress,
                const WSDiscoveryScopes& scopes);

        /**
         * @brief Convenience function to generate appropriate unicast probe messages.
         * @param soapHandle gSoap soap handle.
         * @param targetType Type of target being probed, either a DiscoveryProxy or a TargetService (device).
         * @param address Contains the address of the target
         * @param udpEndpointAddress The UDP unicast endpoint where a DiscoveryProxy will send hello messages.
         * @param scopes Optional discovery scopes.
         * @return string of the generated soap message
         */
        static std::string unicastProbeMessage(DFL::NotNull<struct soap*> soapHandle,
                ProbeTargetType targetType,
                const DFL::Net::Uri& address,
                const boost::optional<DFL::Net::Uri>& udpEndpointAddress,
                const WSDiscoveryScopes& scopes);

       /**
         * @brief Convenience function to generate appropriate unicast resolve messages.
         * @param soapHandle gSoap soap handle.
         * @param targetEpr Endpoint reference of target to resolve.
         * @param discoveryProxyUri Contains the address of the DiscoveryProxy.
         * @param udpEndpointAddress The UDP unicast endpoint where a DiscoveryProxy will send hello messages.
         * @return string of the generated soap message
         */
        static std::string unicastResolveMessage(
                DFL::NotNull<struct soap*> soapHandle,
                const S31::Sdc::EndpointReference& targetEpr,
                const DFL::Net::Uri& discoveryProxyUri,
                const boost::optional<DFL::Net::Uri>& udpEndpointAddress);

        /**
         * @brief Set the AppSequence in the SOAP header.
         * @details
         * This defined in WS-Discovery.
         *
         * > MUST be included to allow ordering discovery messages from a Target Service...
         * > SHOULD be omitted in a managed mode.
         */
        static void setAppSequence(
            struct soap* soapHandle,
            S31::Sdc::MetadataVersion metadataVersion,
            AppSequenceMessageNumber messageNumber);

};

}
}
