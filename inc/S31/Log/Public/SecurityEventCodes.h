#pragma once

#include <Framework/Log/Public/EventCode.h>

namespace S31::Log
{
/**
 * @brief "SDC S31" security events as specified in Doors "Security Event Registry".
 * @details
 * This (currently hand written) enum contains the information from the Doors module with
 * SDC S31 security event codes.
 * @ingroup S31Log
 */
enum class SecurityEventCodes : unsigned int
{
        /// @brief Too many DPWS discovery messages in a second.
        TooManySdcDiscoveryMessages = 2015,

        /// @brief An authenticated SDC Participant tried to use a service that is not authorized.
        UnauthorizedSdcService = 2016,

        /// @brief Remote operation invoked.
        InvocationOfSdcOperation = 2017,

        /// @brief Subscript of SDC Consumer to SDC Provider.
        SubscriptionOfSdcConsumer = 2018,

        /// @brief A received SDC message could not be processed.
        SdcMessageProcessingError = 2019,

        /// @brief TLS-based sequence of message exchange started.
        StartingSdcMessageSequence = 2020,

        /// @brief TLS-based sequence of message exchange ended.
        EndingSdcMessageSequence = 2021,

        /// @brief Invocation of a retriggerable Operation - first invocation of the correlated sequence.
        FirstInvocationOfRetriggerableOperationSequence = 2022,

        /// @brief Invocation of a retriggerable Operation - last invocation of the correlated sequence.
        LastInvocationOfRetriggerableOperationSequence = 2023
};

inline bool operator==(SecurityEventCodes lhs, DFL::Log::EventCode rhs)
{
    return static_cast<unsigned int>(lhs) == rhs.value();
}
inline bool operator==(DFL::Log::EventCode lhs, SecurityEventCodes rhs)
{
    return rhs == lhs;
}
inline bool operator!=(SecurityEventCodes lhs, DFL::Log::EventCode rhs)
{
    return !(lhs == rhs);
}
inline bool operator!=(DFL::Log::EventCode lhs, SecurityEventCodes rhs)
{
    return !(lhs == rhs);
}

}
