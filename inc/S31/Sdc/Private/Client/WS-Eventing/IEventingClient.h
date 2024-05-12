#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/SoapAction.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>

#include <Framework/Utils/Public/Utf8.h>

#include <memory>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

class IRemoteHostedServiceEndpoint;
class IWSEventingClientListener;

/**
 * \brief Interface for WS-Eventing client operations.
 *
 * \ingroup S31SdcClientEventing
 */
class IEventingClient
{
    public:
        virtual ~IEventingClient() noexcept = default;

        /**
         * Subscribe to ALL events of that WS-Eventing source.
         * \returns subscription identifier
         */
        virtual WSEventingClientSubscriptionId subscribe(const S31::Sdc::Impl::Endpoint::Executor& endpoint,
                const std::shared_ptr<S31::Sdc::Impl::IWSEventingClientListener>& callback) = 0;

        /**
         * Subscribe to events with specific SOAP actions only.
         * \returns subscription identifier
         */
        virtual WSEventingClientSubscriptionId subscribe(
                const S31::Sdc::Impl::Endpoint::Executor&                         endpoint,
                const SoapActions&                                                actions,
                const std::shared_ptr<S31::Sdc::Impl::IWSEventingClientListener>& callback) = 0;

        /**
         * Triggers an asynchronous WS-Eventing Renew for an existing subscription.
         *
         * Result will be given in the corresponding callback for the subscription.
         */
        virtual void triggerRenew(const WSEventingClientSubscriptionId& id) = 0;

        /**
         * Triggers an asynchronous WS-Eventing GetStatus for an existing subscription.
         *
         * Result will be given in the corresponding callback for the subscription.
         */
        virtual void triggerGetStatus(const WSEventingClientSubscriptionId& id) = 0;

        /**
         * Immediately unsubscribes the given subscription.
         * Asynchronously the event source with get a WS-Eventing Unsubscribe message.
         */
        virtual void unsubscribe(const WSEventingClientSubscriptionId& id, const DFL::Locale::Utf8& reason) = 0;
};

}
