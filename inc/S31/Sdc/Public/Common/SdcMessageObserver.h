#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <boost/optional/optional.hpp>

#include <string>

namespace S31::Sdc
{
 /**
 * @brief Interface for getting SOAP XML message.
 * @ingroup S31SdcCommon
 */
class SdcMessageObserver
{
    public:
        virtual ~SdcMessageObserver() = default;

        /**
         * @brief Callback for incoming XML SOAP messages.
         * @details
         * The SOAP message without any HTTP header information.
         * The message is completely decoded (no more HTTP chunking and compression).
         */
        virtual void incomingMessage(const std::string& source, const std::string& destination, const std::string& xmlSoapMessage, const boost::optional<S31::Sdc::EndpointReference>& remoteEpr) = 0;
};

}
