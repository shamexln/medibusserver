#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/Http/CreateRequestBody.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>
#include <S31/Sdc/Private/Common/Http/HttpResultCallback.h>
#include <S31/Sdc/Private/Common/Http/HttpTypes.h>
#include <S31/Sdc/Private/Common/Http/VerifyRequestPreconditions.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Uri.h>

#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace S31::Sdc::Impl
{
class HttpSessionContext;
class HttpResult;

/**
 * @brief Builder with fluent interface for @ref HttpClientRequest
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP HttpClientRequestBuilder
{
public:
    using BodyType = HttpClientRequest::BodyType;

    /**
     * @brief Construct the builder
     * @param method Which @ref HttpMethod shall be used for the request
     * @param httpsUrl The Https endpoint address for the request.
     * @throws S31::InternalConsistencyFailure if the provided url is not Https scheme.
     * Only Https is supported by @ref HttpClient.
     */
    HttpClientRequestBuilder(HttpMethod method, const DFL::Net::Uri& httpsUrl);

    /**
     * @brief Set http accept encoding header.
     * @details Setting this header is optional for a request. Example usage is to
     * set gzip accept-encoding, to indicate to the peer server that a compressed response
     * is acceptable.
     */
    HttpClientRequestBuilder&& acceptEncoding(HttpAcceptEncodingView acceptEncoding) &&;

    /**
     * @brief Set the request body and content-type
     * @details A @ref CreateRequestBody function provides possibly dynamically generated
     * body content for the request.  Only one option for providing a request body may be provided,
     * therefore a body string is mutually exclusive with providing a @ref createBodyFunction().
     * The content-type must also be specified.
     */
    HttpClientRequestBuilder&& bodyString(std::string requestBody, HttpContentType contentType) &&;

    /**
     * @brief Set a create body function and content-type
     * @details A @ref CreateRequestBody function provides possibly dynamically generated
     * body content for the request. Only one option for providing a request body may be provided,
     * therefore a create body function is mutually exclusive with providing a @ref bodyString().
     * The content-type must also be specified.
     * @throws S31::InternalConsistencyFailure if the provided function is empty (i.e. not callable).
     *
     * @note If a request is retried (e.g. due to a closed connection) then the provided function
     * may be called twice (once for each attempt). The retried connection may provide different
     * context information (e.g. local IP address). See @ref allowRetry() to disable retry attempts.
     * If a precondition check of the server fails when attempting a request, then the provided
     * function will not be called since the request is not made. See @ref verifyPreconditionsFunction().
     */
    HttpClientRequestBuilder&& createBodyFunction(CreateRequestBody fn, HttpContentType contentType) &&;

    /**
     * @brief Optionally set a function to provide additional precondition checks.
     * @details Setting this function is optional for a request. Example usage is to
     * provide a function which performs additional EKU role checks on the remote peer
     * credentials before reusing an existing keep-alive connection.
     * @note The provided function applies to only one client request. If the precondition
     * check fails the connection will remain open for keep-alive reuse by subsequent
     * requests.
     */
    HttpClientRequestBuilder&& verifyPreconditionsFunction(VerifyRequestPreconditions fn) &&;

    /**
     * @brief Optionally set http content encoding header.
     * @details Setting this header is optional for a request. Example usage is to
     * set gzip content-encoding when the http body is already compressed by the caller.
     */
    HttpClientRequestBuilder&& contentEncoding(HttpContentEncodingView contentEncoding) &&;

    /**
     * @brief Specify whether the http client may retry a request.
     * @details For example, a remote peer may close a keep-alive connection
     * when the http client attempts to send a request. To recover from this
     * asynchronous close event, the client will by default attempt to re-open
     * the connection and retry the message send.  However, the client may not
     * be able to determine if the request was received by the remote peer or not.
     * If a request must not be retried due to side effects of being received by
     * the peer, then this option must be set to @c false.
     * @note Retry is allowed by default.
     */
    HttpClientRequestBuilder&& allowRetry(bool allowed) &&;

    /**
     * @brief Callback function providing @ref HttpResult upon request completion.
     * @note This may be called more than once to register multiple callback functions.
     */
    HttpClientRequestBuilder&& onComplete(HttpResultCallback callback) &&;

    /**
     * @brief Move construct an @ref HttpClientRequest.
     * @note The data of the source request is moved, so it must not be reused following
     * a call of this method.
     */
    DFL::NotNull<std::unique_ptr<HttpClientRequest>> buildRequest() &&;

private:
    HttpMethod                      m_method;
    VerifyRequestPreconditions      m_verifyPreconditionsFunc;
    std::vector<HttpResultCallback> m_onCompleteCallbacks;
    BodyType                        m_requestBody;
    std::string                     m_serverAddress;
    HttpPath                        m_targetPath;
    HttpAcceptEncoding              m_acceptEncoding;
    HttpContentType                 m_contentType;
    HttpContentEncoding             m_contentEncoding;
    HttpClientRequest::RetryAllowed m_retryAllowed{true};
};

}  // namespace S31::Sdc::Impl
