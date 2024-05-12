#pragma once

#include <S31/Sdc/Private/Common/Http/HttpTypes.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Response to be sent by @ref HttpServer
 * @details This class provides response data returned from an @ref S31::Sdc::Impl::HttpServerHandler.
 * The data is to be transmitted back to the requesting http client.
 * @ingroup S31SdcCommon
 */
class HttpServerResponse
{
public:
    explicit HttpServerResponse(
            HttpStatusCode status, ConnectionPersistence persistence = ConnectionPersistence::KeepAlive);

    HttpServerResponse(
            HttpStatusCode        status,
            std::string           body,
            HttpContentType       contentType,
            HttpContentEncoding   contentEncoding,
            ConnectionPersistence persistence = ConnectionPersistence::KeepAlive);

    /// @brief The Http status code of the response.
    unsigned int statusCode() const noexcept;

    /**
     * @brief Returns the response body to send.
     */
    /// @{
    // TODO: Consider making body type = std::variant<std::string, others...>
    //  ~ Maybe this provides options for chunked responses, or file transfer?
    //  ~ Use cases?
    const std::string& body() const& noexcept;
    std::string        body() && noexcept;
    /// @}

    /**
     * @brief Returns the content-type of response body.
     */
    const std::string& contentType() const noexcept;

    /**
     * @brief The value for http content encoding header.
     * @details The application providing the response must provide the content encoding
     * consistent with the response @ref body()
     */
    const std::string& contentEncoding() const noexcept;

    /**
     * @brief Indicate if the connection should be kept alive after sending the response.
     */
    bool keepAlive() const noexcept;

private:
    unsigned int          m_status;
    std::string           m_body;
    std::string           m_contentType;
    std::string           m_contentEncoding;
    ConnectionPersistence m_persistence{ConnectionPersistence::KeepAlive};
};

inline HttpServerResponse::HttpServerResponse(HttpStatusCode status, ConnectionPersistence persistence)
    : m_status(status.get())
    , m_persistence(persistence)
{
}
inline HttpServerResponse::HttpServerResponse(
        HttpStatusCode        status,
        std::string           body,
        HttpContentType       contentType,
        HttpContentEncoding   contentEncoding,
        ConnectionPersistence persistence)
    : m_status(status.get())
    , m_body(std::move(body))
    , m_contentType(std::move(contentType.get()))
    , m_contentEncoding(std::move(contentEncoding.get()))
    , m_persistence(persistence)
{
}
inline unsigned int HttpServerResponse::statusCode() const noexcept
{
    return m_status;
}
inline const std::string& HttpServerResponse::body() const& noexcept
{
    return m_body;
}
inline std::string HttpServerResponse::body() && noexcept
{
    return std::move(m_body);
}
inline const std::string& HttpServerResponse::contentType() const noexcept
{
    return m_contentType;
}
inline const std::string& HttpServerResponse::contentEncoding() const noexcept
{
    return m_contentEncoding;
}
inline bool HttpServerResponse::keepAlive() const noexcept
{
    return m_persistence == ConnectionPersistence::KeepAlive;
}
}
