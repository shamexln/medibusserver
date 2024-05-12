#pragma once

#include <S31/Gsoap/S31Only/AddressingHelper.h>
#include <S31/Gsoap/S31Only/SoapUtils.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Log/Public/SecurityEventCodes.h>
#include <S31/Log/Public/SecurityLogger.h>
#include <S31/Nomenclature/Public/Roles.h>
#include <S31/Sdc/Private/Client/WS-Eventing/EventSinkService.h>
#include <S31/Sdc/Private/Client/WS-Eventing/IWSEventingClientListener.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionManager.h>
#include <S31/Sdc/Private/Common/DsoapCommon/WebServiceConstants.h>
#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/Sdc/Private/Common/Http/HttpServerResponseHelper.h>
#include <S31/Sdc/Private/Common/ISoapContextPool.h>
#include <S31/Sdc/Private/Common/MessageLayer/GsoapEpr.h>
#include <S31/Sdc/Private/Common/MessageLayer/GsoapPostHandler.h>
#include <S31/Sdc/Private/Common/MessageLayer/WebServiceFunctionWrapper.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/Messaging/SoapHeaderUtils.h>
#include <S31/Sdc/Private/Common/SoapUtils.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceManager.h>
#include <S31/Sdc/Private/Common/StackConstants.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Chrono/Public/ChronoIo.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Crypto/Public/DistinguishedNameIo.h>
#include <Framework/Crypto/Public/RandomUuidGenerator.h>
#include <Framework/Format/Public/StdContainerIo.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Mdib/Public/Model/LocalizedTextIo.h>
#include <Framework/Utils/Public/Utf8Io.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <algorithm>
#include <cstddef>
#include <queue>
#include <sstream>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * \brief Holds the handler for subscription jobs.
 *
 * \details Used for time out handling of subscription jobs.
 *
 * \ingroup S31SdcClientEventing
 */
class SubscribeJobsHandlerManager
{
    private:
        const DFL::Chrono::Seconds HandlerTimeout = DFL::Chrono::Seconds(120); // set to arbitrary value of 2 minutes
        struct SubscribeHandler
        {
            S31::Sdc::Impl::Endpoint::HandlerPtr handler;
            DFL::Chrono::SteadyClock::TimePoint startTime;
        };

    public:
        void addHandler(S31::Sdc::Impl::Endpoint::HandlerPtr&& handler)
        {
            std::lock_guard<std::mutex> const lock(m_mutex);
            if (handler)
            {
                m_subscribeHandlers.push(SubscribeHandler{ handler, DFL::Chrono::SteadyClock::now() });
            }
        }

        void eraseStaleHandlers()
        {
            std::lock_guard<std::mutex> const lock(m_mutex);
            const auto now = DFL::Chrono::SteadyClock::now();

            while (!m_subscribeHandlers.empty() && now - m_subscribeHandlers.front().startTime > HandlerTimeout)
            {
                m_subscribeHandlers.pop();
            }
        }

    private:
        std::mutex m_mutex;
        std::queue<SubscribeHandler> m_subscribeHandlers;
};

/**
 * \ingroup S31SdcClientEventing
 */
template<class Jobs>
class WSEventingClientSubscriptionManagerImpl<Jobs>::NetIfChangeObserver : public IInterfaceChangeObserver
{
    public:
        NetIfChangeObserver(const std::shared_ptr<NetworkInterfaceManager>& networkInterfaceManager,
                            const std::shared_ptr<WSEventingClientSubscriptionManagerImpl>& subMan) :
                m_networkInterfaceManager(networkInterfaceManager),
                m_subMan(subMan)
        {}

        void onInterfaceChange(NetworkInterfaceUpdateList netIfUpdates) override
        {
            auto networkInterfaceManager = m_networkInterfaceManager.lock();
            auto subMan = m_subMan.lock();

            if (!(networkInterfaceManager && subMan))
            {
                return;
            }

            if (!NetworkInterfaceManager::hasNewConnectedInterfaceInUpdate(netIfUpdates))
            {
                return;
            }

            auto subList(subMan->getSubscriptionList());

            S31_STREAM_TRACE_LOGGER("Soap.WS", "Client: WS-Eventing: re-subscribe existing subscriptions due to an interface change");

            for (const auto& subscription : subList)
            {
                subMan->unsubscribe(subscription.second.getId(), DFL::Locale::Utf8("Network interface changed."));
                /// @todo whole class has to be reworked for S31-2318
                /// currently unsubscribe() leads to 'offline' re-subscribe is pointless
                // subMan->subscribe(sub.executor(), sub.getActions(), sub.getCallback());
            }
        }

