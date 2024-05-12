#pragma once

#include <S31/Nomenclature/Test/Public/CertHelper.h>

#include <boost/asio/ssl/stream.hpp>

#include <set>

namespace S31::Sdc::Impl::Test
{

/** @brief Configuration of supported ssl/tls Versions for HttpTestClients and HttpTestDevices.
 * @details TlsV1_1AndOlder includes TLS versions 1 and 1.1 as well as SSL versions 2 and 3.
 */
/// @{
enum class SslVersion
{
    TlsV1_3,       //!< TlsV1_3
    TlsV1_2,       //!< TlsV1_2
    TlsV1_1AndOlder//!< TlsV1_1AndOlder
};

using SupportedSslVersions = std::set<SslVersion>;
///@}

enum class Expiration
{
    Valid,  //!< Certificate is NOT expired
    Expired //!< Certificate is expired
};

enum class IssuingCertificateAuthority
{
    DraegerDeviceTestRoot,  //!< Signed by the Draeger test root for device
    SelfSigned,             //!< Self signed certificate for test purposes only.
    UntrustedCa,            //!< Some unknown/untrusted CA.
};

/**
 * @brief Create a (boost asio) ssl context for use in HttpTestDevice and HttpTestClient.
 * @param certCommonName common Name of the certificate
 * @param supportedRoles configuration for the Sdc roles as they appear in the extended key usage of the certificate
 * @param method either @ref boost::asio::ssl::context::tls_server or @ref boost::asio::ssl::context::tls_client
 * @param sslVersions configuration of supported ssl/tls versions, see @ref SupportedSslVersions
 * @param expiration If the certificate shall be expired
 * @param issuer Specifies the issuing CA for the cert
 * @return ssl context in boost asio style to be used in boost beast.
 */
boost::asio::ssl::context createSslContext(
        const std::string& certCommonName,
        S31::Utils::Test::CertHelper::ExtendedKeyUsage supportedRoles,
        boost::asio::ssl::context_base::method method,
        const SupportedSslVersions& sslVersions,
        Expiration expiration = Expiration::Valid,
        IssuingCertificateAuthority issuer = IssuingCertificateAuthority::DraegerDeviceTestRoot);

}
