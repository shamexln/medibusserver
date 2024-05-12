#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>

#include <string>

namespace S31::Sdc::Impl
{

class GsoapEpr;

/**
 * @brief This interface must be implemented for event and waveform messages to send.
 *
 * @ingroup S31SdcDevice
 */
class IOutgoingMessage
{
    public:
        virtual ~IOutgoingMessage() noexcept = default;

        virtual const std::string& soapAction() const = 0;

        /**
         * @brief This function is called from the WS-Eventing plug-in for each subscriber (endpoint).
         * @details
         * The customer implementation must use the @ref gSOAP generated proxy class to send the
         * message to the given endpoint/interface.
         * This function cannot be `const` because it's implementations calls a non-const (gSOAP) interface.
         * @param soapHandle The soap context is already set up
         * @param endpoint To this endpoint the event must be delivered (with help of the gSOAP generated proxy classes for the specific service)
         * @return the gSOAP error code returned for delivering the event to the subscriber
         */
        virtual int sendMessage(struct soap* soapHandle, const GsoapEpr& endpoint) = 0;

        /**
         * @brief Provides a short message description for logging purposes.
         */
        virtual std::string messageDescription() const = 0;
};

}
