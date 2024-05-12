#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Utils/Public/Errors.h>

#include <boost/asio/ssl/verify_context.hpp>

#include <optional>

namespace S31::Sdc::Impl
{
class ConnectionPolicy;

/**
 * @brief Helper class to implement common ssl verify functionality for Http clients and servers.
 * @details During ssl verification, credentials for the communication peer are recorded if available,
 * along with any specific error detected.
 * @ingroup S31SdcCommon
 */
class SslPeerAuthorization
{
public:
    /**
     * @brief Perform verification work
     * @param connectionPolicy A @ref ConnectionPolicy reference which will provide checks specific to the connection.
     * The following functions from this interface are used:
     *      @ref ConnectionPolicy::whitelistCheck() to optionally verify peer is whitelisted.
     *      @ref ConnectionPolicy::provideRoleAuthorizationListFunction() provides role authorization lists for the
     *      remote credentials.
     *      @ref ConnectionPolicy::verifyPeerCredentials() performs any connection specific verification of the
     *      credentials.
     * @param preverified Indicates whether OpenSSL has already determined a verification error.
     * @param ctx Provides the OpenSSL context for verification.
     */
    SslPeerAuthorization(
            const ConnectionPolicy& connectionPolicy, bool preverified, boost::asio::ssl::verify_context& ctx);

    /**
     * @brief Indication that @ref takeRemoteCredentials() and/or @ref takeVerificationError() are ready.
     * @details Ssl verify is called for each certificate in the chain.  The remote credentials are ready once
     * verify is called on the final leaf certificate, or an error has been detected.
     */
    [[nodiscard]] bool ready() const;

    /**
     * @brief The verification result for ssl verify callback.
     * @note For intermediate certificates, this will pass-through the preverified value.
     */
    [[nodiscard]] bool result() const;

    /**
     * @brief Extract the credentials from the remote peer.
     * @note This function returns by move the captured credentials.
     */
    [[nodiscard]] S31::Nomenclature::Credentials takeRemoteCredentials();

    /**
     * @brief Extract any specific verification error detected during verification.
     * @note This function returns by move the error value.
     */
    [[nodiscard]] std::optional<Utils::Error> takeVerificationError();

private:
    static bool isLeafCertificateCurrent(boost::asio::ssl::verify_context& ctx);
    bool verifyPeerCredentials(const ConnectionPolicy& connectionPolicy, boost::asio::ssl::verify_context& ctx);
    void captureFailedCertificate(boost::asio::ssl::verify_context& ctx);

    S31::Nomenclature::Credentials m_credentials;
    std::optional<Utils::Error>    m_verificationError;
    bool                           m_credentialsReady{false};
    bool                           m_verifyResult{false};
};

}  // namespace S31::Sdc::Impl
