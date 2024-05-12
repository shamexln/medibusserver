#pragma once

#include <S31/Nomenclature/Public/Roles.h>
#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapEventSourceBindingService.h>

#include <Framework/Utils/Public/Oids.h>

#include <memory>

namespace S31::Sdc::Impl
{

class IWSEventingSubscriptionManager;

/**
 * @brief Implementation of WS-Eventing messages on DPWS device side
 * (Event Source and Subscription Manager).
 *
 * @ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP DeviceSubscriptionDispatcher: private EventSourceBindingService
{
    public:
        // gSOAP assign and copy do not work as expected (Coverity findings)
        DeviceSubscriptionDispatcher(const DeviceSubscriptionDispatcher&) = delete;
        DeviceSubscriptionDispatcher& operator=(const DeviceSubscriptionDispatcher&) = delete;

        DeviceSubscriptionDispatcher(
                struct soap*                                                    soap,
                std::shared_ptr<S31::Sdc::Impl::IWSEventingSubscriptionManager> registry,
                DFL::Oids                                                       requiredRoles = DFL::Oids{
                        Nomenclature::SdcServiceConsumer, Nomenclature::DraegerSpecificSdcConsumer});

        int dispatch() override;    // uses internal soap handle
        int dispatch(struct soap* soapHandle) override;

    private:
        /**
         * @brief Do not use!
         * @details
         * Copy is not supported by gSOAP. S31 does not want to add copy support. Thus, this class is not copyable.
         */
        DeviceSubscriptionDispatcher* copy() override;

        int SubscribeOp(_wse4__Subscribe* subscribe, _wse4__SubscribeResponse& subscribeResponse) override;
        int SubscribeOpResponse(_wse4__SubscribeResponse* subscribeResponse) override;
        int SubscriptionEnd(_wse4__SubscriptionEnd* wse4SubscriptionEnd) override;
        int RenewOp(_wse4__Renew* renew, _wse4__RenewResponse& renewResponse) override;
        int RenewOpResponse(_wse4__RenewResponse* renewResponse) override;
        int GetStatusOp(_wse4__GetStatus* getStatus, _wse4__GetStatusResponse& getStatusResponse) override;
        int GetStatusOpResponse(_wse4__GetStatusResponse* getStatusResponse) override;
        int UnsubscribeOp(_wse4__Unsubscribe* unsubscribe, struct __wse4__UnsubscribeOpResponse& empty) override;
        int UnsubscribeOpResponse() override;

        static int prepareDestinationUnreachableFault(
                struct soap* soapHandle, const std::string& reason, const std::string& address);

        const std::shared_ptr<S31::Sdc::Impl::IWSEventingSubscriptionManager> m_registry;
        const DFL::Oids                                                       m_requiredRoles;
};

}
