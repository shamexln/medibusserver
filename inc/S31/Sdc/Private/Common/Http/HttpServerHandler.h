#pragma once

#include <S31/Sdc/Private/Common/Http/HttpPostHandler.h>
#include <S31/Sdc/Private/Common/Http/HttpServerResponse.h>
#include <S31/Sdc/Private/Common/Http/HttpTypes.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string_view>

namespace S31::Sdc::Impl
{
class HttpSessionContext;

/**
 * @brief Https Server Handler interface
 * @details This interface provides for application specific handling of Http requests received by a @ref S31::Sdc::Impl::HttpServer
 * @ingroup S31SdcCommon
 */
class HttpServerHandler: public HttpPostHandler
{
public:

    // TODO: Consider a method to allow application to inspect Http header information before receiving the body.
    //  ~ return a "how to proceed" value (variant)?
    //    - read all at once into string
    //    - method to "stream" data into (repeatedly call with chunks of data)
    //    - filepath destination to directly write?
    //    - abort receiving the request (size too big, etc)
    //  ~ Are there use cases for this?

    // TODO: Http HEAD request?
    //  ~ https://www.rfc-editor.org/rfc/rfc2616 section 5.1.1 Method
    //  ~ The methods GET and HEAD MUST be supported by all general-purpose servers.
    //  ~ Only difference is whether body should be returned or not.
    /**
     * @brief Handle Http Get requests
     * @details This method is called by the http server to respond to Get requests.
     */
    virtual HttpServerResponse handleHttpGet(
            HttpPathView                                            targetPath,
            HttpAcceptEncodingView                                  acceptEncoding,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext) = 0;

    /**
     * @brief Notification of error
     * @details This method is called by the http server to report to the application it has detected an error
     * receiving a request which it will handle internally (e.g. incoming payload is too large).
     */
    virtual void handleError(
            HttpPathView                                            targetPath,
            const Utils::Error&                                     error,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext) = 0;
};

}  // namespace S31::Sdc::Impl
