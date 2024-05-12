#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Specifies the reasons why a client subscriptions ends.
 * @ingroup S31SdcClientEventing
 */
enum class SubscriptionEndStatus
{
    // local status
    /**
     * @brief The local WS-Eventing client is shutting down.
     */
    LOCAL_SHUTTING_DOWN,

    /**
     * @brief The WS-Eventing subscription expired (was not renewed).
     */
    SUBSCRIPTION_EXPIRED,

    /**
     * @brief The local WS-Eventing client actively unsubscribes the subscription.
     */
    UNSUBSCRIBED,

    // remote status

    /**
     * @brief Received SubscriptionEnd message indicating source shutting down.
     * @details
     * Remote status: The event source terminated the subscription because the source is being shut down in a controlled manner.
     * That is, if the event source is being shut down but has the opportunity to send a SubscriptionEnd message before it exits.
     */
    SOURCE_SHUTTING_DOWN,

    /**
     * @brief Received SubscriptionEnd message indicating delivery failure.
     * @details
     * Remote status: The event source terminated the subscription because of problems delivering notifications.
     */
    DELIVERY_FAILURE,

    /**
     * @brief Received SubscriptionEnd message indicating unknown reason.
     * @details
     * Remote status: The event source terminated the subscription for some other (no DELIVERY_FAILURE or SOURCE_SHUTTING_DOWN) reason before it expired.
     */
    SOURCE_CANCELLED,

    // unknown status

    /**
     * Subscription was flagged as ended because of an error.
     */
    OTHER_ERROR
};
DFL_ENUM_CLASS_STREAM_OPERATOR(SubscriptionEndStatus, (LOCAL_SHUTTING_DOWN)(SUBSCRIPTION_EXPIRED)(UNSUBSCRIBED)\
                               (SOURCE_SHUTTING_DOWN)(DELIVERY_FAILURE)(SOURCE_CANCELLED)(OTHER_ERROR))


/**
 * @brief Callback interface for WS-Eventing clients that is called for registered incoming events and status information updates.
 *
 * \ingroup S31SdcClientEventing
 */
class IWSEventingClientListener: public Utils::ErrorHandler
{
    public:
        ~IWSEventingClientListener() override = default;

        /// Incoming events are delivered to this function
        virtual int dispatchEvent(struct soap* soapHandle) = 0;

        /// Is called after subscribe, getStatus, and renew network calls with
        /// the corresponding response given from the remote DPWS device
        virtual void expirationResponse(DFL::Chrono::Seconds expiration) = 0;

        /**
         * Is called with information why the subscriptions ends.
         * The enum contains local and remote reasons for subscription termination.
         */
        virtual void subscriptionEnd(SubscriptionEndStatus /*endStatus*/, const DFL::Locale::Utf8& /*reason*/) = 0;

        /// @brief Allow listener to record its subscription Id
        virtual void injectSubscriptionId(WSEventingClientSubscriptionId subscriptionId) = 0;
};

}
