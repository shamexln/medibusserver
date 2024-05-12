#pragma once

#include <S31/Base/S31Only/NtStringView.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/QName.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Constants used in the SOAP communication.
 *
 * @ingroup S31SdcCommon
 */
class StackConstants
{
    public:
        static constexpr NtStringView DEFAULT_MANUFACTURER{"Dr\xC3\xA4gerwerk AG & Co. KGaA"};
        static constexpr NtStringView DEFAULT_MODELNAME{"C++ MDPWS Stack"};

        // An empty string is intended by default: https://jira.draeger.com/browse/PCSWORK-6407
        static constexpr NtStringView DEFAULT_FRIENDLYNAME{""};

        static constexpr int HTTP_STATUS_BAD_REQUEST = 400;
        static constexpr int HTTP_STATUS_NOT_FOUND = 404;
        static constexpr int HTTP_STATUS_PAYLOAD_TOO_LARGE = 413;

        /**
         * @name WS-Discovery
         */
        ///@{

        static constexpr NtStringView WS_DISCOVERY_ENDPOINT_URI_IPV4{"soap.udp://239.255.255.250:3702/"};
        static constexpr NtStringView WS_DISCOVERY_ENDPOINT_URI_IPV6{"soap.udp://[FF02::C]:3702/"};

        static constexpr NtStringView WS_DISCOVERY_ENDPOINT_TO{"urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01"};
        static constexpr NtStringView WS_DISCOVERY_SEQUENCE_ID{"ws-discovery-sequence"};

        static constexpr unsigned short WS_DISCOVERY_PORT = 3702;
        static constexpr NtStringView WS_DISCOVERY_PORT_STRING{"3702"};
        static constexpr NtStringView WS_DISCOVERY_IPV4_MCAST_ADDR{"239.255.255.250"};
        static constexpr NtStringView WS_DISCOVERY_IPV6_MCAST_ADDR{"FF02::C"};
        /** @brief Timeout for Resolve and Probe messages.
         * @details See DPWS 1.1 section 6.5 (WS-Discovery) for its application.
         *          In WS-Discovery it is defined to be 600 milliseconds. However,
         *          it is overwritten in DPWS 1.1 Appendix B to be 10 seconds.
         */
        static constexpr DFL::Chrono::Seconds WS_DISCOVERY_MATCH_TIMEOUT{10};

