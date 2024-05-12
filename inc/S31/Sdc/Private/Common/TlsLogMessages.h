#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>

#include <Framework/Crypto/Public/OpenSslFwd.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace DFL::Crypto
{
class Certificate;
}

namespace S31::Nomenclature
{
class Credentials;
}

namespace S31::Sdc::Impl
{
class HttpSessionContext;

namespace TlsLogMessages
{
struct RetryCountTag;
using RetryCount = DFL::StrongTypedef<int, RetryCountTag, DFL::Skill::Streamable>;

/**
 * @brief Describe how a connection was closed.
 * @ingroup S31SdcCommon
 */
enum class ClosureDescription
{
    Abrupt, ///! Socket closed without TLS shutdown procedure
    Graceful ///! Socket close with successfull TLS shutdown
};

/**
 * @brief Helper functions to write TLS connection log messages to the Security Log
 * @ingroup S31SdcCommon
 */
///@{
void writeTlsConnectionStartingToSecurityLog(const soap& soap, RetryCount retryCount = RetryCount{0});
void writeTlsConnectionClosingToSecurityLog(const soap& soap);

void writeTlsConnectionStartingToSecurityLog(const HttpSessionContext& session,
                                             const SSL* ssl);
void writeTlsConnectionClosingToSecurityLog(const HttpSessionContext& session,
                                            ClosureDescription closureDescription);
///@}

/**
 * @brief Helper functions to write TLS Handshake error messages to the Debug Log
 * @ingroup S31SdcCommon
 */
///@{
void writeTlsHandshakeFailureToDebugLog(soap& soap);
void writeTlsHandshakeFailureToDebugLog(const std::string& remoteIp,
                                        std::uint16_t remotePort,
                                        const std::string& causeInformation,
                                        const DFL::Crypto::Certificate& failedCertificate);
///@}

}
}
