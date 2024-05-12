#pragma once

#include <S31/Sdc/Private/Common/Http/HttpTypes.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>
#include <optional>

namespace S31::Sdc::Impl
{
class HttpSessionContext;

/**
 * @brief Result of an Http Request.
 * @ingroup S31SdcCommon
 */
class HttpResult
{
public:
    /**
     * @brief Constructor with all fields
     */
    HttpResult(
            HttpContentTypeView                                     contentType,
            HttpContentEncodingView                                 contentEncoding,
            std::string                                             body,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext,
            std::optional<Utils::Error>                             error = std::nullopt);

    /**
     * @brief Construct with error
     */
    HttpResult(DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext, Utils::Error error);

    /**
     * @brief Returns true if the http request was successful
     * @details Http status 200, 201, 202, etc.  The @ref error() field is empty.
     */
    explicit operator bool() const noexcept;

    /**
     * @brief Returns the content-type of response body.
     */
    const std::string& contentType() const noexcept;

    /**
     * @brief Returns the content-encoding of response body.
     * @details Content encoding indicates for example whether the response body
     * is compressed, and with which algorithm.
     * @note Response decompression is delegated to the calling application.
     */
    const std::string& contentEncoding() const noexcept;

    /**
     * @brief Returns the response body.
     */
    const std::string& body() const noexcept;

    /**
     * @brief The session context from the request.
     * @details This may be used for example to access peer credentials.
     */
    const HttpSessionContext& sessionContext() const noexcept;

    /**
     * @brief Error detected during the request.
     * @details The error may contain an explanatory message.
     * For @ref S31::Sdc::Impl::Errors::Http errors only status code is provided.
     * The calling application may examine the @ref body() contents to derive a
     * message text (e.g. a soap fault value).
     */
    const std::optional<Utils::Error>& error() const noexcept;

private:
    std::string                                             m_contentType;
    std::string                                             m_contentEncoding;
    std::string                                             m_body;
    DFL::NotNull<std::shared_ptr<const HttpSessionContext>> m_sessionContext;
    std::optional<Utils::Error>                             m_error;
};

inline HttpResult::HttpResult(
        HttpContentTypeView                                     contentType,
        HttpContentEncodingView                                 contentEncoding,
        std::string                                             body,
        DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext,
        std::optional<Utils::Error>                             error)
    : m_contentType{contentType.get()}
    , m_contentEncoding(contentEncoding.get())
    , m_body{std::move(body)}
    , m_sessionContext{std::move(sessionContext)}
    , m_error{std::move(error)}
{
}

inline HttpResult::HttpResult(
        DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext, Utils::Error error)
    : m_sessionContext{std::move(sessionContext)}
    , m_error{std::move(error)}
{
}

inline HttpResult::operator bool() const noexcept
{
    return !m_error.has_value();
}

inline const std::string& HttpResult::contentType() const noexcept
{
    return m_contentType;
}

inline const std::string& HttpResult::contentEncoding() const noexcept
{
    return m_contentEncoding;
}

inline const std::string& HttpResult::body() const noexcept
{
    return m_body;
}

inline const HttpSessionContext& HttpResult::sessionContext() const noexcept
{
    return *m_sessionContext;
}

inline const std::optional<Utils::Error>& HttpResult::error() const noexcept
{
    return m_error;
}

}  // namespace S31::Sdc::Impl
