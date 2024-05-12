#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc::Impl
{
/**
 * @brief Enum for subscription end reason.
 * @ingroup S31SdcDevice
 */
enum class SubscriptionEndReason
{
        /**
         * @brief The event source terminated the subscription because the source is being shut down in a controlled manner.
         * @details That is, if the event source is being shut down but has the opportunity to send a SubscriptionEnd message before it exits.
         */
        SourceShuttingDown,

        /**
         * @brief The event source terminated the subscription because of problems delivering notifications.
         */
        DeliveryFailure,

        /**
         * @brief The event source terminated the subscription for some other reason before it expired.
         */
        SourceCancelling

};
DFL_ENUM_CLASS_STREAM_OPERATOR(SubscriptionEndReason, (SourceShuttingDown)(DeliveryFailure)(SourceCancelling))

}