        static constexpr NtStringView WS_DISCOVERY_SCOPE_MATCHING_RULE_RFC3986{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/rfc3986"};
        static constexpr NtStringView WS_DISCOVERY_SCOPE_MATCHING_RULE_STRCMP0{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/strcmp0"};
        static constexpr NtStringView WS_DISCOVERY_SCOPE_MATCHING_RULE_NONE{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/none"};

        static constexpr NtStringView WS_DISCOVERY_HELLO_ACTION{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Hello"};
        static constexpr NtStringView WS_DISCOVERY_BYE_ACTION{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Bye"};
        static constexpr NtStringView WS_DISCOVERY_PROBE_ACTION{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Probe"};
        static constexpr NtStringView WS_DISCOVERY_PROBE_MATCHES_ACTION{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ProbeMatches"};
        static constexpr NtStringView WS_DISCOVERY_RESOLVE_ACTION{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Resolve"};
        static constexpr NtStringView WS_DISCOVERY_RESOLVE_MATCHES_ACTION{
                "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ResolveMatches"};
        ///@}


        static constexpr NtStringView WS_TRANSFER_GET_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/09/transfer/Get"};
        static constexpr NtStringView WS_TRANSFER_RESPONSE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse"};

        static constexpr NtStringView WS_MEX_GETMETADATA_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/09/mex/GetMetadata/Request"};
        static constexpr NtStringView WS_MEX_GETMETADATA_RESPONSE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/09/mex/GetMetadata/Response"};

        /**
         * @name DPWS
         */
        ///@{
        static constexpr NtStringView DPWS_NAMESPACE{"http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01"};
        static constexpr NtStringView DPWS_DEVICE_DISCOVERY_TYPE{"Device"};
        static constexpr NtStringView DPWS_RELATIONSHIP_TYPE_HOST{
                "http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/host"};
        static constexpr NtStringView DPWS_DIALECT_THISMODEL{
                "http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/ThisModel"};
        static constexpr NtStringView DPWS_DIALECT_THISDEVICE{
                "http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/ThisDevice"};
        static constexpr NtStringView DPWS_DIALECT_RELATIONSHIP{
                "http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/Relationship"};
        static constexpr NtStringView DPWS_WSEVENTING_ACTION_FILTER_DIALECT{
                "http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/Action"};


        static DFL::QName dpwsDeviceQName()
        {
            return {DFL::NamespaceUri{DPWS_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    DPWS_DEVICE_DISCOVERY_TYPE.c_str()};
        }

        ///@}

        static constexpr NtStringView WS_MEX_DIALECT_WSDL{"http://schemas.xmlsoap.org/wsdl/"};

        /**
         * @name WS-Eventing
         */
        ///@{
        static constexpr NtStringView WS_EVENTING_NAMESPACE{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing"};
        static constexpr NtStringView WS_EVENTING_DELIVERYMODE_PUSH{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/DeliveryModes/Push"};
        static constexpr NtStringView WS_EVENTING_SUBSCRIPTIONEND_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/SubscriptionEnd"};
        static constexpr NtStringView WS_EVENTING_SUBSCRIPTIONEND_STATUS_SOURCESHUTTINGDOWN{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/SourceShuttingDown"};
        static constexpr NtStringView WS_EVENTING_SUBSCRIPTIONEND_STATUS_DELIVERYFAILURE{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/DeliveryFailure"};
        static constexpr NtStringView WS_EVENTING_SUBSCRIPTIONEND_STATUS_SOURCECANCELED{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/SourceCancelling"};
        static constexpr NtStringView WS_EVENTING_SUBSCRIBE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/Subscribe"};
        static constexpr NtStringView WS_EVENTING_SUBSCRIBERESPONSE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/SubscribeResponse"};
        static constexpr NtStringView WS_EVENTING_UNSUBSCRIBE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/Unsubscribe"};
        static constexpr NtStringView WS_EVENTING_UNSUBSCRIBERESPONSE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/UnsubscribeResponse"};
        static constexpr NtStringView WS_EVENTING_GETSTATUS_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/GetStatus"};
        static constexpr NtStringView WS_EVENTING_GETSTATUSRESPONSE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/GetStatusResponse"};
        static constexpr NtStringView WS_EVENTING_RENEW_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/Renew"};
        static constexpr NtStringView WS_EVENTING_RENEWRESPONSE_ACTION{
                "http://schemas.xmlsoap.org/ws/2004/08/eventing/RenewResponse"};
        ///@}

        /**
         * @name MDPWS
         */
        ///@{
        static constexpr NtStringView MDPWS_NAMESPACE{"http://standards.ieee.org/downloads/11073/11073-20702-2016"};
        static constexpr NtStringView MDPWS_DEVICE_DISCOVERY_TYPE{"MedicalDevice"};
        ///@}

        /**
         * @name WS-Streaming (MDPWS)
         */
        ///@{
        static constexpr NtStringView WS_STREAMING_APPSEQUENCE_ATTRIBUTE_DEVICEEPRADDRESS{"deviceEprAddress"};
        static constexpr NtStringView WS_STREAMING_APPSEQUENCE_ATTRIBUTE_SERVICEID{"serviceId"};
        static constexpr NtStringView WS_STREAMING_APPSEQUENCE_ATTRIBUTE_STREAMDESCTNS{"streamDescriptionTns"};
        static constexpr NtStringView WS_STREAMING_APPSEQUENCE_ATTRIBUTE_STREAMTYPEID{"streamTypeId"};
        ///@}

        /**
         * @name WS-Streaming (MDPWS)
         */
        ///@{

        /**
         * @brief Filter dialect for WS-Eventing subscribe message.
         * @details
         * Value is defined outside WSDL/schema files in hs:R0002
         */
        static constexpr NtStringView HISTORY_SERVICE_FILTER_DIALECT{"urn:oid:1.3.6.1.4.1.3592.2.6934.1.1.2"};
        static constexpr NtStringView HISTORY_MODEL_NAMESPACE{"urn:oid:1.3.6.1.4.1.3592.2.6933.5.1"};
        static constexpr NtStringView HISTORY_SERVICE_NAMESPACE{"urn:oid:1.3.6.1.4.1.3592.2.6934.1.1"};
        ///@}

        /**
         * @name WS-Addressing
         */
        ///@{
        static constexpr NtStringView WS_ADDRESSING_ANONYMOUS_ADDRESS{"http://www.w3.org/2005/08/addressing/anonymous"};
        static constexpr NtStringView WS_ADDRESSING_NONE_ADDRESS{"http://www.w3.org/2005/08/addressing/none"};
        static constexpr NtStringView WS_ADDRESSING_PREFIX{"wsa5"};
        static constexpr NtStringView WS_ADDRESSING_PROBLEM_HEADER_QNAME_LOCALNAME{"ProblemHeaderQName"};
        static constexpr NtStringView WS_ADDRESSING_UNSPECIFIED_MESSAGE_ID{"http://www.w3.org/2005/08/addressing/unspecified"};

        /**
         * @brief Sub-sub-codes for Invalid Addressing Header Fault.
         * @details
         * The values are defined in <a href="https://www.w3.org/TR/2006/REC-ws-addr-soap-20060509/#invalidmapfault">Web
         * Services Addressing 1.0 - SOAP Binding</a>.
         */
        enum class WS_ADDRESSING_INVALID_ADDRESSING_HEADER_SUBSUBCODES
        {
                InvalidAddress,
                InvalidEPR,
                InvalidCardinality,
                MissingAddressInEPR,
                DuplicateMessageID,
                ActionMismatch,
                OnlyAnonymousAddressSupported,
                OnlyNonAnonymousAddressSupported
        };
        ///@}
};


DFL_ENUM_CLASS_STREAM_OPERATOR(
        StackConstants::WS_ADDRESSING_INVALID_ADDRESSING_HEADER_SUBSUBCODES,
        (InvalidAddress)(InvalidEPR)(InvalidCardinality)(MissingAddressInEPR)(DuplicateMessageID)
        (ActionMismatch)(OnlyAnonymousAddressSupported)(OnlyNonAnonymousAddressSupported))

}
