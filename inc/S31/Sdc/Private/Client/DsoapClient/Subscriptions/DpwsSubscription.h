#pragma once

#include <S31/Sdc/Private/Client/Report/ReportProcessor.h>
#include <S31/Sdc/Private/Client/SetService/InvocationReportSubject.h>
#include <S31/Sdc/Private/Client/WS-Eventing/IWSEventingClientListener.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <Framework/Chrono/Public/SteadyClock.h>

#include <boost/optional/optional.hpp>

#include <mutex>
#include <string>

namespace S31::Sdc::Impl
{
class IDpwsSubscriptionMonitor;

/**
 * @brief One instance is a subscription one remote medical device to retrieve event updates.
 *
 * @details It is possible to have one WS-Eventing subscription for multiple events (SOAP actions).
 * It is instantiated from the @ref DpwsSubscriptionMonitor for each medical device that provides relevant data.
 *
 * \ingroup S31SdcClient
 */
class DpwsSubscription: public S31::Sdc::Impl::IWSEventingClientListener
{
    public:
        DpwsSubscription(const S31::Sdc::EndpointReference& remoteDeviceEpr, // NOLINT(modernize-pass-by-value)
                         std::weak_ptr<Sdc::Impl::Report::ReportProcessor> reportProcessor,
                         std::weak_ptr<IDpwsSubscriptionMonitor> monitor,
                         std::weak_ptr<Sdc::Impl::InvocationReportSubject> invocationReportSubject,
                         DFL::Chrono::Milliseconds timeOutDuration);
        /**
         * Is called for each received gSOAP event.
         *
         * Delegates handling to EventSink implementation that stores the changes in the MDIB.
         * @param soapHandle gSOAP network handle
         * @return gSOAP error code
         */
        int dispatchEvent(struct soap* soapHandle) override;
        void expirationResponse(DFL::Chrono::Seconds expiration) override;

        void subscriptionEnd(S31::Sdc::Impl::SubscriptionEndStatus endStatus, const DFL::Locale::Utf8& reason) override;
        void handleError(const Utils::Error& error) override;

        void injectSubscriptionId(S31::Sdc::Impl::WSEventingClientSubscriptionId subscriptionId) override;

        /// @returns @c true iff the subscription is ended (unsubscribed, error, SubscriptionEnd was received,...)
        bool hasEnded() const;

        /// @returns true iff for this subscription there where notification from the device (== it's working).
        bool hasRecentlyReceivedNotifications() const;

        /// @returns @c true iff the subscription will expire soon (we have to renew before the subscription expires)
        bool willExpireSoon() const;
    private:

        void markAlive();

        S31::Sdc::EndpointReference m_remoteDeviceEpr;

        std::weak_ptr<Sdc::Impl::InvocationReportSubject> m_invocationReportSubject;

        std::weak_ptr<IDpwsSubscriptionMonitor> m_weakMonitor;
        boost::optional<S31::Sdc::Impl::WSEventingClientSubscriptionId> m_subscriptionId;
        boost::optional<Sdc::Impl::SubscriptionEndStatus> m_subscriptionEnded;

        DFL::Chrono::SteadyClock::TimePoint m_lastEventReceivedTimePoint;
        boost::optional<DFL::Chrono::SteadyClock::TimePoint> m_expirationTimePoint;

        std::weak_ptr<Sdc::Impl::Report::ReportProcessor> m_reportProcessor;
        DFL::Chrono::Milliseconds m_timeOutDuration; ///< minimal expected duration between two data receivings ('is alive'), typically some seconds

        mutable std::mutex m_mutex;
};

}
