#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Nomenclature/Public/CryptoFunctions.h>
#include <S31/Nomenclature/Public/Whitelist.h>
#include <S31/Sdc/Private/Common/SocketLayer/QualityOfService.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/RootCas.h>
#include <Framework/Utils/Public/NotNull.h>

#include <type_traits>
#include <functional>
#include <memory>
#include <optional>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface to customize various policies for Https connections.
 *
 * @details Https connections to different endpoints may require
 * specialized rules or policies.  For example, connection to a
 * discovery proxy server does not require Sdc participant role
 * checks, and low or high priority Sdc services require different
 * quality of service configurations.
 * This interface provides a collection methods to customize
 * the behavior of an Https connection.
 *
 * @ingroup S31SdcCommon
 */
class ConnectionPolicy
{
public:
    /// Dtor
    virtual ~ConnectionPolicy() = default;

    /**
     * @brief Provides root CAs for ssl context initialization.
     */
    [[nodiscard]] virtual DFL::Crypto::RootCas provideRootCas() const = 0;

    /**
     * @brief Provides a private key for ssl context initialization.
     */
    [[nodiscard]] virtual std::optional<DFL::Crypto::PrivateKey> providePrivateKey() const = 0;

    /**
     * @brief Provides a certificate chain for ssl context initialization.
     */
    [[nodiscard]] virtual DFL::Crypto::CertificateChain provideCertificateChain() const = 0;

    /**
     * @brief Checks the given peer against a whitelist during ssl peer authorization check.
     */
    [[nodiscard]] virtual Nomenclature::WhiteListingState whitelistCheck(const std::string& peer) const = 0;

    /**
     * @brief Provides a Role Authorization List(RAL) function during ssl peer authorization check.
     */
    [[nodiscard]] virtual Nomenclature::ProvideRoleAuthorizationListFunction provideRoleAuthorizationListFunction() const = 0;

    /**
     * @brief Perform specific authorization checks on credentials during ssl peer authorization check.
     */
    [[nodiscard]] virtual std::optional<Utils::Error> verifyPeerCredentials(const Nomenclature::Credentials&) const = 0;

    /**
     * @brief Provides the @ref QualityOfService configuration for socket connection.
     */
    [[nodiscard]] virtual QualityOfService qualityOfService() const = 0;

    /**
     * @brief Provide the compression level for gzip, during message send.
     * @details Allowed value are 0 (no compression), 1 (fastest) .. 9 (slowest, more effective),
     * or -1 for default compression (compression library internal choice).
     */
    [[nodiscard]] virtual int compressionLevel() const = 0;

    /**
     * @brief Timeout duration for idle keep-alive connections.
     */
    [[nodiscard]] virtual DFL::Chrono::Seconds idleTimeout() const = 0;

    /**
     * @brief Specify the timeout for connection operations.
     * @details Used for socket connect, ssl handshake, ssl shutdown.
     */
    [[nodiscard]] virtual std::chrono::seconds connectionTimeout() const = 0;

    /**
     * @brief Specify the timeout for making a full request.
     * @details Timeout duration is to write a request and read the response.
     */
    [[nodiscard]] virtual std::chrono::seconds requestTimeout() const = 0;

    /**
     * @brief Specify the maximum payload size which may be received.
     */
    [[nodiscard]] virtual std::size_t maxReceiveSize() const = 0;
};


template<
        class ConnectionPolicyType,
        class... Args,
        typename std::enable_if_t<std::is_convertible_v<ConnectionPolicyType*, ConnectionPolicy*>, bool> = true>
DFL::NotNull<std::shared_ptr<const ConnectionPolicy>> makeConnectionPolicy(Args&&... args)
{
    return DFL::asNotNull(std::make_shared<const ConnectionPolicyType>(std::forward<Args>(args)...));
}

}
