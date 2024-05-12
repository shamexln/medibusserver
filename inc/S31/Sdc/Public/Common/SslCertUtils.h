#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/RootCas.h>

#include <string>

namespace S31::Sdc
{

/**
 * @brief Provides utility functions for SSL certificates.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP SslCertUtils
{
    public:
        /**
         * @brief Indicator to specify which Sdc participant key purpose must be checked to determine the authorization of a certificate.
         */
        enum class KeyPurpose
        {
            ServiceProvider,    ///< Extended Key Usage must contain the SDC Service Provider Oid
            ServiceConsumer,    ///< Extended Key Usage must contain the SDC Service Consumer Oid
            BothProviderAndConsumer    ///< Extended Key Usage must contain both SDC Service Provider and Consumer Oids
        };

        SslCertUtils(DFL::Crypto::CertificateChain certChain,
                     DFL::Crypto::RootCas rootCas);

        /**
         * @brief Returns true if the certificate chain and root CA are valid
         */
        bool isValid(std::string& errorMsg) const;

        /**
         * @brief Returns true if the leaf certificate contains the correct extended key usage field.
         * @param keyPurpose Specifies which Sdc participant key purpose must be checked.
         */
        bool isAuthorized(KeyPurpose keyPurpose) const;

        /**
         * @brief Returns true if the certificate chain is empty.
         */
        bool isEmpty() const;

        /**
         * @brief Provide common name of the leaf certificate.
         */
        std::string commonName() const;

    private:
        DFL::Crypto::CertificateChain m_certChain;
        DFL::Crypto::RootCas m_rootCas;
};

}
