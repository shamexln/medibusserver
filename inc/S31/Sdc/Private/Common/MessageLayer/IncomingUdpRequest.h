#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IncomingNetworkRequest.h>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Incoming WS-Discovery UDP SOAP message.
 * @ingroup S31SdcCommonWebServices
 */
class IncomingUdpRequest: public IncomingNetworkRequest
{
    public:
        IncomingUdpRequest(DFL::NotNull<SoapPtr> soapPtrIn, std::shared_ptr<IWebService> webService);

        /**
         * Sets the receive timeout to "non-blocking" (1 us timeout) value.
         */
        void preReceiveHook() override;

    private:
        void handleSoapError() override;
};

}
