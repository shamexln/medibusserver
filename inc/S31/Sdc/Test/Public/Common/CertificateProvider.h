#pragma once

#include <S31/Sdc/Test/Public/Common/CertificateProviderImpl.h>

#include <Framework/Crypto/Public/OpenSslFwd.h>
#include <Framework/Crypto/Public/Csr.h>
#include <Framework/Utils/Public/Key.h>

namespace S31::Sdc::Test
{
/**
 * \brief Certificate provider that provides several certificate utility functions.
 * @ingroup S31SdcCommon
 */
class CertificateProvider
{
    public:
        void downloadCertificate(const DFL::Crypto::Csr& csr) const
        {
            Impl::Test::downloadCertificate(csr);
        }

        void downloadCertChain() const
        {
            Impl::Test::downloadCertChain();
        }

    private:
        void signCsr(const std::string& csrStr) const
        {
            Impl::Test::signCsr(csrStr);
        }

        std::string getCertString(X509* cert) const
        {
            return Impl::Test::getCertString(cert);
        }

        std::string getStringFromBio(BIO* bio) const
        {
            return Impl::Test::getStringFromBio(bio);
        }

        DFL::Crypto::OpenSsl::EvpPkeyPtr parsePrivateKey(const std::string& keyIn) const
        {
            return Impl::Test::parsePrivateKey(keyIn);
        }

        int addExtension(X509* cert, int nid, const char* value) const
        {
            return Impl::Test::addExtension(cert, nid, value);
        }
};

}