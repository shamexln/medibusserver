#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/OutgoingUnicastMessageContext.h>
#include <S31/Utils/Public/Errors.h>

#include <boost/optional/optional.hpp>

#include <any>
#include <string>

namespace S31::Sdc::Impl::Errors
{

/**
 * @brief Thrown if retrieving a DPWS device's metadata failed.
 * @ingroup S31SdcCommon
 */
struct GetDeviceMetadataProcessing: Utils::SpecificError
{
};

/**
 * @brief Thrown if resolving a DPWS device's physical addresses failed.
 * @ingroup S31SdcCommon
 */
struct ResolveXAddrs: Utils::SpecificError
{
};

/**
 * @brief Thrown if the endpoint reference from unsecure channel mismatches the endpoint reference from secure channel.
 * @ingroup S31SdcCommon
 */
struct EndpointReferenceMismatch: Utils::SpecificError
{
};

/**
 * @brief Thrown if XAddrs are empty.
 * @ingroup S31SdcCommon
 */
struct XAddrsEmpty: Utils::SpecificError
{
};

/**
 * @brief Thrown if there was no supported URI scheme found.
 * @ingroup S31SdcCommon
 */
struct NoSupportedUriScheme: Utils::SpecificError
{
};

/**
 * @brief Thrown if there was no executor found for the BICEPS get service.
 * @ingroup S31SdcCommon
 */
struct MissingGetServiceExecutor: Utils::SpecificError
{
};

/**
 * @brief Thrown if there was no executor found to subscribe for events.
 * @ingroup S31SdcCommon
 */
struct MissingEventSourceExecutor: Utils::SpecificError
{
};

/**
 * @brief Thrown if an expected set of associated location contexts does not match an actual set of associated location contexts.
 * @ingroup S31SdcCommon
 */
struct LocationContextMismatch: Utils::SpecificError
{
};

/**
 * @brief Thrown if any unexpected non-restorable system state reached.
 * @ingroup S31SdcCommon
 */
struct Unexpected: Utils::SpecificError
{
};

/**
 * @brief Thrown if there was at least one resolvable physical address expected, but none found.
 * @ingroup S31SdcCommon
 */
struct MissingPhysicalAddress: Utils::SpecificError
{
};

/**
 * @brief The OutgoingBlockingHttpRequest could not get a pointer to a valid soap structure.
 * @details Expected error during shutdown.
 * @ingroup S31SdcCommon
 */
struct NoSoapHandle: Utils::SpecificError
{
};

/**
 * @brief The OutgoingBlockingHttpRequest could not get an HttpClient.
 * @details Expected error during shutdown.
 * @ingroup S31SdcCommon
 */
struct NoHttpClient: Utils::SpecificError
{
};

/**
 * @brief Thrown if there was no hosted service that included a report or if R0034 of SDC Glue was violated for a remote device.
 * @ingroup S31SdcCommon
 */
struct InvalidHostedServiceConfiguration: Utils::SpecificError
{
};

/**
 * @brief A report from network has a Mdib version with a new sequence.
 * @details This should lead to automatic disconnect/reconnect somewhere.
 * @ingroup S31SdcCommon
 */
struct MdibSequenceChanged: Utils::SpecificError
{
};

/**
 * @brief Localization response has a changed Mdib sequenceId. This error may occur with fast reboot devices.
 * @ingroup S31SdcCommon
 */
struct MdibSequenceIdMismatch: Utils::SpecificError
{
};

/**
 * @brief There are too many received reports in the queue.
 * @ingroup S31SdcCommon
 */
struct ReportQueueOverrun: Utils::SpecificError
{
        std::string endpointRef;
};

/**
 * @brief A part of the incoming data (from network) was skipped because it couldn't be interpreted or contradicts existing data.
 * @ingroup S31SdcCommon
 */
struct IncomingDataNotUnderstood: Utils::SpecificError
{
};

/**
 * @brief The reports received for a new Mdib version are not consistent.
 * @details Allowed are:
 *  - Description modifications, states, ... , states, or
 *  - a single state modification report
 * @ingroup S31SdcCommon
 */
struct WrongReportSequence: Utils::SpecificError
{
};

/**
 * @brief Incoming data contains an unknown must-understand extension.
 * @details The data shall not be used. That may imply a gap in the data stream and therefore may require disconnecting.
 * @ingroup S31SdcCommon
 */
struct UnknownMustUnderstandExtension: Utils::SpecificError
{
};

/**
 * @brief Incoming state has a descriptor version that does not suit existing descriptor.
 * @ingroup S31SdcCommon
 */
struct StateDescriptorVersionMismatch: Utils::SpecificError
{
};

/**
 * @brief Error from WS-Eventing Subscription End job
 * @ingroup S31SdcCommon
 */
struct WSSubscriptionEndError: Utils::SpecificError
{
        std::string subscriptionId;
};

/**
 * @brief Error from WS-Eventing Notify job.
 * @details The notification was skipped (never executed/transmitted).
 * @ingroup S31SdcCommon
 */
struct WSNotifyNotExecuted: Utils::SpecificError
{
        std::string subscriptionId;
};

/**
 * @brief Error from WS-Eventing Notify job
 * @ingroup S31SdcCommon
 */
struct WSNotifyError: Utils::SpecificError
{
        std::string subscriptionId;
};

/**
 * @brief Error from WS-Eventing subscription job
 * @ingroup S31SdcCommon
 */
struct WSSubscribeError: Utils::SpecificError
{
        std::string subscriptionId;
        std::any wrappedError; ///< optional detail
};

/**
 * @brief Error from WS-Eventing unsubscribe job
 * @ingroup S31SdcCommon
 */
struct WSUnsubscribeError: Utils::SpecificError
{
        std::string subscriptionId;
        std::any wrappedError; ///< optional detail
};

/**
 * @brief Error from WS-Eventing renew job
 * @ingroup S31SdcCommon
 */
struct WSRenewError: Utils::SpecificError
{
        std::string subscriptionId;
        std::any wrappedError; ///< optional detail
};

/**
 * @brief Error from WS-Eventing GetStatus job
 * @ingroup S31SdcCommon
 */
struct WSGetStatusError: Utils::SpecificError
{
        std::string subscriptionId;
        std::any wrappedError; ///< optional detail
};

/**
 * @brief Subscription is already ended - which was not expected.
 * @details Used in context of subscription watchdog.
 * @ingroup S31SdcCommon
 */
struct SubscriptionUnexpectlyEnded: Utils::SpecificError
{
};

/**
 * @brief A subscription was canceled by the device
 * @ingroup S31SdcCommon
 */
struct SubscriptionCanceledByDevice: Utils::SpecificError
{
};

/**
 * @brief Designates an SSL error.
 * @ingroup S31SdcCommon
 */
struct Ssl: Utils::SpecificError
{
};

/**
 * @brief Designates a TCP error.
 * @ingroup S31SdcCommon
 */
struct Tcp: Utils::SpecificError
{
};

/**
 * @brief Specific error for gSOAP's SOAP_EOF error code.
 * @details Generally this is a (TCP) communication error. One specific reason is (observed) that the
 * communication partner closed the connection due to SSL handshake failure. We use this for specific
 * error message in this case.
 * @ingroup S31SdcCommon
 */
struct GsoapEof: Utils::SpecificError
{
};

/**
 * @brief Specific error for gSOAP's SOAP_CLI_FAULT error code.
 * @ingroup S31SdcCommon
 */
struct GsoapClientFault: Utils::SpecificError
{
};

/**
 * @brief Specific error for gSOAP's SOAP_SVR_FAULT error code.
 * @ingroup S31SdcCommon
 */
struct GsoapServerFault: Utils::SpecificError
{
};


/**
 * @brief Designates a HTTP error.
 * @ingroup S31SdcCommon
 */
struct Http: Utils::SpecificError
{
        /// HTTP status code, if available, 100..599
        boost::optional<unsigned int> httpStatusCode;
};

/**
 * @brief Payload too large error.
 *
 * @details
 * From 11073-20701-2018:
 *
 * > R0067: An SDC SERVICE PROVIDER SHALL utilize the HTTP status code 413 (payload too large) to indicate
 * > if the response to a request MESSAGE could be satisfied but the content length would exceed the maximal
 * > MESSAGE length defined in MDPWS:R0006.
 *
 * @ingroup S31SdcCommon
 */
struct PayloadTooLarge: Utils::SpecificError
{
};

/**
 * @brief The handling of a previous @ref PayloadTooLarge failed.
 * @details There was a way to to handle a @ref PayloadTooLarge error, e.g. splitting the request to get smaller responses.
 * But this handling failed.
 * @ingroup S31SdcCommon
 */
struct PayloadTooLargeHandlingError: Utils::SpecificError
{
};

/**
 * @brief Gsoap error except SSL/TCP
 * @ingroup S31SdcCommon
 */
struct GsoapGeneric: Utils::SpecificError
{
};

/**
 * @brief Generic system error, from boost::asio
 * @ingroup S31SdcCommon
 */
struct SystemGeneric: Utils::SpecificError
{
    /// System error code, if available
    boost::optional<int> systemErrorCode;
};

/**
 * @brief Error for outgoing unicast job
 * @details Given this error, it is worth retrying to send the message (given the internal retry counter is not exceeded yet).
 * @ingroup S31SdcCommon
 */
struct RetryableOutgoingUnicastError: Utils::SpecificError
{
    OutgoingUnicastMessageContext messageContext;
};

/**
 * @brief Error for misconfiguration of the unicast job
 * @ingroup S31SdcCommon
 */
struct OutgoingUnicastConfigurationError: Utils::SpecificError
{
};

/**
 * @brief Thrown if a Discovery Process via Http exceeds the \ref StackConstants::WS_DISCOVERY_MATCH_TIMEOUT "Match Timeout".
 * @details According to dpws:R4065/4066 a ResolveMatch and ProbeMatch
 *          message must be discarded if it is received after MATCH_TIMEOUT.
 *          This time is absolute and not a receive timeout from the
 *          underlying network socket.
 * @ingroup S31SdcCommon
 */
struct WSDiscoveryMatchTimeoutError: Utils::SpecificError
{
};

/**
 * @brief Thrown if processing a {Probe/Resolve}Match produces no suitable result.
 * @ingroup S31SdcCommon
 */
struct NoSuitableMatchResultError: Utils::SpecificError
{
};

/**
 * @brief Indicates that network peer is not in the whitelist
 * @ingroup S31SdcCommon
 */
struct PeerNotWhitelisted: Utils::SpecificError
{
};

/**
 * @brief Indicates that network peer is missing SDC participant roles
 * @ingroup S31SdcCommon
 */
struct PeerMissingSDCRoles: Utils::SpecificError
{
};

/**
 * @brief Indicates that network peer is missing a TLS certificate
 * @ingroup S31SdcCommon
 */
struct PeerMissingCertificate: Utils::SpecificError
{
};

/**
 * @brief Used by @ref WorkplaceDeviceProvider (WPDP)
 * @details Indicates that a disconnect was triggered by the internal logic of the WPDP (e.g. the device left the configured location)
 * @ingroup S31SdcCommon
 */
struct WorkplaceConnectionLost: Utils::SpecificError
{
};

}
