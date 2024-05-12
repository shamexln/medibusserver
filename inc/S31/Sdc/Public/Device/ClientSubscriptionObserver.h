#pragma once

namespace S31::Sdc
{
class SubscriptionInfo;

/**
 * @brief Observer to client subscription(s).
 * @details This observer is intended to be invoked if the subscriptions of an SDC device change.
 * This is either there a new subscribers and/or subscribers are gone.
 *
 * @ingroup S31SdcDevice
 */
class ClientSubscriptionObserver
{
    public:
        virtual ~ClientSubscriptionObserver() = default;

        /**
         * @brief Callback that is invoked if there is any change in subscriptions.
         * @details If invoked the observer can get information about the current subscriptions
         * from the observed subject.
         */
        virtual void clientSubscriptionsChanged() = 0;

        /**
         * @brief Callback that is invoked when a subscription is lost unexpectedly.
         * @details If invoked, then the identified subscription has failed due to delivery timeout or error.
         * To monitor for reconnect, the observer may wait for subsequent @ref clientSubscriptionsChanged()
         * callback invocation, and read information about the current active subscriptions from the observed
         * subject.
         */
        virtual void clientSubscriptionFailed(const SubscriptionInfo& failedSubscription);
};

inline void ClientSubscriptionObserver::clientSubscriptionFailed(const SubscriptionInfo& /* failedSubscription */) {}
}
