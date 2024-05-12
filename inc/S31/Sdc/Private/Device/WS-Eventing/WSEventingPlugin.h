#pragma once

#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequest.h>
#include <S31/Sdc/Private/Device/IHostedServicePlugin.h>
#include <S31/Sdc/Private/Device/WS-Eventing/IWSEventingSubscriptionManager.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionCounter.h>
#include <S31/Sdc/Private/Device/WS-Eventing/WSEventingNotifyJob.h>
#include <S31/Sdc/Private/Device/WS-Eventing/WSEventingSubscriptionEndJob.h>
#include <S31/Sdc/Public/Common/CompressionConfiguration.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Crypto/Public/DistinguishedName.h>
#include <Framework/Utils/Public/NotNull.h>

#include <string_view>
#include <vector>

namespace S31::Sdc::Impl
{
class IOutgoingMessage;
class IOutgoingJobQueue;
class IScheduling;
class GsoapEpr;
class WSEventingSubscription;

/**
 * @brief Limit of how many notifications can be buffered for each subscriber.
 * @details This number is not totally random - The number of notifications that can be handled
 * is at least limited by the HTTP roundtrip time. So 10..20 notification per second can
 * be already considered 'a lot'. Then the queue would be able to hold 5..10sec of data.
 * This corresponds to another limititation - that queued shall not be older than 5sec.
 */
constexpr unsigned int MaxQueueSize = 100;

/**
 * @brief This WS-Eventing plug-in is used for DPWS device hosted services.
 *
 * @details One instance is created for exactly one hosted service.
 * We can not implement the web service operation (subscribe etc.) within this
 * class, because we need one instance for each web service request (from the network).
 * To avoid a self copy we have a separate class (@ref DeviceSubscriptionDispatcher)
 * that simulates the dispatching function in this class.
 *
 * @ingroup S31SdcDevice
 */
class WSEventingPlugin: public IHostedServicePlugin,
                        public IWSEventingSubscriptionManager,
                        public Utils::OutcomeConsumer<WSEventingPlugin, WSEventingNotifyJobResult>,
                        public Utils::OutcomeConsumer<WSEventingPlugin, WSEventingSubscriptionEndJobResult>,
                        public std::enable_shared_from_this<WSEventingPlugin>
{
    public:
        static DFL::NotNull<std::shared_ptr<WSEventingPlugin>> create(
                const std::shared_ptr<IOutgoingJobQueue>& jobQueue,
                const std::shared_ptr<IScheduling>& scheduling,
                CompressionConfiguration supportCompression,
                WeakSubscriptionCounter subscriptionCounter,
                unsigned int maxNotificationQueueSize = MaxQueueSize)
        {
            auto ptr = std::shared_ptr<WSEventingPlugin>(new WSEventingPlugin(
                    jobQueue,
                    scheduling,
                    supportCompression,
                    subscriptionCounter,
                    maxNotificationQueueSize
                    ));
            ptr->initJobHandlers();
            return DFL::asNotNull(ptr);
        }
    private:
        WSEventingPlugin(const std::shared_ptr<IOutgoingJobQueue>& jobQueue,
                         const std::shared_ptr<IScheduling>& scheduling,
                         CompressionConfiguration supportCompression,
                         WeakSubscriptionCounter subscriptionCounter,
                         unsigned int maxNotificationQueueSize);
    public:
        ~WSEventingPlugin() noexcept override;

        // IHostedServicePlugin
        int dispatch(struct soap* soapHandle) override;
        void deviceShuttingDown() override;

        /**
         * @brief Checks whether there exists a subscriber for any SOAP action.
         *
         * @return @c true is there is at least one subscriber for any SOAP action.
         */
        bool hasSubscriber();

        /**
         * @brief Checks whether there exists a subscriber for a specific SOAP action.
         *
         * @param action WS-Eventing SOAP action URI for which the existence of subscriber is checked.
         * @return @c true is there is at least one subscriber for the given SOAP action.
         */
        bool hasSubscriberForAction(std::string_view action);

        /**
         * @brief Check if there is a subscription created by a remote client with a specific X.509 distinguished name.
         *
         * @details If distinguishedName is empty then @c false is returned.
         */
        bool hasSpecificSubscriberForAction(const DFL::Crypto::DistinguishedName& distinguishedName, std::string_view action);

        /**
         * @brief Registers subscription change observer.
         *
         * @param observer Observer interested in subscription information changes.
         */
        void registerClientSubscriptionObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer);

