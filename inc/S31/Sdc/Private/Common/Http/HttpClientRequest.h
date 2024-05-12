#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/EncodingType.h>
#include <S31/Sdc/Private/Common/Http/CreateRequestBody.h>
#include <S31/Sdc/Private/Common/Http/HttpResultCallback.h>
#include <S31/Sdc/Private/Common/Http/HttpTypes.h>
#include <S31/Sdc/Private/Common/Http/VerifyRequestPreconditions.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Utils/Public/StrongTypedef.h>

#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace S31::Sdc::Impl
{
struct HttpClientRequestRetryAllowedTag {};

class HttpSessionContext;
class HttpResult;

/**
 * @brief Provide parameters to an http client request operation.
 * @details This class provides the parameters for composing an http request, including a callback function to execute
 * upon completion. Parameters include the http method, target endpoint address, and optional message body and header
 * fields appropriate for the method. It also provides some customization of behavior on a per-request basis, such has
 * additional credentials checks.
 * @note This class is not intended for direct use by application code, but to be constructed using the
 * @ref HttpClientRequestBuilder class, and provided to a @ref HttpClient.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP HttpClientRequest
{
public:
    /// Body type definiton allows a string value or a function to dynamically create the body.
    using BodyType = std::variant<std::string, CreateRequestBody>;

    /// Strong type indicator if the request is allowed automatic retry in case of connection loss.
    using RetryAllowed = DFL::StrongTypedef<bool, HttpClientRequestRetryAllowedTag>;

    /**
     * @brief Construct a request.
     *
     * @param method The @ref HttpMethod for the request.
     * @param serverAddress The authority component from a URI (minus user info) which the request will be sent to.  It
     * is formatted as \c host:port
     * @param targetPath The path and query components from a URI which is transmitted as the target path of the
     * request.  It must be an absolute path starting with \c '/'
     * @param acceptEncoding The @ref HttpAcceptEncoding header is optional and will be ignored if an empty string is
     * provided.
     * @param requestBody The body for the request is optional and will be ignored if an empty string is provided.
     * @param contentType The @ref HttpContentType must be provided if a body value is provided, but will be ignored if
     * the message body is empty.
     * @param contentEncoding The @ref HttpContentEncoding must be provided if the body value has additional encoding
     * (e.g. compression) but will be ignored if the message body is empty.
     * @param retryAllowed Indicate whether or not automatic retry of the request is allowed in case of connection loss.
     * @param verifyPreconditionsFunc Is an optional function (i.e. may be empty) additional per-request verification of
     * the @ref HttpSessionContext (e.g. additional credentials verification) which is called before the request is
     * sent.
     * @param onCompleteCallbacks Functions which are called when the response to a request is received, or a final error
     * is detected. It provides the @ref HttpResult to the consumer of http requested data.
     *
     * @note It is recommended to use a @ref HttpClientRequestBuilder to configure the request, rather than calling
     * this constructor directly.
     */
    HttpClientRequest(
            HttpMethod                      method,
            std::string                     serverAddress,
            HttpPath                        targetPath,
            HttpAcceptEncoding              acceptEncoding,
            BodyType                        requestBody,
            HttpContentType                 contentType,
            HttpContentEncoding             contentEncoding,
            RetryAllowed                    retryAllowed,
            VerifyRequestPreconditions      verifyPreconditionsFunc,
            std::vector<HttpResultCallback> onCompleteCallbacks);

    /**
     * @name Getter methods
     * @details Access to fields of the request.
     */
    /// @{
    HttpMethod         method() const;
    const std::string& serverAddress() const;
    const std::string& targetPath() const;
    const std::string& acceptEncoding() const;
    const std::string& contentType() const;
    const std::string& contentEncoding() const;
    bool               retryAllowed() const;
    const BodyType&    body() const;
    /// @}

    /**
     * @brief Modifies the request by adding completion callbacks.
     * @details This method allows additional components to register interest in receiving notification
     * about the request completion.
     */
    void registerCompletionCallback(HttpResultCallback callback);

    /**
     * @brief Modifies the request to disable retry allowed.
     * @details This method is intended for use by a @ref HttpClient to indicate that that a request is being retried, and
     * shall not be automatically retried a second time.
     */
    void disableRetry();

    /**
     * @brief Runs the @ref VerifyRequestPreconditions callback function.
     * @details This method is intended for use by a @ref HttpClient before a request is transmitted.
     */
    std::optional<Utils::Error> verifyPreconditions(const HttpSessionContext& session) const;

    /**
     * @brief Runs all the @ref HttpResultCallback functions.
     * @details This method is intended for use by a @ref HttpClient indicating the request has completed.
     */
    void notifyCompletion(const HttpResult& result) const;

private:
    HttpMethod                      m_method;
    VerifyRequestPreconditions      m_verifyPreconditionsFunc;
    std::vector<HttpResultCallback> m_onCompleteCallbacks;
    BodyType                        m_requestBody;
    std::string                     m_serverAddress;
    std::string                     m_targetPath;
    std::string                     m_acceptEncoding;
    std::string                     m_contentType;
    std::string                     m_contentEncoding;
    bool                            m_retryAllowed;
};

}  // namespace S31::Sdc::Impl
