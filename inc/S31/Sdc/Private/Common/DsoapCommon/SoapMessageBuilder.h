#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/GsoapEpr.h>
#include <S31/Sdc/Private/Common/DsoapCommon/SoapViewTypes.h>

#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{
/**
 * @brief Create a one way SOAP request message.
 * @details
 * Creates an xml string with a complete SOAP envelop based on the given input.  The request is suited only for
 * one way message exchange (i.e. MessageID addressing header is not included).
 * @param endpoint EPR (endpoint reference) to be added to SOAP header (wsa:To as well as additional SOAP header blocks)
 * @param soapAction SOAP action (used for wsa:Action)
 * @param messageBody SOAP body (content of SOAP body element)
 * @return The complete SOAP message.
 */
std::string
createOneWaySoapRequestMessage(const GsoapEpr& endpoint, SoapActionView soapAction, SoapMessageBodyView messageBody);

/**
 * @brief Create a two way SOAP request message.
 * @details
 * Creates an xml string with a complete SOAP envelop based on the given input. The request is suited for
 * two way message exchange (i.e. it includes a MessageID addressing header).  The request wsa:To address
 * is omitted for brevity (i.e. addressed to the anonymous endpoint).
 * @param soapAction SOAP action (used for wsa:Action)
 * @param messageBody SOAP body (content of SOAP body element).
 * @return The complete SOAP message.
 */
std::string createTwoWaySoapRequestMessage(SoapActionView soapAction, SoapMessageBodyView messageBody);

/**
 * @brief Create a one way SOAP request message from gzip compressed data
 * @param endpoint EPR (endpoint reference) to be added to SOAP header (wsa:To as well as additional SOAP header blocks)
 * @param soapAction SOAP action (used for wsa:Action)
 * @param messageBodyInDeflateWithFullSync already compressed SOAP body
 * @return The complete compressed SOAP message.
 */
std::string createGzipCompressedOneWaySoapRequestMessage(
        const GsoapEpr& endpoint, SoapActionView soapAction, std::string_view messageBodyInDeflateWithFullSync);

}
