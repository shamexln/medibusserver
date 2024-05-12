#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/EncodingType.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>
#include <S31/Sdc/Private/Common/Http/HttpResult.h>
#include <S31/Sdc/Private/Common/Http/HttpResultCallback.h>
#include <S31/Sdc/Private/Common/Http/HttpServerHandler.h>
#include <S31/Sdc/Private/Common/DsoapCommon/SoapViewTypes.h>
#include <S31/Sdc/Private/Device/IHostedServicePlugin.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionEndReason.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionFilterHandler.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <chrono>
#include <optional>
#include <string_view>

namespace S31::Sdc::Impl
{
class HttpClient;

struct SubscriptionIdViewTag;
using SubscriptionIdView = DFL::
        StrongTypedef<std::string_view, SubscriptionIdViewTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;

class SubscribeHandler
{
public:
    virtual ~SubscribeHandler() = default;

    struct Result
    {
        bool         isSuccess{false};
        EncodingType notificationEncoding{EncodingType::None};

        /// Not empty in case of error.
        DFL::Locale::Utf8 errorMessage;

        /// Qname for filter error
        SubscriptionErrorCode errorQname;

        explicit operator bool() const noexcept
        {
            return isSuccess;
        }

        /**
         * @brief Optional function to execute after subscription has been added to the system.
         * @details
         * This could be used for initial notification for example. It is not possible to notify a message from within
         * the subscribe call.
         */
        std::function<void()> exitFunction;
    };

    struct RequestView
    {
        /**
         * @brief Construct a request object with view types.
         * @details
         * It is designed as a container to bundle relevant information in the subscribe() call and make it easily
         * extendable.
         */
        explicit RequestView(DFL::NotNull<std::shared_ptr<const HttpSessionContext>> context)
            : sessionContext{std::move(context)}
        {
        }

        /**
         * @brief The type of filter (if any).
         * @details
         * Typical values are http://www.w3.org/TR/1999/REC-xpath-19991116 (the implied value) or
         * http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/Action (DPWS 1.1 action filter).
         * If it is empty there is no filter given at all.
         */
        std::string_view filterDialect;

        /**
         * @brief Content of the \<wse:Filter\> element.
         * @details
         * The content might be simple text or an XML element depending on the filter dialect and what is used as
         * xsd:any payload.
         */
        std::string_view filterContent;

        /**
         * @brief Id for this subscription.
         * @details An id is already assigned that will be used for further message handling.
         *
         */
        SubscriptionIdView subscriptionId;

        EncodingType requestedEncoding{EncodingType::None};

        /**
         * @brief HTTP session information.
         */
        DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext;
    };

    /**
     * @brief Will be called for each new WS-Eventing Subscribe message (from the network).
     * @details
     * An implementation is free to abort such a subscribe request, e.g., if too many subscriptions exists or the
     * requested filter does not fit.
     */
    virtual Result subscribe(const RequestView& request) = 0;

    enum class EndReason
    {
        SubscriptionExpired,
        ClientUnsubscribed,
        DeliveryFailure,
        SourceShuttingDown,
        SourceCancelling
    };
    struct EndData
    {
        SubscriptionIdView subscriptionId;

        EndReason endReason;

        /**
         * @brief Helper function to check for graceful end reason.
         */
        [[nodiscard]] bool gracefulEnd() const
        {
            return endReason != EndReason::DeliveryFailure;
        }

        /**
         * @brief Optional message for reason.
         * @details Typically filled with error details.
         */
        std::string_view reasonMessage;
    };

    /**
     * @brief Information about the end of a subscription.
     * @details
     * This function will only be called for situation that are not explicitly request locally.
     * These are subscription expiration, unsubscribe and transmission errors.
     * If \c endSubscription() was called to explicitly end a subscription no such call will be made.
     * Also in case of destruction no callback will be made.
     * To gracefully end a subscription call \c endSubscription with \c SubscriptionEndReason::SourceShuttingDown for
     * example.
     */
    virtual void subscriptionEnded(const EndData& endData) = 0;
};

DFL_ENUM_CLASS_STREAM_OPERATOR(
        SubscribeHandler::EndReason,
        (SubscriptionExpired)(ClientUnsubscribed)(DeliveryFailure)(SourceShuttingDown)(SourceCancelling))

/**
 * @brief Interface for an individual notification result.
 * @details
 * With this interface it is possible to get informed about he outcome of a notification, if it succeeded or failed.
 * Exactly one of the two function will be called. Some implementations want to use this information to schedule the
 * next notification for example to enforce in oder delivery.
 *
 * @ingroup S31SdcDevice
 */
class NotificationResultHandler
{
public:
    virtual ~NotificationResultHandler() = default;

