#pragma once

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace S31::Sdc::Impl
{
class IOutgoingMessage;

/**
 * @brief Boundary interface for outgoing network events (e.g., firing WS-Eventing messages).
 *
 * @details Typically it is attached to a network node (e.g. DPWS device) that manages subscriptions internally.
 *
 * \ingroup S31SdcDevice
 */
class ILocalEventing
{
    public:
        virtual ~ILocalEventing() noexcept = default;

        /**
         * Checks if at least one subscriber for the given action URI is subscribed.
         *
         * It is a shortcut to skip the creation of outgoing messages in case there is no subscriber.
         */
        virtual bool hasEventListenerForAction(std::string_view actionUri) const = 0;
        /**
         * Checks whether there exists a subscriber for any SOAP action.
         *
         * @return \c true is there is at least one subscriber for any SOAP action.
         */
        virtual bool hasEventListenerForAnyAction() const = 0;
        /**
         * Outgoing messages given to this method are send out to the network as event messages.
         * @param event Takes ownership of this message to send out.
         */
        virtual void fireEvent(DFL::NotNull<std::unique_ptr<S31::Sdc::Impl::IOutgoingMessage>> event) = 0;

        /**
         * Sets WS-Discovery scopes for the given locations.
         */
        virtual void setDiscoveryLocationScopes(const std::vector<std::string>& locations) = 0;

        /**
         * Sets WS-Discovery scopes for the given Mds information. This includes types and metaData information like Manufacturer, ModelName and DeviceName
         */
        virtual void setDiscoveryMdsInfoScopes(const std::vector<std::string>& types) = 0;

        /**
         * Notification that a component report will start delivery to available WS-Eventing subscribers with the indicated mdib version.
         */
        virtual void componentReportDeliveryStarting(const DFL::Mdib::MdibVersion& version) = 0;

        /**
         * Notification that a component report has completed delivery to available WS-Eventing subscribers with the indicated version.
         */
        virtual void componentReportDeliveryCompleted(const DFL::Mdib::MdibVersion& version) noexcept = 0;
};

}
