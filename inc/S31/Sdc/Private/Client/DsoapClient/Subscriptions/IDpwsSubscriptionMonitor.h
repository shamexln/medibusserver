#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Utils/Public/Errors.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface to notify a specific subscription as active.
 *
 * @ingroup S31SdcClient
 */
class IDpwsSubscriptionMonitor: public Utils::ErrorHandler
{
    public:
        ~IDpwsSubscriptionMonitor() noexcept override = default;

        /**
         * @brief Inform monitor about the now active subscription.
         *
         * @details
         * This call can allow the subscription monitor to activate set operations
         * to avoid races between subscription for invocation reports and the first
         * set command.
         */
        virtual void setSubscriptionActive(Sdc::Impl::WSEventingClientSubscriptionId subscriptionId) = 0;
};

}
