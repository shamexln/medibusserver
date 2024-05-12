#pragma once

#include <S31/Sdc/Private/Common/Http/HttpServerResponse.h>
#include <S31/Sdc/Private/Common/Http/HttpTypes.h>

#include <Framework/Utils/Public/NotNull.h>

namespace S31::Sdc::Impl
{
class HttpSessionContext;

/**
 * @brief Https POST Handler interface.
 * @details This interface provides for application specific handling of POST requests received by a @ref
 * S31::Sdc::Impl::HttpServer.
 * @ingroup S31SdcCommon
 */
class HttpPostHandler
{
public:
    virtual ~HttpPostHandler() = default;

    /**
     * @brief Handle Http Post requests
     * @details This method is called by the http server to respond to Post requests.
     * @note The message body may be compressed (which is indicated by the contentEncoding).
     * Responsibility to decompress the body is delegated to class implementing this interface.
     */
    virtual HttpServerResponse handleHttpPost(
            HttpPathView                                            targetPath,
            HttpAcceptEncodingView                                  acceptEncoding,
            std::string_view                                        body,
            HttpContentTypeView                                     contentType,
            HttpContentEncodingView                                 contentEncoding,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext) = 0;
};

}  // namespace S31::Sdc::Impl
