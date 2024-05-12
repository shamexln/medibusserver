#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc
{

/**
 * @brief Enumeration for configuring %Diffserv %AssuredForwarding for quality of service.
 * @details %Assured %Forwarding (%AF) behavior is specified in <a href="https://tools.ietf.org/html/rfc2597">RFC 2597</a>
 * and <a href="https://tools.ietf.org/html/rfc3260">RFC 3260</a>.
 * @ingroup S31SdcCommon
 */
enum class AssuredForwardingClass
{
    None =  0,    ///< Default forwarding
    AF11 = 10,    ///< Assured forwarding class 1, low drop probablity
    AF12 = 12,    ///< Assured forwarding class 1, medium drop probablity
    AF13 = 14,    ///< Assured forwarding class 1, high drop probablity
    AF21 = 18,    ///< Assured forwarding class 2, low drop probablity
    AF22 = 20,    ///< Assured forwarding class 2, medium drop probablity
    AF23 = 22,    ///< Assured forwarding class 2, high drop probablity
    AF31 = 26,    ///< Assured forwarding class 3, low drop probablity
    AF32 = 28,    ///< Assured forwarding class 3, medium drop probablity
    AF33 = 30,    ///< Assured forwarding class 3, high drop probablity
    AF41 = 34,    ///< Assured forwarding class 4, low drop probablity
    AF42 = 36,    ///< Assured forwarding class 4, medium drop probablity
    AF43 = 38,    ///< Assured forwarding class 4, high drop probablity
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AssuredForwardingClass, (None)(AF11)(AF12)(AF13)(AF21)(AF22)(AF23)(AF31)(AF32)(AF33)(AF41)(AF42)(AF43))

}
