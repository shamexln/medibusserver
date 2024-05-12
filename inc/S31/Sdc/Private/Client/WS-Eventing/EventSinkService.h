#pragma once

#include <S31/Gsoap/S31Only/generated/gsoap/soapEventSourceBindingService.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Implementation of WS-Eventing messages on DPWS client side (Event Sink).
 *
 * \ingroup S31SdcClientEventing
 */
template<class SubscriptionManager>
class EventSinkService: private EventSourceBindingService
{
        // gSOAP assign and copy do not work as expected (Coverity findings)
        DFL_NOT_COPYABLE(EventSinkService)
    public:

        EventSinkService(struct soap* soapHandle, std::shared_ptr<SubscriptionManager> subscriptionManager,
                std::string clientSubscriptionIdentifier);

        int dispatch() override;    // uses internal soap handle
        int dispatch(struct soap* soapDispatch) override;

    private:
        EventSinkService<SubscriptionManager>* copy() override;    ///< do not use!
        int SubscribeOp(_wse4__Subscribe* subscribe, _wse4__SubscribeResponse& subscribeResponse) override;
        int SubscribeOpResponse(_wse4__SubscribeResponse* subscribeResponse) override;
        int SubscriptionEnd(_wse4__SubscriptionEnd* wse4SubscriptionEnd) override;
        int RenewOp(_wse4__Renew* renew, _wse4__RenewResponse& renewResponse) override;
        int RenewOpResponse(_wse4__RenewResponse* renewResponse) override;
        int GetStatusOp(_wse4__GetStatus* getStatus, _wse4__GetStatusResponse& getStatusResponse) override;
        int GetStatusOpResponse(_wse4__GetStatusResponse* getStatusResponse) override;
        int UnsubscribeOp(_wse4__Unsubscribe* unsubscribe, struct __wse4__UnsubscribeOpResponse& empty) override;
        int UnsubscribeOpResponse() override;

        std::shared_ptr<SubscriptionManager> m_subscriptionManager;
        std::string m_clientSubscriptionIdentifier;

};

}
