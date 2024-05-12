#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Sdc/Private/Common/EncodingType.h>
#include <S31/Sdc/Private/Device/WS-Eventing/NotificationQueue.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionCounter.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Oids.h>

#include <memory>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{
class WSEventingNotifyJob;
class GsoapEpr;

/**
 * @brief Container for all subscription relevant data.
 *
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP WSEventingSubscription final
{
    public:

        using SubscriptionExpiration = DFL::Chrono::Seconds;

        /// @param[in] subscriptionId      Is filled from the registry with a unique subscription identifier.
        /// @param[in] credentials         Client credentials used for WS-Eventing subscribe.
        /// @param[in] expirationDuration  Set with accepted value.
        /// @param[in] soapActionFilter    List of SOAP actions to subscribe to.
        /// @param[in] notifyTo            EPR for notification.
        /// @param[in] endTo               optional EPR for SubscriptionEnd. If @c nullptr no message shall be send.
        /// @param[in] subManAddr          Transport address where the subscription should be send to.
        /// @param[in] encoding            Encoding (compression) type of outgoing message (or none)
        /// @param[in] subscriptionCounter Shared counter for subscriptions (already incremented before this call. Will be decremented in dtor.
        /// @param[in] maxQueueSize        Maximum size of the notification queue
        WSEventingSubscription(std::string subscriptionId,
                               Nomenclature::Credentials credentials,
                               SubscriptionExpiration expirationDuration,
                               std::vector<std::string> soapActionFilter,
                               DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GsoapEpr>> notifyTo,
                               std::shared_ptr<S31::Sdc::Impl::GsoapEpr> endTo,
                               std::string subManAddr,
                               EncodingType encoding,
                               WeakSubscriptionCounter subscriptionCounter,
                               unsigned int maxQueueSize);

        ~WSEventingSubscription() noexcept;

        const std::string& subscriptionId() const;
        const Nomenclature::Credentials& subscriberCredentials() const;
        const std::vector<std::string>& subscriptionActions() const;

        void subscriptionExpiration(SubscriptionExpiration expirationDuration);
        SubscriptionExpiration remainingSubscriptionExpiration() const;
        bool isSubscriptionExpired() const;

        bool hasActionSubscribed(std::string_view soapAction) const;
        bool hasSubscriptionDistinguishedName(const DFL::Crypto::DistinguishedName& dn) const noexcept;
        DFL::NotNull<std::shared_ptr<GsoapEpr>> notifyToEpr() const;

        /**
         * @brief Optional EPR where to send a SubscriptionEnd message if the subscription is terminated unexpectedly.
         */
        std::shared_ptr<GsoapEpr> endToEpr() const;
        std::string subscriptionManagerAddress() const;
        EncodingType encoding() const;

        void pushEvent(std::unique_ptr<WSEventingNotifyJob> event);
        std::unique_ptr<WSEventingNotifyJob> popPendingEvent();
        void transmissionSucceeded();

        DFL::Chrono::SteadyClock::TimePoint nextTimeoutCheckAt() const;
        bool deliveryTimeout() const;

        bool pendingEventQueueOverflow() const;

    private:
        const std::string m_subscriptionId;
        const Nomenclature::Credentials m_subscriberCredentials;
        DFL::Chrono::SteadyClock::TimePoint m_subscriptionExpirationTime;
        const std::vector<std::string> m_soapActionFilter;
        const DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GsoapEpr>> m_notifyTo;
        const std::shared_ptr<S31::Sdc::Impl::GsoapEpr> m_endTo;
        const std::string m_subscriptionManagerAddress;
        const EncodingType m_encoding;
        WeakSubscriptionCounter m_subscriptionCounter;
        NotificationQueue m_pendingEvents;

};

}
