#include <S31/Nomenclature/Public/SdcCertificateId.h>
#include <S31/Utils/Public/CryptoStoreCache.h>
#include <S31/Test/S31Only/Exception.h>

#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/Csr.h>
#include <Framework/Crypto/Public/PemString.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/Registry.h>
#include <Framework/Crypto/Public/Store.h>
#include <Framework/Crypto/Public/Table.h>
#include <Framework/Crypto/Test/Public/CertificatePrivateKey.h>

#include <gtest/gtest.h>

#include <openssl/asn1.h>
#include <openssl/bio.h>
#include <openssl/obj_mac.h>
#include <openssl/ossl_typ.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/x509v3.h>

namespace S31::Sdc::Impl::Test
{
static constexpr int DAYS_TILL_EXPIRE = 365;
static constexpr int EXPIRE_SECS = (60 * 60 * 24 * DAYS_TILL_EXPIRE);
static constexpr char rootCaCertString[] =
        "-----BEGIN CERTIFICATE-----\n"
        "MIICzDCCAjWgAwIBAgIJAN6oev222WqCMA0GCSqGSIb3DQEBDQUAMH8xCzAJBgNV\n"
        "BAYTAkRFMRMwEQYDVQQIDApTb21lLVN0YXRlMRAwDgYDVQQHDAdMdWViZWNrMRAw\n"
        "DgYDVQQKDAdEcmFlZ2VyMRwwGgYDVQQLDBNDb0MgU3lzdGVtIFNvZnR3YXJlMRkw\n"
        "FwYDVQQDDBBPRERTIFRlc3QgUm9vdENBMB4XDTE2MDUxMDE0MjE0MloXDTI2MDUw\n"
        "ODE0MjE0MlowfzELMAkGA1UEBhMCREUxEzARBgNVBAgMClNvbWUtU3RhdGUxEDAO\n"
        "BgNVBAcMB0x1ZWJlY2sxEDAOBgNVBAoMB0RyYWVnZXIxHDAaBgNVBAsME0NvQyBT\n"
        "eXN0ZW0gU29mdHdhcmUxGTAXBgNVBAMMEE9ERFMgVGVzdCBSb290Q0EwgZ8wDQYJ\n"
        "KoZIhvcNAQEBBQADgY0AMIGJAoGBANi5cDQsKucPHoQ1hISl1HPGkknyeareA5Yi\n"
        "WvTSrWnZRGC4cWjASEMhmgV7l7HfQ2/z7Cx8Pit6n+DdmeNEQiqoi2+t4oNJvfUR\n"
        "yAjFVImDog6E7YsJlPkx2+fOBaFQc1q0IZi2ZwBA6A1AHr5M6H3aNvIof6lEgeaA\n"
        "rnHJgNATAgMBAAGjUDBOMB0GA1UdDgQWBBQ2StgIerHVSBQf9lncywsEKokwRzAf\n"
        "BgNVHSMEGDAWgBQ2StgIerHVSBQf9lncywsEKokwRzAMBgNVHRMEBTADAQH/MA0G\n"
        "CSqGSIb3DQEBDQUAA4GBADFm48KIF5s7GAufFfFk/3FfMj+AD0wh6R6EoZLIAEU2\n"
        "cZTsycUnTJVto+oK2baZNLsL/zqS+7teVdz6/wp1fBR0NKlXQgHRA4SdyR1y12yg\n"
        "g3eHsz0JSBT+YCxkaEkGtVGkR23TQpcsXPNmo6u6wdTJ+SphVNfR4QrTwnwPm+Ga\n"
        "-----END CERTIFICATE-----\n";
static constexpr char rootCaCertKey[] =
        "-----BEGIN PRIVATE KEY-----\n"
        "MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBANi5cDQsKucPHoQ1\n"
        "hISl1HPGkknyeareA5YiWvTSrWnZRGC4cWjASEMhmgV7l7HfQ2/z7Cx8Pit6n+Dd\n"
        "meNEQiqoi2+t4oNJvfURyAjFVImDog6E7YsJlPkx2+fOBaFQc1q0IZi2ZwBA6A1A\n"
        "Hr5M6H3aNvIof6lEgeaArnHJgNATAgMBAAECgYAzLk/eMlQLbxmg1VavUM5EbS+d\n"
        "AQNUo8urB//880f6yFGKmeRGfapTGDtcchyX6AbwCGXM96Zi9DmPjCXMcxFAvDG9\n"
        "fenB35xQVNJf2NQ98J+hGIZ1I1m6KOEAOu8JVpr4r5DxMguJ0Bcrzbem2UBy3nXo\n"
        "vA8v92hQuTvH8jNw8QJBAP11Ir4FhhxbbIX/cElglmX3WxWF5N7xWh1K5ThQlpRL\n"
        "ivx2KCoJICQ4p0S4cYIPSLEtKL2kTXWr9t5arOl7w6sCQQDa5flQJHK+B60qMs8M\n"
        "au442aoexseymw+6lSB9zS/TOYFOR1bk2N/NzY3Doir34kDfYuNeyJFoDBrHlcNr\n"
        "d705AkAI7QsgLgmfDgkwXuKRcvlY9fEbPO/mehF2XqDb7tqetlpasb6QXGnpXKVn\n"
        "Yid9MRSaSMDajOK9diTnh8H3JwipAkEApRmLn0y+VmHH0+oajA0ivDI/w5K+EBIw\n"
        "HNRZe0kFZ1UaGAZqnZSNyNXetM1dhzVZJKObRmQUd9uZXyuwByB60QJBAK7pNXzp\n"
        "dxWWLK4m50JtKLdJitEtMNVVSUkuN4Hr55jpLcl2OkvSq2IHwP7E0cLwlh/j/Zna\n"
        "DtRngyN+VjANRwg=\n"
        "-----END PRIVATE KEY-----";

void downloadCertificate(const DFL::Crypto::Csr& csr);
void signCsr(const std::string& csrStr);

void downloadCertChain()
{
    DFL::Crypto::Table table = DFL::Crypto::Store::table();
    DFL::Crypto::Table::OptionalValueType optionalTable = table[S31::Nomenclature::sdcCertificateId()];
    ASSERT_TRUE(optionalTable);

    std::string errorMessage;
    DFL::Crypto::Store::OptionalCsr optionalCsr = DFL::Crypto::Store::generateCsrFor(S31::Nomenclature::sdcCertificateId(), errorMessage);
    ASSERT_TRUE(optionalCsr);
    downloadCertificate(*optionalCsr);
    S31::Utils::CryptoStoreCache::instance().forceSynchronousUpdate();
}

void downloadCertificate(const DFL::Crypto::Csr& csr)
{
    // convert to pemString
    std::string csrString(DFL::Crypto::Convert::toPem(csr).str());
    signCsr(csrString);
}

int addExtension(X509* cert, int nid, const char* value)
{
    X509V3_CTX ctx;

    // This sets the 'context' of the extensions.
    // No configuration database
    X509V3_set_ctx_nodb(&ctx);

    // Issuer and subject certs: both the target since it is self-signed, no
    // request and no CRL
    X509V3_set_ctx(&ctx, cert, cert, nullptr, nullptr, 0);

    auto extension(std::shared_ptr<X509_EXTENSION>(X509V3_EXT_conf_nid(nullptr, &ctx, nid, const_cast<char*>(value)), X509_EXTENSION_free));
    THROW_IF_NOT(extension);

    X509_add_ext(cert, extension.get(), -1);
    return 1;
}

DFL::Crypto::OpenSsl::EvpPkeyPtr parsePrivateKey(const std::string& keyIn)
{
    auto bio(DFL::Crypto::OpenSsl::BioNewMemBuf(const_cast<char*>(keyIn.c_str()), static_cast<int>(keyIn.length())));
    auto key(DFL::Crypto::OpenSsl::PemReadBioPrivateKey(bio.get(), nullptr, nullptr, nullptr));
    EXPECT_TRUE(key) << "cannot parse private key";

    return key;
}

std::string getStringFromBio(BIO* bio)
{
    BUF_MEM* mem = nullptr;
    BIO_get_mem_ptr(bio, &mem);
    EXPECT_TRUE(mem && mem->data && mem->length) << "cannot create string from BIO";

    return {mem->data, mem->length};
}

std::string getCertString(X509* cert)
{
    auto bio(DFL::Crypto::OpenSsl::BioNew());
    EXPECT_TRUE(PEM_write_bio_X509(bio.get(), cert)) << "cannot create certificate string";

    return getStringFromBio(bio.get());
}

void signCsr(const std::string& csrStr)
{
    std::shared_ptr<BIO> bio(DFL::Crypto::OpenSsl::BioNewMemBuf(csrStr.c_str(), static_cast<int>(csrStr.length())));
    auto req = DFL::Crypto::OpenSsl::PemReadBioX509Req(bio.get(), nullptr, nullptr, nullptr);
    ASSERT_TRUE(req) << "cannot parse csr";
    auto caKey(parsePrivateKey(rootCaCertKey));

    ASSERT_TRUE(caKey);
    ASSERT_TRUE(X509_REQ_sign(req.get(), caKey.get(), EVP_sha256())) << "cannot sign request";

    auto bioC = std::shared_ptr<BIO>(BIO_new_mem_buf(rootCaCertString, sizeof(rootCaCertString)), BIO_free_all);

    std::shared_ptr<X509> racert(DFL::Crypto::OpenSsl::PemReadBioX509(bioC.get(), nullptr, nullptr, nullptr));
    ASSERT_TRUE(racert) << "cannot parse certificate";

    DFL::Crypto::OpenSsl::EvpPkeyPtr pKey(DFL::Crypto::OpenSsl::X509ReqGetPubkey(req.get()));
    ASSERT_TRUE(pKey) << "error getting public key from request";

    DFL::Crypto::OpenSsl::X509Ptr signedCert(DFL::Crypto::OpenSsl::X509New());
    ASSERT_TRUE(signedCert) << "error creating X509 object";

    DFL::Crypto::OpenSsl::X509SetVerionToV3(*signedCert);

    X509_NAME* nameInter = DFL::Crypto::OpenSsl::X509GetSubjectName(signedCert.get());
    X509_NAME_add_entry_by_txt(nameInter, "C", MBSTRING_ASC, reinterpret_cast<const unsigned char*>("DE"), -1, -1, 0);
    X509_NAME_add_entry_by_txt(nameInter, "O", MBSTRING_ASC, reinterpret_cast<const unsigned char*>("Draegerwerk"), -1, -1, 0);
    X509_NAME_add_entry_by_txt(nameInter, "CN", MBSTRING_ASC, reinterpret_cast<const unsigned char*>("Intermediate CA"), -1, -1, 0);

    static long serial = 1;

    ASN1_INTEGER_set(X509_get_serialNumber(signedCert.get()), serial++);

    // set issuer and subject name of the cert from the req and the CA
    X509_NAME* issuer = DFL::Crypto::OpenSsl::X509GetSubjectName(racert.get());
    ASSERT_TRUE(issuer) << "error getting subject name from CA certificate";

    ASSERT_TRUE(X509_set_issuer_name(signedCert.get(), issuer)) << "error setting issuer name of certificate";

    // set public key in the certificate

    auto interKey = DFL::Crypto::Test::generateCertificatePrivateKey();
    ASSERT_TRUE(X509_set_pubkey(signedCert.get(), const_cast<::EVP_PKEY*>(interKey.privateKey())))
            << "error setting public key of the certificate";

    // set duration for the certificate
    ASSERT_TRUE(X509_gmtime_adj(X509_getm_notBefore(signedCert.get()), 0)) << "error setting beginning time of the certificate";

    ASSERT_TRUE(X509_gmtime_adj(X509_getm_notAfter(signedCert.get()), EXPIRE_SECS)) << "error setting ending time of the certificate";

    DFL::Crypto::OpenSsl::X509Ptr lastCert(DFL::Crypto::OpenSsl::X509New());
    X509V3_CTX ctx;

    X509V3_set_ctx(&ctx, racert.get(), signedCert.get(), nullptr, nullptr, 0);

    addExtension(signedCert.get(), NID_basic_constraints, "critical,CA:TRUE");

    ASSERT_TRUE(X509_sign(signedCert.get(), caKey.get(), EVP_sha256())) << "error signing certificate";

    X509_NAME* name = DFL::Crypto::OpenSsl::X509ReqGetSubjectName(req.get());
    ASSERT_TRUE(name) << "error getting subject name from request";

    ASSERT_TRUE(X509_set_subject_name(lastCert.get(), name)) << "error setting subject name of certificate";
    ASSERT_TRUE(X509_set_pubkey(lastCert.get(), pKey.get())) << "error setting public key of the certificate1..";
    ASSERT_TRUE(X509_set_issuer_name(lastCert.get(), nameInter)) << "error setting issuer name of certificate";
    ASSERT_TRUE(X509_gmtime_adj(X509_getm_notBefore(lastCert.get()), 0)) << "error setting beginning time of the certificate";
    ASSERT_TRUE(X509_gmtime_adj(X509_getm_notAfter(lastCert.get()), EXPIRE_SECS)) << "error setting ending time of the certificate";

    X509V3_CTX ctx2;
    X509V3_set_ctx(&ctx2, signedCert.get(), lastCert.get(), nullptr, nullptr, 0);

    addExtension(lastCert.get(), NID_basic_constraints, "critical,CA:FALSE");
    addExtension(lastCert.get(), NID_ext_key_usage, "serverAuth, clientAuth, 1.2.840.10004.20701.1.1, 1.2.840.10004.20701.1.2");
    ASSERT_TRUE(X509_sign(lastCert.get(), const_cast<::EVP_PKEY*>(interKey.privateKey()), EVP_sha256()))
            << "error signing certificate";

    std::string certChainStr;
    certChainStr.append(getCertString(lastCert.get()));
    certChainStr.append(getCertString(signedCert.get()));
    DFL::Crypto::PemString pem(certChainStr);
    DFL::Crypto::CertificateChain certificateChain(pem);
    ASSERT_FALSE(certificateChain.empty()) << "certificate chain is empty";

    ASSERT_TRUE(DFL::Crypto::Store::certificateChain(certificateChain)) << "certificate signing was unsuccessful";
}

}