    /**
     * @brief This function will be called when the notification was successfully transmitted to the event sink.
     * @details
     * If there are multiple notifications pending in a queue, this callback could be used to send the next message from
     * the queue.
     * @param id The identifier for the subscription. Can be used for dispatching in case the same callback will be used
     * for multiple subscriptions.
     */
    virtual void notificationSucceeded(SubscriptionIdView id) = 0;

    /**
     * @brief Notification result reasons in case of a failed transmission.
     * @details Different reasons might be responsible why a notification might fail. This starts from an unknown
     * subscription identifier used for notification (typically an internal error) up to a transmission/network error
     * that results in a delivery failure.
     */
    enum class Reason
    {
        /**
         * @brief The subscription (identifier) is not known to the eventing handler, so it cannot be delivered.
         */
        UnknownSubscription,

        /**
         * @brief The subscription is not valid anymore, it already ended in the past.
         * @details
         * This typically happens in race condition scenarios, like sending a notification while a client unsubscribes
         * or the subscription expired meanwhile.
         */
        EndedSubscription,

        /**
         * @brief This notification failed due to network or communication issues.
         */
        DeliveryFailed
    };

    /**
     * @brief The message was not notified due to the given reason.
     *
     * @param id The identifier for the subscription. Can be used for dispatching in case the same callback will be used
     * for multiple subscriptions.
     * @param reason End reason as enum value
     * @param detailMessage Optional end message, might be empty. Could provide detailed information for delivery
     * failure for exmaple.
     */
    virtual void notificationFailed(SubscriptionIdView id, Reason reason, std::string_view detailMessage) = 0;
};

DFL_ENUM_CLASS_STREAM_OPERATOR(
        NotificationResultHandler::Reason, (UnknownSubscription)(EndedSubscription)(DeliveryFailed))


/**
 * @brief WS-Eventing implementation for the device side.
 * @details
 * This class handles the XML processing of WS-Eventing messages including the subscription handling.
 * It does not include HTTP server or client functionality.
 *
 * Required dependencies like a subscription handler (e.g., based on filters) as well as HTTP client functionality are
 * passed in the constructor.
 * Incoming WS-Eventing messages as well as notifying or ending subscriptions has to be done by calling the
 * corresponding functions.
 *
 * The implementation does not queue notifications to send them in order nor limits the number of subscriptions. This
 * needs to be done by the injected \ref SubscribeHandler (if required).
 * Retransmission support is available due to the fact that the HTTP client supports it for smoothly working keep-alive
 * connections. Keep-alive connection might timeout when starting to re-use them what requires a retry.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP WSEventingHandler : public IHostedServicePlugin
{
public:
    /**
     * @brief Construct a new WS-Eventing SOAP message handler.
     * @details
     * This WS-Eventing instance has no configuration to support different filters at the same time for example.
     * An instance might want to have different subscriptions at the same endpoint (URL). Therefore the subscribeHandler
     * is able to dispatch, if it wants to.
     *
     * @param subscribeHandler Implementation that handles the subscribe requests.
     * @param httpClient HTTP client to be used for notification and WS-Eventing SubscriptionEnd messages.
     */
    WSEventingHandler(
            DFL::NotNull<std::shared_ptr<SubscribeHandler>> subscribeHandler, std::weak_ptr<HttpClient> httpClient);

    /**
     * @brief Starts sending the message asynchronously via the network.
     */
    void notifyMessage(
            SubscriptionIdView                         subscriptionId,
            SoapActionView                             soapActionUri,
            SoapMessageBodyView                        xmlSoapBody,
            std::shared_ptr<NotificationResultHandler> resultHandler);

    /**
     * @brief End a subscription from the device side.
     * @details
     * A typical scenario is shutting down the event source.
     *
     * @param subscriptionId
     * @param subscriptionEndReason
     * @param optionalEndDetailMessage
     */
    void endSubscription(
            SubscriptionIdView    subscriptionId,
            SubscriptionEndReason subscriptionEndReason,
            std::string_view      optionalEndDetailMessage = std::string_view{});

    /**
     * @brief Entry point for SOAP messages to handle.
     */
    int dispatch(struct soap* soapHandle) override;

    /**
     * @brief Gracefully shutdown all subscription with SubscriptionEnd message.
     * @details
     * Before destroying the instance a call to this function gracefully shutdowns all subscriptions.
     * Otherwise, no graceful shutdown is performed.
     */
    void deviceShuttingDown() override;

    /**
     * @brief Provide name for debugging.
     */
    std::string pluginName() const override;

private:
    class Impl;
    DFL::NotNull<std::shared_ptr<Impl>> m_impl;
};
}  // namespace S31::Sdc::Impl