        /**
         * @brief Unregisters subscription change observer.
         */
        void unregisterClientSubscriptionObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer);

        /**
         * @brief Returns the active subscriptions.
         */
        ClientSubscriptions subscriptions() const;

        /**
         * @brief Function to fire events to subscribers interested in the given action.
         * @details The list of current subscriber is handled by the plug-in automatically.
         *
         * @param eventMessage The notification message that will be send to all relevant subscribers.
         */
        void fireEvent(DFL::NotNull<std::unique_ptr<IOutgoingMessage>> eventMessage);

        SubscribeResult subscribe(
                const DFL::Chrono::Seconds&                                    requestedExpiration,
                const DFL::NotNull<std::shared_ptr<const HttpSessionContext>>& httpSessionContext,
                SubscriptionFilterDialect                                      dialect,
                SubscriptionFilterContent                                      content,
                DFL::NotNull<std::shared_ptr<GsoapEpr>>                        notifyTo,
                std::shared_ptr<GsoapEpr>                                      endTo,
                const std::string&                                             subManagerAddress,
                EncodingType                                                   encoding) override;

        boost::optional<DFL::Chrono::Seconds> renew(const std::string& subscriptionId,
                                                    DFL::Chrono::Seconds requestedExpiration) override;

        boost::optional<DFL::Chrono::Seconds> getStatus(const std::string& subscriptionId) override;

        void unsubscribe(const std::string& subscriptionId) override;

        std::string pluginName() const override;
    private:
        /**
         * @brief Has to be called after construction to set up internal data.
         * @details
         * The initialization is not possible in the constructor due to shared_from_this.
         */
        void initJobHandlers();

        /**
         * @brief Non-virtual function could be called in destructor.
         */
        void internalDeviceShuttingDown();

        void updateDeliveryCheckFor(const std::string& subscriptionId);
        void subscriptionEnd(const std::string& subscriptionId,
                             SubscriptionEndReason endReason,
                             const DFL::Locale::Utf8& reasonMessage);

        void addJobToJobQueue(DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> job);

        bool hasSubscriberForAction(const DFL::Crypto::DistinguishedName& distinguishedName, std::string_view action);

        std::shared_ptr<WSEventingSubscription> subscription(const std::string& subscriptionId) const;
        static DFL::Chrono::Seconds correctExpiresValue(DFL::Chrono::Seconds requestedExpiration);

        void removeExpiredSubscriptions();

        ClientSubscriptions clientSubscriptionsNoLock() const;

        void notifySubscriptionChangeListeners();
        void notifySubscriptionFailureListeners(const ClientSubscriptions& failedSubscriptionInfos);

        static std::string toString(const WSEventingSubscription& subscription);

        std::weak_ptr<IOutgoingJobQueue> m_jobQueue;
        std::weak_ptr<IScheduling> m_scheduling;
        std::map<std::string, DFL::NotNull<std::shared_ptr<WSEventingSubscription>>> m_subscriptions;
        mutable std::mutex m_mutex;
        CompressionConfiguration m_compression;
        Utils::OutcomeConsumer<WSEventingPlugin, WSEventingNotifyJobResult>::HandlerPtr m_handlerOfNotifyJobs;
        Utils::OutcomeConsumer<WSEventingPlugin, WSEventingSubscriptionEndJobResult>::HandlerPtr m_handlerOfSubscriptionEndJobs;
        WeakSubscriptionCounter m_subscriptionCounter;
        const unsigned int m_maxNotificationQueueSize;
        S31::Utils::ObservableSubjectDelegate<ClientSubscriptionObserver> m_subscriptionInfoSubject;

};

}
