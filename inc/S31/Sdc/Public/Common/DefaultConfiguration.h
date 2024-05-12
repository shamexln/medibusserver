#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/Uri.h>
#include <Framework/Utils/Public/Utf8.h>

#include <cstdint>

namespace S31
{

/*!
 * \brief Provides default configuration constants for S31 and S31.x.
 *
 * \ingroup S31SdcCommon
 */
class DefaultConfiguration
{
public:

    /**
     * @brief Maximum number of idle keep-alive outgoing connections.
     * @details It covers connections from a device to the client (event sink)
     * as well as from a client to a device (e.g., GetMDIB calls)
     */
    static unsigned int maxIdleOutgoingConnections()
    {
        return 250;
    }

    /**
     * @brief Maximum number of idle keep-alive incoming connections.
     * @details One a device it covers requests such as GetMDIB or WS-Eventing subscribe.
     * In a client it is the max numbers of notifications connections.
     */
    static unsigned int maxIdleIncomingConnections()
    {
        return 250;
    }

    /**
     * @brief Timeout duration for idle keep-alive connections.
     */
    static unsigned int idleTimeoutInSeconds()
    {
        return 10;
    }

    /**
     * @brief Maximum of concurrent SSL handshakes.
     */
    static unsigned int maxConcurrentSslHandshakes()
    {
        return 10;
    }

    /**
     * @brief Maximum of concurrent outgoing running HTTP requests.
     */
    static unsigned int maxConcurrentOutgoingHttpRequests()
    {
        return 50;
    }

    /**
     * @brief Maximum of concurrent incoming running HTTP requests.
     */
    static unsigned int maxConcurrentIncomingHttpRequests()
    {
        return 50;
    }

    /**
     * @brief UDP multicast packet Time-To-Live value.
     */
    static std::uint8_t udpMulticastTtl()
    {
        return 15;
    }

    /**
     * @brief Minimum of UDP multicast packet Time-To-Live value.
     */
    static std::uint8_t minUdpMulticastTtl()
    {
        return 1;
    }

    /**
     * @brief Maximum of UDP multicast packet Time-To-Live value.
     */
    static std::uint8_t maxUdpMulticastTtl()
    {
        return 255;
    }

    /**
     * @brief Flag, if LLDP is enabled or not
     */
    static bool lldpEnabled()
    {
        return false;
    }

    /**
     * @brief Flag, if AutoValidation is enabled or not
     */
    static bool autoValidationEnabled()
    {
        return false;
    }

    /**
     * @brief Flag, if UseFixedLocation is enabled or not
     */
    static bool useFixedLocation()
    {
        return false;
    }

    /**
     * @brief Flag, if Network Qos is enabled or not
     */
    static bool networkQosEnabled()
    {
        return true;
    }

    /**
     * @brief String that represents default DPWS friendly name
     */
    static DFL::Locale::Utf8 friendlyName()
    {
        return DFL::Locale::Utf8("");
    }

    /**
     * @brief Uri of the default discovery proxy
     */
    static boost::optional<DFL::Net::Uri> discoveryProxy()
    {
        return boost::none;
    }
};

}
