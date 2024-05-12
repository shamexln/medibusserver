#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>

#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Utils/Public/NotNull.h>

namespace S31
{
class CoreConfiguration;
namespace Sdc::Impl
{
/**
 * @brief This class is responsible for creating and configuring ssl context.
 *
 * @ingroup S31SdcCommon
 */
class SslContextInitializer
{
    public:
        /**
         * @brief Constructor gets \ref S31::CoreConfiguration from soap pointer and creates a new X509_STORE pointer.
         */
        explicit SslContextInitializer(DFL::NotNull<soap*> soap);

        /**
         * @brief Creates and configures a new SSL context (requires TLSv1.3).
         *
         * @details configures the created context with root CA, certificate chain, private key and CRL.
         * Also sets the cipher list and performance related parameters. Builds the certificate chain and configures ssl context
         * to use ECDH.
         */
        int initializeSslContext();
    private:
        /**
         * @brief Creates a new TLSv1.3 SSL context.
         */
        int createSslContext();
        /**
         * @brief Set the allowed Tls version (Tls 1.3)
         */
        int setAllowedTlsVersion();
        /**
         * @brief Set/replace the newly created X509_STORE for certificate chain building and verification in SSL context.
         */
        int setX509CertStore();
        /**
         * @brief Configure performance relates params.
         */
        int configurePerformanceParams();
        /**
         * @brief Add the list of root CAs to the X509_STORE.
         * Also adds the CA name extracted from the root certificates to the list of CAs sent to the client when requesting a client certificate.
         */
        int configureRootCA();
        /**
         * @brief Checks that the first certificate in the chain is not a CA.
         */
        int firstCertificateIsNotCA();
        /**
         * @brief loads the leaf certificate into SSL context and sets the certificate chain associated with the leaf certificate in the SSL context.
         */
        int configureCertificateChain();
        /**
         * @brief Add the private key of the leaf certificate to the SSL context and verify whether the private key matches with the public key
         * of the leaf certificate.
         */
        int configurePrivateKey();
        /**
         * @brief Append the CA certificates to the chain associated with the leaf certificate.
         */
        int addRootCaToCertChain();
        /**
         * @brief Add all the certificates in the certificate chain (other than leaf certificate) to the X509_STORE and
         * add the CA name extracted from the certificate chain to the list of CAs sent to the client when requesting a client certificate.
         */
        int addCertificatesToCertChain();
        /**
         * @brief Builds the certificate chain for the SSL context.
         */
        int buildCertChain();
        /**
         * @brief Add the revocation list to the X509_STORE and configure the verification parameters.
         */
        int configureCertRevocationList();
        /**
         * @brief Sets the supported groups used for key exchange. Only ECDH groups are used.
         */
        int configureKeyExchange();
        /**
         * @brief Set options related to SSL context and also verification options.
         */
        void addOptionsToSsl();

        DFL::NotNull<soap*> m_soap;
        std::shared_ptr<CoreConfiguration> m_config;
        DFL::Crypto::OpenSsl::X509StorePtr m_certStore;

};

}
}
