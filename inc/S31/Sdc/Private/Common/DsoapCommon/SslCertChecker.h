#pragma once

#include <S31/Error/Public/EventCode.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>
#include <Framework/Crypto/Public/RootCas.h>

#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Check code for the validity of SSL certificates.
 *
 * @details This class is used to check the validity of certificates and to
 * raise errors in case of invalid or soon invalid certificates.
 * The checker will also run some basic checks on the certificate chain
 * to ensure a working of the certificates for communication.
 *
 * @ingroup S31SdcCommon
 */
class SslCertChecker
{
    public:
        /**
         * Timespan in days to warn about a soon expired certificate
         */
        const static DFL::Chrono::Days CERTIFICATE_EXPIRES_WARN_DAYS;

        /**
         * @brief Set the functions that provide the certificate chain and the root CAs.
         * @details In production these never change but this design is needed for testing (instead of just setting
         * this in a ctor).
         * So it can be tested that errors disappear (the needed time related functionality of OpenSSL cannot be mocked).
         * In testing this is simulated by changing the provide functions in an existing SslCertChecker.
         */
        void setProvideFunctions(S31::ProvideCertificateChainFunction provideChain, S31::ProvideRootCasFunction provideRootCas);

        void checkCertificateValidity();

    private:
        void checkAndRaiseError(Error::EventCode errorId, const std::string& subject);
        void checkAndDropError(Error::EventCode errorId, const std::string& subject);
        void checkAndRaiseExpiresSoonError(const ASN1_TIME *asnNow, const ASN1_TIME *notAfter, const std::string& cn);

        S31::ProvideCertificateChainFunction m_provideChain;
        S31::ProvideRootCasFunction m_provideRootCas;
        std::set<Error::EventCode> m_raisedErrors;
        std::mutex m_raisedErrorMutex;
};

}
