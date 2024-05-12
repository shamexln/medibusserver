#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Client/WS-Eventing/EventSinkService.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionManagerImpl.h>
#include <S31/Sdc/Private/Common/StackConstants.h>
#include <S31/Base/S31Only/Exception.h>

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>

#include <stdexcept>
#include <utility>

namespace S31::Sdc::Impl
{

template<class SubscriptionManager>
EventSinkService<SubscriptionManager>::EventSinkService(
            struct soap* soapHandle,
            std::shared_ptr<SubscriptionManager> subscriptionManager,
            std::string clientSubscriptionIdentifier) :
        EventSourceBindingService(soapHandle),
        m_subscriptionManager(std::move(subscriptionManager)),
        m_clientSubscriptionIdentifier(std::move(clientSubscriptionIdentifier))
{
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::dispatch()
{
    return EventSourceBindingService::dispatch();
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::dispatch(struct soap* soapDispatch)
{
    return EventSourceBindingService::dispatch(soapDispatch);
}

// do NOT use!
// We can not copy the internal soap struct without side effects!
template<class SubscriptionManager>
EventSinkService<SubscriptionManager>* EventSinkService<SubscriptionManager>::copy()
{
    S31_STREAM_ERROR_LOGGER("Soap", "Do not use the copy function. We can not make a copy without side effects.");
    S31_THROW_EXCEPTION(
            InternalResourceMissing, "Do not use the copy function. We can not make a copy without side effects.");
}

static boost::optional<DFL::Locale::LanguageTag> toOptionalLanguageTag(const std::optional<std::string>& optTag)
{
    if (optTag)
    {
        return DFL::Locale::LanguageTag(*optTag);
    }
    return {};
}

static DFL::Mdib::LocalizedTexts toLocalizedTexts(const std::vector<std::shared_ptr<wse4__LanguageSpecificStringType>>& source)
{
    DFL::Mdib::LocalizedTexts dest;
    for (const auto& entry : source)
    {
        dest.push_back(DFL::Mdib::LocalizedText(DFL::Locale::Utf8(entry->__item), toOptionalLanguageTag(entry->xml__lang)));
    }
    return dest;
}

static SubscriptionEndStatus toSubscriptionEndStatus(const std::string& endStatus)
{
    if (endStatus == StackConstants::WS_EVENTING_SUBSCRIPTIONEND_STATUS_SOURCESHUTTINGDOWN)
    {
        return SubscriptionEndStatus::SOURCE_SHUTTING_DOWN;
    }
    if (endStatus == StackConstants::WS_EVENTING_SUBSCRIPTIONEND_STATUS_DELIVERYFAILURE)
    {
        return SubscriptionEndStatus::DELIVERY_FAILURE;
    }
    return SubscriptionEndStatus::SOURCE_CANCELLED;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::SubscriptionEnd(_wse4__SubscriptionEnd* wse4SubscriptionEnd)
{
    if (m_clientSubscriptionIdentifier.empty())
    {
        // "eat" SubscriptionEnd messages, that we cannot process,
        // since we already have removed the subscription (local unsubscribe for example).
        return soap_send_empty_response(wse4SubscriptionEnd->soap, 202);
    }
    WSEventingClientSubscriptionId const subId(m_clientSubscriptionIdentifier);
    m_subscriptionManager->subscriptionEnd(subId,
                                           toSubscriptionEndStatus(wse4SubscriptionEnd->Status),
                                           toLocalizedTexts(wse4SubscriptionEnd->Reason));
    return soap_send_empty_response(wse4SubscriptionEnd->soap, 202);
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::SubscribeOp(_wse4__Subscribe*, _wse4__SubscribeResponse&)
{
    return SOAP_NO_METHOD;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::SubscribeOpResponse(_wse4__SubscribeResponse*)
{
    return SOAP_NO_METHOD;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::RenewOp(_wse4__Renew*, _wse4__RenewResponse&)
{
    return SOAP_NO_METHOD;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::RenewOpResponse(_wse4__RenewResponse*)
{
    return SOAP_NO_METHOD;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::GetStatusOp(_wse4__GetStatus*, _wse4__GetStatusResponse&)
{
    return SOAP_NO_METHOD;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::GetStatusOpResponse(_wse4__GetStatusResponse*)
{
    return SOAP_NO_METHOD;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::UnsubscribeOp(_wse4__Unsubscribe*, struct __wse4__UnsubscribeOpResponse&)
{
    return SOAP_NO_METHOD;
}

template<class SubscriptionManager>
int EventSinkService<SubscriptionManager>::UnsubscribeOpResponse()
{
    return SOAP_NO_METHOD;
}

}