    private:
        std::weak_ptr<NetworkInterfaceManager> m_networkInterfaceManager;
        std::weak_ptr<WSEventingClientSubscriptionManagerImpl> m_subMan;
};

template<class Jobs>
WSEventingClientSubscriptionManagerImpl<Jobs>::WSEventingClientSubscriptionManagerImpl(
        std::weak_ptr<ISoapContextPool>        soapContextPool,
        std::weak_ptr<IOutgoingJobQueue>       outgoingJobQueue,
        std::weak_ptr<NetworkInterfaceManager> networkInterfaceManager,
        unsigned short                         localCallbackPort)
    : m_soapPool{std::move(soapContextPool)}
    , m_networkInterfaceManager(std::move(networkInterfaceManager))
    , m_outgoingJobQueue(std::move(outgoingJobQueue))
    , m_localCallbackPort(localCallbackPort)
    , m_subscriptions()
    , m_mutex()
    , m_callbackDirname()
    , m_subscribeJobsHandlerManager(DFL::asNotNull(std::make_unique<SubscribeJobsHandlerManager>()))
{
    S31_STREAM_TRACE_LOGGER("Soap.WS", "WSEventingClientSubscriptionManager()");
    std::ostringstream cbDirname;
    cbDirname << "clientEventManager_" << this;
    m_callbackDirname = cbDirname.str();
}

template<class Jobs>
WSEventingClientSubscriptionManagerImpl<Jobs>::~WSEventingClientSubscriptionManagerImpl() noexcept
{
    try
    {
        // remove all expired subscriptions
        removeExpiredSubscriptions();

        // remove all valid subscriptions
        while (!m_subscriptions.empty())
        {
            auto it = m_subscriptions.begin();
            WSEventingClientSubscriptionId const id(it->first);

            // no unsubscribe because in current usage the job queue is faster
            // destroyed than the jobs can be executed - see jira PCSWORK-624
    //        //
    //        auto subMan = it->second.getRemoteSubscriptionManager();
    //        if (subMan)
    //        {
    //            m_networkIO->unsubscribe(id, *subMan,
    //                // pass nullptr since we are not interested in the result
    //                std::shared_ptr<IWSEventingSubscribeListener>());
    //        }

            removeSubscription(id, SubscriptionEndStatus::LOCAL_SHUTTING_DOWN);
        }
    }
    catch (const std::exception& e)
    {
        S31_STREAM_ERROR_LOGGER("Soap.WS", "Failed to cancel all subscriptions: ", e.what());
    }
    S31_STREAM_TRACE_LOGGER("Soap.WS", "~WSEventingClientSubscriptionManager()");
}

template<class Jobs>
std::string WSEventingClientSubscriptionManagerImpl<Jobs>::getSubscriptionDirectoryName() const
{
    return m_callbackDirname;
}

template<class Jobs>
HttpServerResponse WSEventingClientSubscriptionManagerImpl<Jobs>::handleHttpPost(
        HttpPathView                                            targetPath,
        HttpAcceptEncodingView                                  acceptEncoding,
        std::string_view                                        body,
        HttpContentTypeView                                     contentType,
        HttpContentEncodingView                                 contentEncoding,
        DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext)
{
    auto soapPool = m_soapPool.lock();
    if (!soapPool)
    {
        return status500_InternalError();
    }
    auto webService = std::make_shared<WebServiceFunctionWrapper>(
            [this](soap* soapHandle)
            { return this->dispatch(soapHandle); });
    return GsoapPostHandler::handleHttpPost(
            targetPath, acceptEncoding, body, contentType, contentEncoding, sessionContext, webService, *soapPool);
}

