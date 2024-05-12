#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc
{

/**
 * @brief Priority groups to configure the delay before sending the first http(s) message after discovery
 *
 * @details Priority groups allow clients to connect to a device in priority order, since the highest priority
 * Group0 connects with the shortest delay, and the lowest priority Group9 connects after the longest delay.
 *
 * Priority groups are defined in IEEE 11073-20701-2018:8.1.5.
 *
 * @ingroup S31SdcClient
 */
enum class ConnectionPriorityGroup
{
    Group0, ///< delay time 0 to 15 seconds
    Group1, ///< delay time 5 to 20 seconds
    Group2, ///< delay time 10 to 25 seconds
    Group3, ///< delay time 15 to 30 seconds
    Group4, ///< delay time 20 to 35 seconds
    Group5, ///< delay time 25 to 40 seconds
    Group6, ///< delay time 30 to 45 seconds
    Group7, ///< delay time 35 to 50 seconds
    Group8, ///< delay time 40 to 55 seconds
    Group9, ///< delay time 45 to 60 seconds
    NoDelay, ///< group for testing that does not delay connection
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ConnectionPriorityGroup, (Group0)(Group1)(Group2)(Group3)(Group4)(Group5)(Group6)(Group7)(Group8)(Group9)(NoDelay))

}
