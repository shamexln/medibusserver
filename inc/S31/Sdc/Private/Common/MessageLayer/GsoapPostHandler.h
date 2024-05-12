#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/Http/HttpServerHandler.h>
#include <S31/Sdc/Private/Common/ISoapContextPool.h>
#include <S31/Sdc/Private/Common/IWebService.h>

namespace S31::Sdc::Impl
{

class S31_CORE_EXPIMP GsoapPostHandler
{
public:
    static HttpServerResponse handleHttpPost(
            HttpPathView                                            targetPath,
            HttpAcceptEncodingView                                  acceptEncoding,
            std::string_view                                        body,
            HttpContentTypeView                                     contentType,
            HttpContentEncodingView                                 contentEncoding,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext,
            std::shared_ptr<IWebService>                            webService,
            DFL::NotNull<SoapPtr>                                   soapPtr);

    static HttpServerResponse handleHttpPost(
            HttpPathView                                            targetPath,
            HttpAcceptEncodingView                                  acceptEncoding,
            std::string_view                                        body,
            HttpContentTypeView                                     contentType,
            HttpContentEncodingView                                 contentEncoding,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext,
            std::shared_ptr<IWebService>                            webService,
            ISoapContextPool&                                       soapPool);
};

}  // namespace S31::Sdc::Impl