template<class Jobs>
int WSEventingClientSubscriptionManagerImpl<Jobs>::dispatch(struct soap* soapHandle)
{
    const auto* action = S31::Gsoap::soapAction(soapHandle);
    if (!action)
    {
        // soap header 'action' is required element
        return soapHandle->error = SOAP_NO_METHOD;
    }
    if (auto res = SoapUtils::checkThatPeerHasRoles(soapHandle, DFL::Oids{Nomenclature::SdcServiceProvider}))
    {
        return res;
    }

    const auto identifier(SoapHeaderUtils::getSubscriptionIdentifier(soapHandle));

    if (identifier.empty())
    {
        S31_STREAM_TRACE_LOGGER(
                "Soap.WS", "Client: WS-Eventing: no subscription identifier found for action '", action, "'");
        return SOAP_NO_METHOD;
    }

    // First check for general WS-Eventing messages for the client side (SubscriptionEnd)
    if (StackConstants::WS_EVENTING_SUBSCRIPTIONEND_ACTION == action)
    {
        EventSinkService<WSEventingClientSubscriptionManagerImpl<Jobs>> service(soapHandle, this->shared_from_this(), identifier);
        int const r = service.dispatch();
        if (r != SOAP_OK && r != SOAP_STOP)
        {
            // SOAP_STOP is fine, since for one way messages (SubscriptionEnd in this case)
            // the HTTP status "202 Accepted" results in SOAP_STOP (code 1000)
            S31_STREAM_WARN_LOGGER("Soap.WS", "Dispatching of SubscriptionEnd failed, error code: ", Gsoap::soapCode(r));
        }
        return r;
    }

    std::shared_ptr<IWSEventingClientListener> callback;
    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        if (auto subscription = findSubscriptionNoLock(WSEventingClientSubscriptionId(identifier)))
        {
            if (subscription->isSubscribedToAction(action))
            {
                callback = subscription->getCallback();
            }
        }
        else
        {
            DFL::Format::Stream msg;
            msg << "Client: WS-Eventing: unknown subscription identifier " << identifier;
            S31_STREAM_WARN_LOGGER("Soap.WS", msg.cStr());
            return SoapHeaderUtils::prepareSoapSenderFault(soapHandle, msg.cStr(), nullptr);
        }
    }

    if (callback)
    {
        int r = 0;
        try
        {
            r = callback->dispatchEvent(soapHandle);
        }
        catch (const std::exception& e)
        {
            S31_STREAM_ERROR_LOGGER(
                    "Soap.WS",
                    "Caught exception: '",
                    e.what(),
                    "' while dispatching event with soap action '",
                    action,
                    "'");
        }
        if (r && r != SOAP_STOP)
        {
            S31_STREAM_TRACE_LOGGER("Soap.WS", "Client: WS-Eventing: dispatching event to client failed with error ", r);
        }
        return r;
    }

    S31_STREAM_TRACE_LOGGER(
            "Soap.WS", "Client: WS-Eventing: no callback for subscription ", identifier, " and action ", action);

    return SOAP_NO_METHOD;
}

template<class Jobs>
WSEventingClientSubscriptionId WSEventingClientSubscriptionManagerImpl<Jobs>::subscribe(
        const S31::Sdc::Impl::Endpoint::Executor& executor,
        const std::shared_ptr<IWSEventingClientListener>& callback)
{
    return subscribe(executor, SoapActions{}, callback);
}

