#pragma once

#include <S31/Sdc/Private/Client/DpwsSubscriptionOnRemoteDeviceObserver.h>
#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/IDpwsSubscriptionMonitor.h>
#include <S31/Sdc/Private/Client/NewSubscriptionActiveNotifierImpl.h>
#include <S31/Sdc/Private/Client/PortTypeExecutors.h>
#include <S31/Sdc/Private/Client/Report/ReportProcessor.h>
#include <S31/Sdc/Private/Client/SetService/InvocationReportSubject.h>
#include <S31/Sdc/Private/Client/WS-Eventing/SoapAction.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Public/Client/MdibSubscriptionType.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>

#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

namespace S31::Sdc::Impl
{
class ISoapContextPool;
class IRemoteHostedServiceEndpoint;
class IEventingClient;
class DpwsSubscription;

/// Enum used for internal dispatching
enum class SubscriptionGroup
{
    mdibUpdate,
    setService
};
DFL_ENUM_CLASS_STREAM_OPERATOR(SubscriptionGroup, (mdibUpdate)(setService))

/**
 * @brief Information of a Mdib or SetService subscription.
 * @ingroup S31SdcClient
 */
class Subscription
{
    public:
        explicit Subscription(SubscriptionGroup group);

        std::shared_ptr<DpwsSubscription> dpwsSubscription;
        boost::optional<Sdc::Impl::WSEventingClientSubscriptionId> id;
        bool active = false;
        SubscriptionGroup group;
};

/**
 * @brief Monitors the 2 subscriptions (%Mdib updates and operation invoke reports) belonging to a remote medical device.
 *
 * @details Monitors that the subscriptions are ok, or raises error and terminates them.
 * If there is no Set Service then there is only 1 subscription - this is also fine.
 *
 * Responsible for:
 *  - subscribing the 2 subscriptions to a remote device
 *  - handling life time of subscriptions (going active, error, keep alive check, unsubscribe)
 *  - allow invoking of keep alive actions on the subscription (renew if necessary)
 *
 * @ingroup S31SdcClient
 */
class DpwsSubscriptionMonitor:
        public IDpwsSubscriptionMonitor,
        public std::enable_shared_from_this<DpwsSubscriptionMonitor>
{
    public:
        DpwsSubscriptionMonitor(const DpwsSubscriptionMonitor&) = delete;
        DpwsSubscriptionMonitor(DpwsSubscriptionMonitor&&) = delete;
        DpwsSubscriptionMonitor& operator=(const DpwsSubscriptionMonitor&) = delete;
        DpwsSubscriptionMonitor& operator=(DpwsSubscriptionMonitor&&) = delete;

        DpwsSubscriptionMonitor(const S31::Sdc::EndpointReference& remoteDeviceEpr, // NOLINT(modernize-pass-by-value)
                                S31::Sdc::Impl::Endpoint::Executor getServiceExecutor,
                                S31::Sdc::Impl::Endpoint::Executor mdibUpdateExecutor,
                                boost::optional<S31::Sdc::Impl::Endpoint::Executor> setServiceExecutor,
                                std::weak_ptr<S31::Sdc::Impl::Report::ReportProcessor> reportProcessor,
                                DFL::NotNull<std::shared_ptr<Sdc::Impl::IEventingClient>> eventing,
                                std::weak_ptr<Sdc::Impl::InvocationReportSubject> invocationReportSubject,
                                Utils::WeakErrorHandler errorHandler,
                                std::weak_ptr<DpwsSubscriptionOnRemoteDeviceObserver> subscriptionOnRemoteDeviceObserver,
                                DFL::Chrono::Milliseconds timeOutDuration);

        void init(const SoapActions& mdibChangeReports);

        ~DpwsSubscriptionMonitor() noexcept override;

        void setSubscriptionActive(Sdc::Impl::WSEventingClientSubscriptionId subscriptionId) override;

        void handleError(const Utils::Error& error) override;

        /**
         * @brief Unsubscribe the subscriptions in the monitor.
         * @details This is only done if the subscriptions are still active, i.e. they are not unsubscribed
         * or terminated because of an error.
         */
        void unsubscribeActiveSubscriptions(const DFL::Locale::Utf8& reason);

        /**
         * @brief Check whether unsubscribe is completed or not.
         *
         * @c Complete means that it is safe to destroy the @ref S31::Sdc::Impl::DpwsSubscriptionMonitor and not have running subscriptions
         * managed by nobody. Note that unsubscribing might just be queued at this point (as unsubscribe job). That implies
         * that e.g. communication errors from this unsubscribe request can still be raised (in future).
         *
         * Secondly @c Complete does not mean that all unsubscribe requests before were successful.
         *
         * Requires a call of S31::Sdc::Impl::DpwsSubscriptionMonitor::unsubscribeActiveSubscriptions() beforehand.
         *
         * @return true if so
         */
        bool unsubscribeCompleted() const;

        /**
         * @brief Check subscriptions' keep alive status.
         * @details Has to be called periodically. Invokes RENEW if necessary. Does nothing if subscription is not
         * there or has ended already.
         */
        void keepAlive();

        /**
         * @brief Raises an error if one of the subscriptions is ended.
         * @details This is to be used in connection with @ref keepAlive() because only a not ended subscription can be kept alive.
         */
        void raiseErrorIfIsEnded();
    private:
        void subscribeSetService();
        void subscribeMdibUpdates(const SoapActions& mdibChangeReports);

        void internalUnsubscribe(Impl::Subscription& subscription, const DFL::Locale::Utf8& reason);
        void internalSubscribe(Impl::Subscription& subscription, const SoapActions& actionUriList);
        void handleUnsubscribedFlag();

        enum class SubscriptionTypesChangeResult
        {
            unchanged,
            changed
        };

        const S31::Sdc::EndpointReference m_remoteDeviceEpr;
        const S31::Sdc::Impl::Endpoint::Executor m_getServiceExecutor;
        const S31::Sdc::Impl::Endpoint::Executor m_mdibUpdateExecutor;
        const boost::optional<S31::Sdc::Impl::Endpoint::Executor> m_setServiceExecutor;
        const std::weak_ptr<S31::Sdc::Impl::Report::ReportProcessor> m_reportProcessor;

        DFL::NotNull<std::shared_ptr<Sdc::Impl::IEventingClient>> m_eventingClient;

        std::weak_ptr<Sdc::Impl::InvocationReportSubject> m_invocationReportSubject;
        Utils::WeakErrorHandler m_errorHandler;
        std::weak_ptr<DpwsSubscriptionOnRemoteDeviceObserver> m_subscriptionOnRemoteDeviceObserver;
        DFL::Chrono::Milliseconds m_timeOutDuration;
        bool m_unsubscribeCompleted = false;

        Impl::Subscription m_mdibUpdateSubscription;
        Impl::Subscription m_setServiceSubscription;

        std::mutex m_mdibUpdateMutex;
        std::mutex m_setServiceMutex;

        S31::Sdc::Impl::Endpoint::HandlerPtr m_executorHandlerPtr;
};

}
