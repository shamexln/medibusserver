#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IncomingHttpRequest.h>

namespace S31::Sdc::Impl
{

/**
 * Continues HTTP request for an existing keep-alive connect.
 * @ingroup S31SdcCommonWebServices
 */
class FollowingIncomingHttpRequest: public IncomingHttpRequest
{
    public:
        FollowingIncomingHttpRequest(DFL::NotNull<SoapPtr> soapPtrIn, std::shared_ptr<IWebService> webService,
                std::weak_ptr<SocketStore> sockStoreIn);

        std::string jobName() const override;
};

}