template<class Jobs>
WSEventingClientSubscriptionId WSEventingClientSubscriptionManagerImpl<Jobs>::subscribe(
        const S31::Sdc::Impl::Endpoint::Executor& executor,
        const SoapActions& actions,
        const std::shared_ptr<IWSEventingClientListener>& callback)
{
    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        auto networkInterfaceManager = m_networkInterfaceManager.lock();
        if (!m_netIfObserver && networkInterfaceManager)
        {
            m_netIfObserver = std::make_shared<NetIfChangeObserver>(networkInterfaceManager, this->shared_from_this());
            networkInterfaceManager->registerObserver(m_netIfObserver);
        }
    }

    WSEventingClientSubscriptionId subscriptionId(WSEventingClientSubscriptionManagerImpl::createId());
    callback->injectSubscriptionId(subscriptionId);
    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        WSEventingClientSubscription subs(subscriptionId, executor, actions, callback);
        m_subscriptions.insert(std::make_pair(subscriptionId.get(), std::move(subs)));
    }

    if (!m_handlerOfSubscribeJobs)
    {
        m_handlerOfSubscribeJobs = this->Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingSubscribeJobResult>::makeOutcomeHandler(
            [&](typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingSubscribeJobResult>::OutcomeType& outcome)
            {
                if (!outcome.hasError())
                {
                    auto result = outcome.result();
                    this->networkResponse(result->subscriptionId, result->remoteManger, result->duration, result->remoteDeviceDistinguishedName);
                }
                else
                {
                    this->removeSubscription(outcome.error());
                }
            });
    }

    auto callbackDirname = m_callbackDirname;
    auto localCallbackPort = m_localCallbackPort;
    auto createJob = [subscriptionId, actions, callbackDirname, localCallbackPort](const S31::Sdc::Impl::Endpoint::Url& target, const S31::Utils::OutcomeTypes::HandlerPtr<WSEventingSubscribeJobResult>& handler)
    {
        return std::make_unique<typename Jobs::Subscribe>(handler, subscriptionId, target, actions, callbackDirname, localCallbackPort);
    };

    m_subscribeJobsHandlerManager->eraseStaleHandlers();
    m_subscribeJobsHandlerManager->addHandler(executor.submit<WSEventingSubscribeJobResult>(m_handlerOfSubscribeJobs, createJob));

    S31_STREAM_INFO_LOGGER("Soap.WS", "Client: WS-Eventing: Subscribe ", subscriptionId, " with actions: ", shortActionList(actions));
    return subscriptionId;
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::unsubscribe(const WSEventingClientSubscriptionId& subscriptionId, const DFL::Locale::Utf8& reason)
{
    removeExpiredSubscriptions();

    if (!m_handlerOfUnsubscribeJobs)
    {
        m_handlerOfUnsubscribeJobs = this->Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingUnsubscribeJobResult>::makeOutcomeHandler(
            [this,subscriptionId](typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingUnsubscribeJobResult>::OutcomeType& outcome)
            {
                if (!outcome.hasError())
                {
                    auto result = outcome.result();
                    S31_STREAM_TRACE_LOGGER("Soap.WS", "Client: WS-Eventing: Unsubscribe succeeded for ", result->subscriptionId);
                    removeSubscription(result->subscriptionId, SubscriptionEndStatus::UNSUBSCRIBED);
                }
                else
                {
                    DFL::Format::Stream msg;
                    msg << "WS-Eventing Unsubscribe request failed: " << outcome.errorMessage();
                    DFL::Mdib::LocalizedTexts const texts{DFL::Mdib::LocalizedText{DFL::Locale::Utf8{msg.cStr()}}};
                    removeSubscription(subscriptionId, SubscriptionEndStatus::UNSUBSCRIBED, texts);
                    handleError(outcome.error());
                }
            });
    }

    auto subscription = findSubscription(subscriptionId);
    if (!subscription)
    {
        S31_STREAM_WARN_LOGGER("Soap.WS", "Client: WS-Eventing: Unsubscribe subscription with Id ", subscriptionId, " failed: subscription not found");
        return;
    }

    auto eprPtr = subscription->getRemoteSubscriptionManager();
    if (!eprPtr)
    {
        S31_STREAM_INFO_LOGGER("Soap.WS", "Client: WS-Eventing: Unsubscribe ", toString(*subscription), " failed: missing EPR");
        return;
    }

    S31_STREAM_INFO_LOGGER("Soap.WS", "Client: WS-Eventing: Unsubscribe ", toString(*subscription),
                           !reason.empty() ? DFL::Locale::Utf8(", reason: ") + reason : DFL::Locale::Utf8(""));

    auto job = std::make_unique<typename Jobs::Unsubscribe>(m_handlerOfUnsubscribeJobs, subscriptionId, *eprPtr);
    if (auto queue = m_outgoingJobQueue.lock())
    {
        queue->addAsyncJob(DFL::asNotNull(std::move(job)));
    }
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::triggerRenew(const WSEventingClientSubscriptionId& subscriptionId)
{
    removeExpiredSubscriptions();

    auto subscription(findSubscription(subscriptionId));
    if (!subscription)
    {
        S31_STREAM_INFO_LOGGER("Soap.WS", "Client: WS-Eventing: Renew for subscription ", subscriptionId, " failed. Client subscription not found");
        return;
    }

    S31_STREAM_TRACE_LOGGER("Soap.WS", "Client: WS-Eventing: trigger Renew of ", toString(*subscription));

    auto subMan(subscription->getRemoteSubscriptionManager());
    if (!subMan)
    {
        S31_STREAM_INFO_LOGGER("Soap.WS", "Client: WS-Eventing: no remote subscription manager found to trigger Renew of subscription ", subscriptionId, " (subscribe request running?)");
        return;
    }

    if (!m_handlerOfRenewJobs)
    {
        m_handlerOfRenewJobs = this->Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingRenewJobResult>::makeOutcomeHandler(
            [&](typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingRenewJobResult>::OutcomeType& outcome)
            {
                if (!outcome.hasError())
                {
                    auto result = outcome.result();
                    this->networkResponse(result->subscriptionId, std::shared_ptr<GsoapEpr>(), result->duration, DFL::Crypto::DistinguishedName{});
                }
                else
                {
                    this->removeSubscription(outcome.error());
                }
            });
    }

    std::unique_ptr<OutgoingBlockingHttpRequest> job = std::make_unique<typename Jobs::Renew>(m_handlerOfRenewJobs, subscriptionId, *subMan);

    if (auto queue = m_outgoingJobQueue.lock())
    {
        queue->addAsyncJob(DFL::asNotNull(std::move(job)));
    }
}

template<class Jobs>
boost::optional<const WSEventingClientSubscription> WSEventingClientSubscriptionManagerImpl<Jobs>::findSubscription(const WSEventingClientSubscriptionId& subscriptionId) const
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    return findSubscriptionNoLock(subscriptionId);
}

