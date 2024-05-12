#pragma once

#include <string>
#include <S31/Sdc/Public/Client/MdibSubscriptionType.h>

namespace S31::Sdc
{

class EndpointReference;

namespace Impl
{

/**
 * @brief Observer of eventing subscriptions on a certain device/node.
 *
 * @ingroup S31SdcClient
 */
class DpwsSubscriptionOnRemoteDeviceObserver
{
    public:
        virtual ~DpwsSubscriptionOnRemoteDeviceObserver() = default;

        /**
         * @brief Notification that the subscription for Mdib updates is active(running) with the given type.
         *
         * It's not required that the subscription is changed between calls. (also allowed on RENEW)
         */
        virtual void mdibUpdatesSubscriptionActive(const S31::Sdc::EndpointReference& endpointReference) = 0;

        /**
         * @brief Notification that the subscription invocation reports is active.
         *
         * It's not required that the subscription is changed between calls. (also allowed on RENEW)
         */
        virtual void setServiceSubscriptionActive(const S31::Sdc::EndpointReference& endpointReference) = 0;
};

}
}
