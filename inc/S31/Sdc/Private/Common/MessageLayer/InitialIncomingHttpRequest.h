#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IncomingHttpRequest.h>

namespace S31::Sdc::Impl
{

/**
 * Initial HTTP request for a new TCP connect.
 * @ingroup S31SdcCommonWebServices
 */
class InitialIncomingHttpRequest: public IncomingHttpRequest
{
    public:
        InitialIncomingHttpRequest(DFL::NotNull<SoapPtr> soapPtrIn,
                                   std::shared_ptr<IWebService> webService,
                                   std::weak_ptr<SocketStore> sockStoreIn);

        std::string jobName() const override;

        /**
         * Takes care about SSL handshaking.
         */
        void preReceiveHook() override;

    private:
        void optionalTlsAccept();
};

}
