#pragma once

#include <S31/Nomenclature/Public/Credentials.h>

#include <Framework/Utils/Public/EnumClass.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Describe the direction of a connection for logging.
 * @ingroup S31SdcCommon
 */
enum class ConnectionDirection
{
    Incoming,
    Outgoing
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ConnectionDirection, (Incoming)(Outgoing))

/**
 * @brief Information about an Http connection.
 * @details Provides access to the @ref S31::Nomenclature::Credentials of the remote
 * peer, and details including local and remote IP addresses and ports.
 * @ingroup S31SdcCommon
 */
class HttpSessionContext
{
public:
    explicit HttpSessionContext(ConnectionDirection direction);

    HttpSessionContext(
            ConnectionDirection            direction,
            std::string                    localIpAddress,
            std::uint16_t                  localPort,
            std::string                    remoteIpAddress,
            std::uint16_t                  remotePort,
            S31::Nomenclature::Credentials remoteCredentials);

    ConnectionDirection                   connectionDirection() const;
    const std::string&                    localIpAddress() const;
    std::uint16_t                         localPort() const;
    const std::string&                    remoteIpAddress() const;
    std::uint16_t                         remotePort() const;
    const S31::Nomenclature::Credentials& remoteCredentials() const;

private:
    ConnectionDirection            m_connectionDirection;
    std::string                    m_localIpAddress;
    std::string                    m_remoteIpAddress;
    std::uint16_t                  m_localPort{0};
    std::uint16_t                  m_remotePort{0};
    S31::Nomenclature::Credentials m_remoteCredentials;
};

inline HttpSessionContext::HttpSessionContext(ConnectionDirection direction)
    : m_connectionDirection(direction)
{
}
inline HttpSessionContext::HttpSessionContext(
        ConnectionDirection            direction,
        std::string                    localIpAddress,
        std::uint16_t                  localPort,
        std::string                    remoteIpAddress,
        std::uint16_t                  remotePort,
        S31::Nomenclature::Credentials remoteCredentials)
    : m_connectionDirection(direction)
    , m_localIpAddress(std::move(localIpAddress))
    , m_remoteIpAddress(std::move(remoteIpAddress))
    , m_localPort(localPort)
    , m_remotePort(remotePort)
    , m_remoteCredentials(std::move(remoteCredentials))
{
}
inline ConnectionDirection HttpSessionContext::connectionDirection() const
{
    return m_connectionDirection;
}
inline const std::string& HttpSessionContext::localIpAddress() const
{
    return m_localIpAddress;
}
inline std::uint16_t HttpSessionContext::localPort() const
{
    return m_localPort;
}
inline const std::string& HttpSessionContext::remoteIpAddress() const
{
    return m_remoteIpAddress;
}
inline std::uint16_t HttpSessionContext::remotePort() const
{
    return m_remotePort;
}
inline const S31::Nomenclature::Credentials& HttpSessionContext::remoteCredentials() const
{
    return m_remoteCredentials;
}
}
