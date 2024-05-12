#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/S31CoreExImp.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{
/**
 * Contains functions to use for in- and outbound web service requests/responses.
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP SoapHeaderUtils
{
    public:

        /**
         * @brief Prepares a Soap Fault reply.
         * @details These functions set up the fault message, and configure the
         * appropriate WS-Addressing header fields including the Action and RelatesTo
         * headers.
         * It also takes care that the original request header is used to derive the
         * new WS-Addressing headers, even if @ref prepareReply() has already been called.
         * @return gSOAP error code (e.g. SOAP_FAULT).
         */
        ///@{
        static int prepareSoapSenderFault(struct soap* soap, const char *faultstring, const char *faultdetail);
        static int prepareSoapSenderFaultSubcode(struct soap* soap, const char *faultsubcode, const char *faultstring, const char *faultdetail);
        static int prepareSoapReceiverFault(struct soap* soap, const char *faultstring, const char *faultdetail);
        ///@}

        /**
         * @brief Prepares the response SOAP header for the reply.
         *
         * @details This function sets the reply WS-Addressing headers (RelatesTo, ...).
         *
         * It also validates the request WS-Addressing headers which are required
         * when formulating a reply message (MessageID).
         *
         * It will discard the message if the ReplyTo address is the "none" address,
         * which for http sends an empty accepted response (202).  Otherwise only the
         * "anonymous" address is supported, and automatic forwarding of reponses is avoided.
         *
         * @param soap \ref gSOAP's soap struct for the request/response
         * @param replyActionUri The WS-Addressing soap action URI for the reply.
         * @return gSOAP error code (SOAP_OK or a specific gSOAP error).
         */
        static int prepareReply(soap* soap, std::string_view replyActionUri);

        /**
         * For outgoing requests this function should be called to set the request WS-Addressing SOAP headers.
         */
        static void prepareRequest(soap* soap, std::string_view to, std::string_view action);

        /**
         * @brief Does not set the message id in SOAP header.
         */
        static void prepareHttpOnewayRequest(soap* soap, std::string_view to, std::string_view action);

        /**
         * Extract the subscription identifier from the SOAP header.
         * @param soap \ref gSOAP's soap struct
         * @return Subscription identifier or empty string if the identifier could not be determined
         */
        static std::string getSubscriptionIdentifier(struct soap* soap);

        /**
         * @brief Validates DPWS service request SOAP header element 'To'
         */
        static bool dpwsServiceEpr(struct soap* soap);

        /**
         * @brief Validates Discovery service request SOAP header element 'To'
         */
        static bool discoveryServiceEpr(struct soap* soap);

        /**
         * @brief Checks the presence and cardinality of WS-Addressing information headers.
         * @return gSOAP error code (SOAP_OK or a specific gSOAP error).
         */
        static int checkSoapWsaHeaders(struct soap* soap);

        /**
         * @brief Repair a soap header if it is missing any required properties for WS-Addressing.
         * @details Intended to be used before sending a soap fault, to ensure required headers
         * are provided.
         */
        static void repairSoapWsaFaultHeader(struct soap* soap);
};

}
