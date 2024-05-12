#pragma once

#include <Framework/Chrono/Public/Duration.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface for sending a UDP (response) message to a given endpoint.
 * @ingroup S31SdcCommonWebServices
 */
class IOutgoingUdpResponder
{
    public:
        virtual ~IOutgoingUdpResponder() = default;

        /**
         * @brief Sends the given data as UDP datagram to given URI.
         * @param soapOverUdpUri UDP endpoint URI, e.g., "soap.udp://fabrikam1.com:54321/Server"
         * @param udpPayload Serialized SOAP XML message
         */
        virtual void sendUdpMessage(const std::string& soapOverUdpUri, const std::string& udpPayload) = 0;

        /**
         * @brief Sends the given data as UDP datagram to given URI.
         * @param soapOverUdpUri UDP endpoint URI, e.g., "soap.udp://fabrikam1.com:54321/Server"
         * @param udpPayload Serialized SOAP XML message
         * @param delay The message will be send after the given delay.
         */
        virtual void sendUdpMessage(const std::string& soapOverUdpUri, const std::string& udpPayload, DFL::Chrono::Milliseconds delay) = 0;
};

}
