#pragma once

#include <S31/Sdc/Private/Common/Http/HttpSessionContext.h>

#include <boost/asio/ip/tcp.hpp>

namespace S31::Sdc::Impl
{

/**
 * @brief Builder with fluent interface for @ref HttpSessionContext
 * @ingroup S31SdcCommon
 */
class HttpSessionContextBuilder
{
public:
    using Endpoint = boost::asio::ip::tcp::endpoint;

    explicit HttpSessionContextBuilder(const HttpSessionContext& data);

    HttpSessionContextBuilder&& connectionDirection(ConnectionDirection dir) &&;
    HttpSessionContextBuilder&& localEndpoint(const Endpoint& endpoint) &&;
    HttpSessionContextBuilder&& remoteEndpoint(const Endpoint& endpoint) &&;
    HttpSessionContextBuilder&& remoteCredentials(S31::Nomenclature::Credentials&& credentials) &&;

    DFL::NotNull<std::shared_ptr<const HttpSessionContext>> makeShared() &&;

private:
    ConnectionDirection            m_connectionDirection;
    std::string                    m_localIpAddress;
    std::string                    m_remoteIpAddress;
    std::uint16_t                  m_localPort;
    std::uint16_t                  m_remotePort;
    S31::Nomenclature::Credentials m_credentials;
};

inline HttpSessionContextBuilder::HttpSessionContextBuilder(const HttpSessionContext& data)
    : m_connectionDirection(data.connectionDirection())
    , m_localIpAddress(data.localIpAddress())
    , m_remoteIpAddress(data.remoteIpAddress())
    , m_localPort(data.localPort())
    , m_remotePort(data.remotePort())
    , m_credentials(data.remoteCredentials())
{
}

inline HttpSessionContextBuilder&& HttpSessionContextBuilder::connectionDirection(ConnectionDirection dir) &&
{
    m_connectionDirection = dir;
    return std::move(*this);
}

inline HttpSessionContextBuilder&& HttpSessionContextBuilder::localEndpoint(const Endpoint& endpoint) &&
{
    m_localIpAddress = endpoint.address().to_string();
    m_localPort      = endpoint.port();
    return std::move(*this);
}

inline HttpSessionContextBuilder&& HttpSessionContextBuilder::remoteEndpoint(const Endpoint& endpoint) &&
{
    m_remoteIpAddress = endpoint.address().to_string();
    m_remotePort      = endpoint.port();
    return std::move(*this);
}

inline HttpSessionContextBuilder&&
HttpSessionContextBuilder::remoteCredentials(S31::Nomenclature::Credentials&& credentials) &&
{
    m_credentials = std::move(credentials);
    return std::move(*this);
}

inline DFL::NotNull<std::shared_ptr<const HttpSessionContext>> HttpSessionContextBuilder::makeShared() &&
{
    return DFL::asNotNull(std::make_shared<const HttpSessionContext>(
            m_connectionDirection,
            std::move(m_localIpAddress),
            m_localPort,
            std::move(m_remoteIpAddress),
            m_remotePort,
            std::move(m_credentials)));
}

}  // namespace S31::Sdc::Impl
