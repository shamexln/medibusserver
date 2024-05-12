#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IncomingHttpRequest.h>

namespace S31::Sdc::Impl
{

/**
 * Closes an idle keep-alive incoming HTTP connection.
 * @ingroup S31SdcCommonWebServices
 */
class ClosingIncomingHttpRequest: public IncomingHttpRequest
{
    public:
        ClosingIncomingHttpRequest(DFL::NotNull<SoapPtr> soapPtrIn, std::shared_ptr<IWebService> webService,
                std::weak_ptr<SocketStore> sockStoreIn);

        /**
         * @brief No HTTP request handling, but socket close.
         */
        void execute() override;

        [[nodiscard]] std::string jobName() const override;
};

}
