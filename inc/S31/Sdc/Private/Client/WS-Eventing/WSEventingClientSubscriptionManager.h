#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/IEventingClient.h>
#include <S31/Sdc/Private/Client/WS-Eventing/IWSEventingClientListener.h>
#include <S31/Sdc/Private/Client/WS-Eventing/SoapAction.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscription.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingGetStatusJob.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingRenewJob.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingSubscribeJob.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingUnsubscribeJob.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>
#include <S31/Sdc/Private/Common/Http/HttpPostHandler.h>
#include <S31/Sdc/Private/Common/ISoapContextPool.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceUpdateList.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <map>
#include <memory>
#include <string>

namespace S31::Sdc::Impl
{

class IRemoteHostedServiceEndpoint;
class IWSEventingClientListener;
class NetworkInterfaceManager;
class IScheduling;
class IOutgoingJobQueue;
class SubscribeJobsHandlerManager;

/**
 * @brief Types of jobs used in WSEventingClientSubscriptionManager (for production).
 * @ingroup S31SdcClientEventing
 */
struct WSEventingClientSubscriptionManagerJobs
{
        using Subscribe = WSEventingSubscribeJob;
        using Unsubscribe = WSEventingUnsubscribeJob;
        using Renew = WSEventingRenewJob;
        using GetStatus = WSEventingGetStatusJob;
};

/**
 * \brief Registers itself as a WS-Eventing sink and handles client side subscriptions.
 *
 * \ingroup S31SdcClientEventing
 */
template<class Jobs>
class WSEventingClientSubscriptionManagerImpl:
        public IEventingClient,
        public HttpPostHandler,
        public Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingSubscribeJobResult>,
        public Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingUnsubscribeJobResult>,
        public Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingRenewJobResult>,
        public Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingGetStatusJobResult>,
        public std::enable_shared_from_this<WSEventingClientSubscriptionManagerImpl<Jobs>>
{
    public:
        /**
         * @brief Construct a WS-Eventing client.
         * @details
         *
         * @param soapContextPool Soap pool for gsoap usage.
         * @param outgoingJobQueue The job queue is required for GetStatus, Renew or Unsubscribe messages.
         * @param networkInterfaceManager It looks like network interface changes are used right now to trigger an
         * unsubscribe. Documentation why this is required is missing.
         * @param localCallbackPort The local HTTP server port is required for subscription to build up the URLs for
         * notify-to and end-to endpoint reference addresses. It is not possible to derive them from any outgoing HTTP
         * connection. From that TCP connection only the IP address could be used for the Subscribe message.
         */
        WSEventingClientSubscriptionManagerImpl(
                std::weak_ptr<ISoapContextPool> soapContextPool,
                std::weak_ptr<IOutgoingJobQueue> outgoingJobQueue,
                std::weak_ptr<NetworkInterfaceManager> networkInterfaceManager,
                unsigned short localCallbackPort);
        ~WSEventingClientSubscriptionManagerImpl() noexcept override;

        std::string getSubscriptionDirectoryName() const;

        /**
         * Is called for incoming events, that have to be dispatched to the subscribed client.
         */
        HttpServerResponse handleHttpPost(
                HttpPathView                                            targetPath,
                HttpAcceptEncodingView                                  acceptEncoding,
                std::string_view                                        body,
                HttpContentTypeView                                     contentType,
                HttpContentEncodingView                                 contentEncoding,
                DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext) override;

        // available for testing, is used internally
        int dispatch(struct soap* soap);

        /// @name client operations and the callback listener implementation
        ///@{
        WSEventingClientSubscriptionId subscribe(const S31::Sdc::Impl::Endpoint::Executor& executor,
                const SoapActions& actions, const std::shared_ptr<IWSEventingClientListener>& callback) override;
        WSEventingClientSubscriptionId subscribe(const S31::Sdc::Impl::Endpoint::Executor& executor,
                const std::shared_ptr<IWSEventingClientListener>& callback) override;
        void triggerRenew(const WSEventingClientSubscriptionId& subscriptionId) override;
        void triggerGetStatus(const WSEventingClientSubscriptionId& subscriptionId) override;
        void unsubscribe(const WSEventingClientSubscriptionId& id, const DFL::Locale::Utf8& reason) override;

        /**
         * Incoming network message from the event source.
         */
        void subscriptionEnd(const WSEventingClientSubscriptionId& id,
                             SubscriptionEndStatus status,
                             const DFL::Mdib::LocalizedTexts& reason);
        ///@}

        size_t size() const;
        bool empty() const;
        std::map<std::string, WSEventingClientSubscription> getSubscriptionList() const;

        static WSEventingClientSubscriptionId createId();

    private:
        void handleError(const Utils::Error& error);

        boost::optional<const WSEventingClientSubscription> getAndEraseSubscription(const WSEventingClientSubscriptionId& id);
        void removeSubscription(const WSEventingClientSubscriptionId& id, SubscriptionEndStatus status);
        void removeSubscription(const WSEventingClientSubscriptionId& id, SubscriptionEndStatus status, const DFL::Mdib::LocalizedTexts& reason);
        void removeSubscription(const Utils::Error& error);

        void removeExpiredSubscriptions();

        static DFL::Chrono::Seconds getSteadyClock();

        void networkResponse(const WSEventingClientSubscriptionId& id,
                const std::shared_ptr<GsoapEpr>& optionalSubscriptionManager,
                DFL::Chrono::Seconds expiration,
                const DFL::Crypto::DistinguishedName& optionalRemoteDeviceDistinguishedName);

        boost::optional<const WSEventingClientSubscription> findSubscription(const WSEventingClientSubscriptionId& subscriptionId) const;
        boost::optional<const WSEventingClientSubscription> findSubscriptionNoLock(const WSEventingClientSubscriptionId& subscriptionId) const;
        DFL::Chrono::Seconds getExpirationTime(DFL::Chrono::Seconds expiration);

        std::string toString(const WSEventingClientSubscription& clientSubscription) const;
        /// for logging: list of actions, actions shortened
        static std::string shortActionList(const SoapActions& actions);

        void logSubscriptionStart(const WSEventingClientSubscription& clientSubscription) const;
        void logSubscriptionEnd(const WSEventingClientSubscription& clientSubscription, SubscriptionEndStatus endStatus, const DFL::Locale::Utf8& reason) const;

        std::weak_ptr<ISoapContextPool> m_soapPool;
        std::weak_ptr<NetworkInterfaceManager> m_networkInterfaceManager;
        std::weak_ptr<IOutgoingJobQueue> m_outgoingJobQueue;
        std::shared_ptr<IScheduling> m_scheduling;
        unsigned short m_localCallbackPort;

        std::map<std::string, WSEventingClientSubscription> m_subscriptions;
        mutable std::mutex m_mutex;

        std::string m_callbackDirname;

        class NetIfChangeObserver;
        std::shared_ptr<NetIfChangeObserver> m_netIfObserver;

        typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl, WSEventingSubscribeJobResult>::HandlerPtr m_handlerOfSubscribeJobs;
        typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl, WSEventingUnsubscribeJobResult>::HandlerPtr m_handlerOfUnsubscribeJobs;
        typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl, WSEventingRenewJobResult>::HandlerPtr m_handlerOfRenewJobs;
        typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl, WSEventingGetStatusJobResult>::HandlerPtr m_handlerOfGetStatusJobs;

        DFL::NotNull<std::unique_ptr<SubscribeJobsHandlerManager>> m_subscribeJobsHandlerManager;
};

/**
 * WSEventingClientSubscriptionManager, instantiation of WSEventingClientSubscriptionManagerImpl with production type jobs.
 *
 * \ingroup S31SdcClientEventing
 */
class WSEventingClientSubscriptionManager
    : public WSEventingClientSubscriptionManagerImpl<WSEventingClientSubscriptionManagerJobs>
{
    public:
        using WSEventingClientSubscriptionManagerImpl<WSEventingClientSubscriptionManagerJobs>::WSEventingClientSubscriptionManagerImpl;
};

}
