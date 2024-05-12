#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Utils/S31Only/StringAppendOutputStream.h>

#include <sstream>

namespace S31::Sdc::Impl
{

/**
 * @brief Helper method for SOAP message serialization
 * @ingroup S31SdcCommonWebServices
 */
class Serializer
{
    public:
        /**
         * @brief Serializes a complete SOAP message to a std::string.
         * @details Uses the given \ref gSOAP soap context to serialize an operation with the given soap_put_XYZ() method.
         *
         * @param soapHandle \ref gSOAP context used for serialization. The SOAP header shall be set correctly!
         * @param operationContainer In doc/lit SOAP messages, the body has exactly one child element is.
         *                           This parameter is this child element.
         * @param soapPutFunction \ref gSOAP generates soap_put_XYZ() methods for serialization.
         *                        For the HelloOp of WS-Discovery this is \c soap_put___wsd11__HelloOp for example.
         * @return
         */
        template<class C, class F>
        static std::string serializeSoapMessage(struct soap* soapHandle, const C& operationContainer, const F& soapPutFunction);

        template<class C, class F>
        static std::string serializeSoapBody(struct soap* soapHandle, const C& bodyContainer, const F& soapPutFunction);

};

template<class C, class F>
inline std::string Serializer::serializeSoapMessage(struct soap* soapHandle, const C& operationContainer, const F& soapPutFunction)
{
    // save old stream
    auto* previousOs = soapHandle->os;

    std::string xmlMessage;
    S31::Utils::StringAppendOutputStream xmlStream{xmlMessage};
    soapHandle->os = &xmlStream;

    // Prepare soap handle
    struct soap *soap = soapHandle;
    if (soap_begin_send(soapHandle))
    {
        return "";
    }
    soap->encodingStyle = nullptr;

    // Serialize message to xmlStream
    if (soap_envelope_begin_out(soap)
        || soap_putheader(soap)
        || soap_body_begin_out(soap)
        || soapPutFunction(soap, &operationContainer, "-", "")
        || soap_body_end_out(soap)
        || soap_envelope_end_out(soap)
        || soap_end_send(soap))
    {
        return "";
    }

    soapHandle->os = previousOs;

    return xmlMessage;
}

template<class C, class F>
inline std::string Serializer::serializeSoapBody(struct soap* soapHandle, const C& bodyContainer, const F& soapPutFunction)
{
    // save old data
    auto* previousOs = soapHandle->os;
    auto previousSocket = soapHandle->socket;
    auto previousSendfd = soapHandle->sendfd;

    // serialize XML data to std::string buffer
    std::string xmlMessage;
    S31::Utils::StringAppendOutputStream xmlStream{xmlMessage};
    soapHandle->os = &xmlStream;

    if (soap_begin_send(soapHandle))
    {
        return "";
    }

    // Do not add
    //    <?xml version="1.0" encoding="UTF-8"?>
    // at the beginning of the serialization
    soapHandle->prolog = "";

    soapPutFunction(soapHandle, &bodyContainer, "-", "");

    if (soap_end_send(soapHandle))
    {
        return "";
    }

    // restore old data
    soapHandle->os = previousOs;
    soapHandle->socket = previousSocket;
    soapHandle->sendfd = previousSendfd;

    return xmlMessage;
}

}