template<class Jobs>
boost::optional<const WSEventingClientSubscription> WSEventingClientSubscriptionManagerImpl<Jobs>::findSubscriptionNoLock(const WSEventingClientSubscriptionId& subscriptionId) const
{
    auto it = m_subscriptions.find(subscriptionId.get());
    if (it != m_subscriptions.end())
    {
        return it->second;
    }

    return boost::none;
}

template<class Jobs>
DFL::Chrono::Seconds WSEventingClientSubscriptionManagerImpl<Jobs>::getExpirationTime(DFL::Chrono::Seconds expirationInSeconds)
{
    return WSEventingClientSubscriptionManagerImpl::getSteadyClock() + DFL::Chrono::Seconds(expirationInSeconds);
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::triggerGetStatus(const WSEventingClientSubscriptionId& subscriptionId)
{
    removeExpiredSubscriptions();

    std::shared_ptr<GsoapEpr> subMan;
    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        if (auto subscription = findSubscriptionNoLock(subscriptionId))
        {
            subMan = subscription->getRemoteSubscriptionManager();
        }
    }

    if (!subMan)
    {
        return;
    }

    if (!m_handlerOfGetStatusJobs)
    {
        m_handlerOfGetStatusJobs = this->Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingGetStatusJobResult>::makeOutcomeHandler(
            [&](typename Utils::OutcomeConsumer<WSEventingClientSubscriptionManagerImpl<Jobs>, WSEventingGetStatusJobResult>::OutcomeType& outcome)
            {
                if (!outcome.hasError())
                {
                    auto result = outcome.result();
                    this->networkResponse(result->subscriptionId, std::shared_ptr<GsoapEpr>(), result->duration, DFL::Crypto::DistinguishedName{});
                }
                else
                {
                    this->removeSubscription(outcome.error());
                }
            });
    }

    std::unique_ptr<OutgoingBlockingHttpRequest> job = std::make_unique<typename Jobs::GetStatus>(m_handlerOfGetStatusJobs, subscriptionId, *subMan);

    if (auto queue = m_outgoingJobQueue.lock())
    {
        queue->addAsyncJob(DFL::asNotNull(std::move(job)));
    }
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::networkResponse(const WSEventingClientSubscriptionId& subscriptionId,
                                                                    const std::shared_ptr<GsoapEpr>& optionalSubscriptionManager,
                                                                    DFL::Chrono::Seconds expiration,
                                                                    const DFL::Crypto::DistinguishedName& optionalRemoteDeviceDistinguishedName)
{
    std::shared_ptr<IWSEventingClientListener> listener;
    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        auto it = m_subscriptions.find(subscriptionId.get());
        if (it != m_subscriptions.end())
        {
            listener = it->second.getCallback();

            if (optionalSubscriptionManager)
            {
                it->second.setRemoteSubscriptionManager(optionalSubscriptionManager);
            }

            it->second.setExpirationTime(getExpirationTime(expiration));

            // Empty distinguished name indicates this is not the start of a subscription
            // (maybe a renew or status check instead), so logging is not required.
            if (optionalRemoteDeviceDistinguishedName.commonName())
            {
                it->second.remoteDeviceDistinguishedName(optionalRemoteDeviceDistinguishedName);
                logSubscriptionStart(it->second);
            }
        }
    }
    if (listener)
    {
        listener->expirationResponse(expiration);
    }
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::subscriptionEnd(const WSEventingClientSubscriptionId& subscriptionId,
                                                                    SubscriptionEndStatus status,
                                                                    const DFL::Mdib::LocalizedTexts& reason)
{
    removeSubscription(subscriptionId, status, reason);
}

template<class Jobs>
boost::optional<const WSEventingClientSubscription> WSEventingClientSubscriptionManagerImpl<Jobs>::getAndEraseSubscription(const WSEventingClientSubscriptionId& id)
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    if (auto subscription = findSubscriptionNoLock(id))
    {
        m_subscriptions.erase(id.get());
        return subscription;
    }
    return boost::none;
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::removeSubscription(const WSEventingClientSubscriptionId& subscriptionId,
                                                                       SubscriptionEndStatus status)
{
    removeSubscription(subscriptionId, status, DFL::Mdib::LocalizedTexts{});
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::removeSubscription(
      const WSEventingClientSubscriptionId& id,
      SubscriptionEndStatus status,
      const DFL::Mdib::LocalizedTexts& reason)
{
    if (reason.empty())
    {
        S31_STREAM_INFO_LOGGER("Soap.WS", "Client: WS-Eventing: ", id, " ended with status ", status);
    }
    else
    {
        S31_STREAM_INFO_LOGGER("Soap.WS", "Client: WS-Eventing: ", id, " ended with status ", status, ", reason: ", reason);
    }

    if (auto subscription = getAndEraseSubscription(id))
    {
        DFL::Locale::Utf8 reasonConverted;
        if (!reason.empty())
        {
            S31::Utils::Utf8AppenderStream s(reasonConverted);
            s << reason;
        }

        logSubscriptionEnd(*subscription, status, reasonConverted);

        if (auto listener = subscription->getCallback())
        {
            listener->subscriptionEnd(status, reasonConverted);
        }
    }
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::removeSubscription(const Utils::Error& error)
{
    WSEventingClientSubscriptionId id("UNKNOWN_SUBSCRIPTION_ID");
    if (auto e = error.is<Errors::WSSubscribeError>())
    {
        id = WSEventingClientSubscriptionId(e->subscriptionId);
    }
    if (auto e = error.is<Errors::WSUnsubscribeError>())
    {
        id = WSEventingClientSubscriptionId(e->subscriptionId);
    }
    if (auto e = error.is<Errors::WSRenewError>())
    {
        id = WSEventingClientSubscriptionId(e->subscriptionId);
    }
    if (auto e = error.is<Errors::WSGetStatusError>())
    {
        id = WSEventingClientSubscriptionId(e->subscriptionId);
    }

    if (auto subscription = getAndEraseSubscription(id))
    {
        logSubscriptionEnd(*subscription, SubscriptionEndStatus::OTHER_ERROR, error.message());

        if (auto listener = subscription->getCallback())
        {
            listener->handleError(error);
        }
        else
        {
            handleError(error);
        }
    }
}

template<class Jobs>
size_t WSEventingClientSubscriptionManagerImpl<Jobs>::size() const
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    return m_subscriptions.size();
}

template<class Jobs>
bool WSEventingClientSubscriptionManagerImpl<Jobs>::empty() const
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    return m_subscriptions.empty();
}

template<class Jobs>
WSEventingClientSubscriptionId WSEventingClientSubscriptionManagerImpl<Jobs>::createId()
{
    return WSEventingClientSubscriptionId("client-sub-id-" + DFL::Crypto::generateRandomUuidString());
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::removeExpiredSubscriptions()
{
    for (;;)
    {
        std::string subscriptionId;
        std::string message;
        {
            message.clear();
            std::lock_guard<std::mutex> const guard(m_mutex);
            // find first expired subscription
            for (const auto & m_subscription : m_subscriptions)
            {
                if (m_subscription.second.isExpired(WSEventingClientSubscriptionManagerImpl::getSteadyClock(), message))
                {
                    subscriptionId = m_subscription.first;
                    break;
                }
            }
        }
        if (!subscriptionId.empty())
        {
            removeSubscription(
                        WSEventingClientSubscriptionId(subscriptionId),
                        SubscriptionEndStatus::SUBSCRIPTION_EXPIRED,
                        {DFL::Mdib::LocalizedText(DFL::Locale::Utf8(message))});
        }
        else
        {
            // no more expired subscriptions
            break;
        }
    }
}

template<class Jobs>
DFL::Chrono::Seconds WSEventingClientSubscriptionManagerImpl<Jobs>::getSteadyClock()
{
    return DFL::Chrono::duration_cast<DFL::Chrono::Seconds>(DFL::Chrono::SteadyClock::now().time_since_epoch());
}

template<class Jobs>
std::map<std::string, WSEventingClientSubscription> WSEventingClientSubscriptionManagerImpl<Jobs>::getSubscriptionList() const
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    return m_subscriptions;
}

template<class Jobs>
std::string WSEventingClientSubscriptionManagerImpl<Jobs>::toString(const WSEventingClientSubscription& clientSubscription) const
{
    std::ostringstream str;
    str << "ClientSubscription[client-id: " << clientSubscription.getId();

    if (auto remEpr = clientSubscription.getRemoteSubscriptionManager())
    {
        str << "; remote-epr-addr: " << remEpr->getAddress();
    }

    str << "]";
    return str.str();
}

template<class Jobs>
std::string WSEventingClientSubscriptionManagerImpl<Jobs>::shortActionList(const SoapActions& actions)
{
    std::string result;
    for (const auto& action : actions)
    {
        if (!result.empty())
        {
            result.append(",");
        }
        result.append(action.substr(action.find_last_of('/') + 1));
    }
    return result;
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::handleError(const Utils::Error& error)
{
    // Error of unknown provenance - it was not possible to map the given error to something known
    // (no subscription id available)
    // Only log error message to make error visible in the unlikely case it ever comes up
    S31_STREAM_WARN_LOGGER("Soap.WS", error.message());
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::logSubscriptionStart(const WSEventingClientSubscription& clientSubscription) const
{
    S31_SECURITY_LOG(S31::Log::SecurityEventCodes::SubscriptionOfSdcConsumer,
                     {
                         S31::Log::KeyValue("dn", clientSubscription.remoteDeviceDistinguishedName()),
                         S31::Log::KeyValue("status", "Active"),
                         S31::Log::KeyValue("id", clientSubscription.getId()),
                         S31::Log::KeyValue("actions", shortActionList(clientSubscription.getActions())),
                     },
                     "Client subscription started.");
}

template<class Jobs>
void WSEventingClientSubscriptionManagerImpl<Jobs>::logSubscriptionEnd(const WSEventingClientSubscription& clientSubscription, SubscriptionEndStatus endStatus, const DFL::Locale::Utf8& reason) const
{
    // Check that the subscription was started before logging that it has ended.
    // Remote device common name is set at subscription start.
    if (!clientSubscription.remoteDeviceDistinguishedName().commonName())
    {
        return;
    }

    S31_SECURITY_LOG(S31::Log::SecurityEventCodes::SubscriptionOfSdcConsumer,
                     {
                         S31::Log::KeyValue("dn", clientSubscription.remoteDeviceDistinguishedName()),
                         S31::Log::KeyValue("status", endStatus),
                         S31::Log::KeyValue("id", clientSubscription.getId()),
                     },
                     "Client subscription ended. ", reason);
}

}
