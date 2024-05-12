#pragma once

#include <S31/Sdc/Private/Common/Http/CreateRequestBody.h>

#include <Framework/Chrono/Public/Duration.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface for sending WS-Discovery messages.
 * @ingroup S31SdcCommonWebServices
 */
class IOutgoingSender
{
    public:
        virtual ~IOutgoingSender() = default;

        /**
         * @brief Send WS-Discovery message.
         * @param soapMessage Serialized SOAP WS-Discovery message.
         */
        virtual void sendMessage(const CreateRequestBody& soapMessage) = 0;

        /**
         * @brief Send WS-Discovery message after given delay.
         * @param soapMessage Serialized SOAP WS-Discovery message.
         * @param delay Time to wait before sending the message.
         */
        virtual void sendMessage(const CreateRequestBody& soapMessage, DFL::Chrono::Milliseconds delay) = 0;

};

}
