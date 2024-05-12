#pragma once

#include <Framework/Crypto/Private/Bio.h>
#include <Framework/Crypto/Private/Convert.h>
#include <Framework/Crypto/Private/Store/KnownRootCas.h>
#include <Framework/Crypto/Private/Store/Store.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/DistinguishedName.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/PemString.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/PublicKey.h>
#include <Framework/Crypto/Test/Private/TestRootCaPemStrings.h>
#include <Framework/Crypto/Test/Public/ValidityPeriod.h>

#include <Framework/Chrono/Public/Convert.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/Round.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/SystemTime.h>
#include <Framework/Chrono/Public/TimeOfDay.h>
#include <Framework/Chrono/Public/YearMonthDay.h>
#include <Framework/Chrono/Public/ZonedTime.h>
#include <Framework/Format/Public/Pad.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/Oids.h>

#include <openssl/asn1.h>
#include <openssl/pem.h>
#include <openssl/x509v3.h>

#include <boost/serialization/strong_typedef.hpp>

#include <functional>
#include <stdexcept>
#include <string>
#include <utility>

namespace DFL
{
namespace Crypto
{
namespace Test
{
namespace Impl
{
/**
 * @brief Returns a ASN.1 time format representation of the given zonedTime.
 * @ingroup Crypto
 */
inline std::string toAsn1TimeFormat(Chrono::SystemClock::TimePoint systemTime)
{
    using namespace ::DFL::Chrono;

    const YearMonthDay& ymd = floor<Days>(systemTime);
    const auto& tod = makeTime(systemTime - ymd.systemDays());

    Format::Stream str;
    str << Format::pad(ymd.year().value(), 4, '0')
        << Format::pad(ymd.month().value(), 2, '0')
        << Format::pad(ymd.day().value(), 2, '0')
        << Format::pad(tod.hours().count(), 2, '0')
        << Format::pad(tod.minutes().count(), 2, '0')
        << Format::pad(tod.seconds().count(), 2, '0') << "Z";
    return str.cStr();
}

enum class certType
{
    leafCertificate,
    intermediateCaCertificate
};

BOOST_STRONG_TYPEDEF(long, CertificateSerialNumber)

/**
 * @brief Sets the time span during which the X509 certificate is valid.
 * @ingroup Crypto
 */
inline void setValidityPeriod(::X509& x509Cert,
                              const ValidityPeriod& validityPeriod)
{
    if (!::ASN1_TIME_set_string(
            X509_getm_notBefore(&x509Cert),
            Impl::toAsn1TimeFormat(validityPeriod.validFrom()).c_str()))
    {
        throw std::runtime_error(
            "setValidInterval failed: set valid from failed");
    }

    if (!::ASN1_TIME_set_string(
            X509_getm_notAfter(&x509Cert),
            Impl::toAsn1TimeFormat(validityPeriod.validUntil()).c_str()))
    {
        throw std::runtime_error(
            "setValidInterval failed: set valid until failed");
    }
}

/**
 * @brief Sets the public key in the X509 certificate.
 * @ingroup Crypto
 */
inline void setPublicKey(::X509& x509Cert, const PublicKey& publicKey)
{
    auto* pkey = const_cast<::EVP_PKEY*>(publicKey.publicKey());
    if (!pkey)
    {
        throw std::runtime_error("setPublicKey failed: get public key failed");
    }
    if (::X509_set_pubkey(&x509Cert, pkey) != 1)
    {
        throw std::runtime_error("setPublicKey failed: set public key failed");
    }
}

/**
 * @brief Sets the public key in the X509 certificate to the public key
 * contained in the private key.
 * @ingroup Crypto
 */
inline void setPublicKey(::X509& x509Cert, const PrivateKey& privateKey)
{
    setPublicKey(x509Cert, PublicKey(privateKey));
}

/**
 * @brief Sets the serial number of the X509 certificate.
 * @ingroup Crypto
 */
inline void setSerialNumber(::X509& x509Cert,
                            const CertificateSerialNumber& serialNumber)
{
    if (!::ASN1_INTEGER_set(X509_get_serialNumber(&x509Cert), serialNumber))
    {
        throw std::runtime_error(
            "setSerialNumber failed: set serial number failed");
    }
}

/**
 * @brief Sets the Basic Constraints of the X509 certificate.
 * @ingroup Crypto
 */
inline void setBasicConstraints(::X509& x509Cert, const char* str)
{
    auto ex = OpenSsl::X509v3ExtConfNid(nullptr, NID_basic_constraints, str);
    if (!ex)
    {
        throw std::runtime_error(
            "setBasicConstraints failed: get extensions failed");
    }
    if (!::X509_add_ext(&x509Cert, ex.get(), -1))
    {
        throw std::runtime_error(
            "setBasicConstraints failed: add extensions failed");
    }
}

/**
 * @brief Sets the Basic Constraints of the X509 certificate.
 * @ingroup Crypto
 */
inline void setKeyUsage(::X509& x509Cert, const char* str)
{
    auto ex = OpenSsl::X509v3ExtConfNid(nullptr, NID_key_usage, str);
    if (!ex)
    {
        throw std::runtime_error("setKeyUsage failed: get extensions failed");
    }
    if (!::X509_add_ext(&x509Cert, ex.get(), -1))
    {
        throw std::runtime_error("setKeyUsage failed: add extensions failed");
    }
}

/**
 * @brief Sets the CA capabilities of the X509 certificate.
 * @ingroup Crypto
 */
inline void setCaCapability(::X509& x509Cert)
{
    setBasicConstraints(x509Cert, "critical,CA:TRUE,pathlen:0");
    setKeyUsage(x509Cert,
                "critical,Digital Signature,Certificate Sign,CRL Sign");
}

/**
 * @brief Sets the Basic Constraints and Key Usage of the X509 certificate.
 * @ingroup Crypto
 */
inline void setLeafCertificateCapability(::X509& x509Cert)
{
    setBasicConstraints(x509Cert, "critical,CA:FALSE");
    setKeyUsage(x509Cert, "critical,Digital Signature");
}

/**
 * @brief Sets the TLS capabilities of the X509 certificate.
 * @ingroup Crypto
 */
inline void setTlsCapability(::X509& x509Cert)
{
    X509V3_CTX ctx;
    X509V3_set_ctx_nodb(&ctx);
    X509V3_set_ctx(&ctx, nullptr, &x509Cert, nullptr, nullptr, 0);
    auto ex = OpenSsl::X509v3ExtConfNid(&ctx,
                                        NID_ext_key_usage,
                                        "serverAuth, clientAuth");
    if (!ex)
    {
        throw std::runtime_error(
            "setTslCapability failed: get extensions failed");
    }
    if (!::X509_add_ext(&x509Cert, ex.get(), -1))
    {
        throw std::runtime_error(
            "setCaCapability failed: add extensions failed");
    }
}

/**
 * @brief Sets the issuer name of the X509 certificate.
 *
 * Set the issuer name of the X509 certificate to the name of the provided
 * certificate of the issuing authority
 * @ingroup Crypto
 */
inline void setIssuerName(::X509& x509Cert,
                          const ::X509& x509CertOfIssuingAuthority)
{
    ::X509_NAME* issuerName = OpenSsl::X509GetSubjectName(&x509CertOfIssuingAuthority);

    if (!issuerName)
    {
        throw std::runtime_error("setIssuerName failed: issuer name is null");
    }
    if (::X509_set_issuer_name(&x509Cert, issuerName) != 1)
    {
        throw std::runtime_error(
            "setIssuerName failed: set issuer name failed");
    }
}

/**
 * @brief Sets the subject name of the X509 certificate.
 * @ingroup Crypto
 */
inline void setSubjectName(::X509& x509Cert, const DistinguishedName& dn)
{
    ::X509_NAME* subjectName = OpenSsl::X509GetSubjectName(&x509Cert);
    if (!subjectName)
    {
        throw std::runtime_error("setSubjectName failed: subject name is null");
    }

    ::DFL::Crypto::Impl::Convert::toX509Name(
        ::DFL::Crypto::Impl::Convert::attributes(dn),
        subjectName);

    if (::X509_set_subject_name(&x509Cert, subjectName) != 1)
    {
        throw std::runtime_error(
            "setSubjectName failed: set subject name failed");
    }
}

/**
 * @brief Signs the X509 certificate with the given private key
 * @ingroup Crypto
 */
inline void signCertificate(::X509& x509Cert, const PrivateKey& privateKey)
{
    auto* pkey = const_cast<::EVP_PKEY*>(privateKey.privateKey());
    if (!pkey)
    {
        throw std::runtime_error(
            "signCertificate failed: get private key failed");
    }
    if (!::X509_sign(&x509Cert, pkey, EVP_sha256()))
    {
        throw std::runtime_error("signCertificate failed: signing failed");
    }
}

/**
 * @brief Sets the subject key ID of the X509 certificate.
 * @ingroup Crypto
 */
inline void setSubjectKeyId(::X509& x509Cert)
{
    X509V3_CTX ctx;
    X509V3_set_ctx_nodb(&ctx);
    X509V3_set_ctx(&ctx, nullptr, &x509Cert, nullptr, nullptr, 0);
    auto ex =
        OpenSsl::X509v3ExtConfNid(&ctx, NID_subject_key_identifier, "hash");
    if (!ex)
    {
        throw std::runtime_error(
            "setSubjectKeyId failed: get extensions failed");
    }
    if (!::X509_add_ext(&x509Cert, ex.get(), -1))
    {
        throw std::runtime_error(
            "setSubjectKeyId failed: add extensions failed");
    }
}

/**
 * @brief Sets the authority key ID of the X509 certificate.
 * @ingroup Crypto
 */
inline void setAuthorityKeyId(::X509& x509Cert,
                              const ::X509& x509CertOfIssuingAuthority)
{
    X509V3_CTX ctx;
    X509V3_set_ctx_nodb(&ctx);
    X509V3_set_ctx(&ctx,
                   const_cast<::X509*>(&x509CertOfIssuingAuthority),
                   &x509Cert,
                   nullptr,
                   nullptr,
                   0);
    auto ex = OpenSsl::X509v3ExtConfNid(&ctx,
                                        NID_authority_key_identifier,
                                        "keyid:always");
    if (!ex)
    {
        throw std::runtime_error(
            "setAuthorityKeyId failed: get extensions failed");
    }
    if (!::X509_add_ext(&x509Cert, ex.get(), -1))
    {
        throw std::runtime_error(
            "setAuthorityKeyId failed: add extensions failed");
    }
}

/**
 * @brief Gets the DFL::Crypto representation of the X509 certificate.
 * @ingroup Crypto
 */
inline Certificate createCertificateFromX509(const ::X509& x509Cert)
{
    Crypto::Impl::Bio const bio;
    if (::PEM_write_bio_X509(bio.bio(), const_cast<::X509*>(&x509Cert)) != 1)
    {
        throw std::runtime_error(
            "getCryptoCertificate failed: write bio failed");
    }
    return Certificate(bio.pem());
}

/**
 * @brief Sets the extended key usage field of the X509 certificate.
 * @ingroup Crypto
 */
inline void setExtendedKeyUsage(::X509& x509Cert, const Oids& oids)
{
    X509V3_CTX ctx;
    X509V3_set_ctx_nodb(&ctx);
    X509V3_set_ctx(&ctx, nullptr, &x509Cert, nullptr, nullptr, 0);
    auto ex = OpenSsl::X509v3ExtConfNid(&ctx,
                                        NID_ext_key_usage,
                                        Oids::toCommaSeparated(oids).c_str());
    if (!ex)
    {
        throw std::runtime_error(OpenSsl::getErrorReason());
    }
    if (!::X509_add_ext(&x509Cert, ex.get(), -1))
    {
        throw std::runtime_error(OpenSsl::getErrorReason());
    }
}

/**
 * @brief Gets a default ValidityPeriod.
 * @details The period is calculated from the current system time and maximum
 * certificate lifetime, leaving a day buffer a both ends to prevent time-sync
 * issues and max lifetime violation.
 * @ingroup Crypto
 */
inline ValidityPeriod getMaximumValidityPeriod()
{
    using namespace ::DFL::Chrono;
    return ValidityPeriod()
        .validFrom(SystemClock::now() - Days{1})
        .validFor(Crypto::Impl::Store::maxCertificateLifetime() - Days{1});
}

/**
 * @brief Creates a base X509 certificate as starting point for self signed and
 * testroot CA signed certificate creation
 * @ingroup Crypto
 */
inline OpenSsl::X509Ptr createBaseX509(const DistinguishedName& dn,
                                       const PublicKey& publicKey,
                                       const ValidityPeriod& validityPeriod,
                                       const Oids& extendedKeyUsages)
{
    OpenSsl::X509Ptr cert{OpenSsl::X509New()};
    if (!cert)
    {
        throw std::runtime_error("createBaseX509 failed: cert is null");
    }
    ::X509& certX509 = *cert;
    OpenSsl::X509SetVerionToV3(certX509);
    Impl::setValidityPeriod(certX509, validityPeriod);
    Impl::setSubjectName(certX509, dn);
    if (!extendedKeyUsages.empty())
    {
        Impl::setExtendedKeyUsage(certX509, extendedKeyUsages);
    }
    Impl::setPublicKey(certX509, publicKey);
    return cert;
}

/**
 * @brief Creates a self signed certificate from given arguments
 * @ingroup Crypto
 */
inline Certificate createSelfSignedCertificate(
    const DistinguishedName& dn,
    const PrivateKey& privateKey,
    const ValidityPeriod& validityPeriod,
    const Oids& extendedKeyUsages)
{
    const auto& certX509ptr = createBaseX509(dn,
                                             PublicKey{privateKey},
                                             validityPeriod,
                                             extendedKeyUsages);
    setIssuerName(*certX509ptr, *certX509ptr);
    setSubjectKeyId(*certX509ptr);
    setAuthorityKeyId(*certX509ptr, *certX509ptr);
    signCertificate(*certX509ptr, privateKey);
    return createCertificateFromX509(*certX509ptr);
}

/**
 * @brief Creates a signed certificate from given CA and given arguments.
 * @ingroup Crypto
 */
inline Certificate createCaSignedCertificate(
    const Certificate& issuerCert,
    const PrivateKey& issuerPrivateKey,
    const DistinguishedName& dn,
    const PublicKey& publicKey,
    const ValidityPeriod& validityPeriod,
    const certType& typeOfCertificate,
    const Oids& extendedKeyUsages)
{
    const OpenSsl::X509Ptr issuerCaCert(
        OpenSsl::X509Dup(issuerCert.certificate()));
    const OpenSsl::X509Ptr cert =
        createBaseX509(dn, publicKey, validityPeriod, extendedKeyUsages);
    // A certificate should have a unique issuer + serial number combination,
    // the hash of common name is to make a reasonably unique and stable serial
    // number for testing.
    const std::hash<std::string> stringHash;
    const CertificateSerialNumber& serialNumber = CertificateSerialNumber(
        static_cast<long>(stringHash(dn.commonName().value())));
    if (!issuerCaCert)
    {
        throw std::runtime_error(
            "createCaSignedCertificate failed: issuer CA cert is null");
    }
    const ::X509& issuerCaX509 = *issuerCaCert;
    ::X509& certX509 = *cert;
    setIssuerName(certX509, issuerCaX509);
    if (typeOfCertificate == certType::intermediateCaCertificate)
    {
        setCaCapability(certX509);
    }
    else
    {
        setLeafCertificateCapability(certX509);
    }
    setSubjectKeyId(certX509);
    setAuthorityKeyId(certX509, issuerCaX509);
    setSerialNumber(certX509, serialNumber);
    signCertificate(certX509, issuerPrivateKey);
    return createCertificateFromX509(certX509);
}
/**
 * @brief Creates a testroot CA signed certificate from given arguments
 * @ingroup Crypto
 */
inline Certificate createTestrootCaSignedCertificate(
    const DistinguishedName& dn,
    const PublicKey& publicKey,
    const ValidityPeriod& validityPeriod,
    const certType& typeOfCertificate,
    const Oids& extendedKeyUsages)
{
    const Certificate& cryptoTestrootCaCert =
        ::DFL::Crypto::Impl::KnownRootCas::testRootCa();
    const PrivateKey& privateKey = PrivateKey(TestRootCaPrivateKey);
    return createCaSignedCertificate(cryptoTestrootCaCert,
                                     privateKey,
                                     dn,
                                     publicKey,
                                     validityPeriod,
                                     typeOfCertificate,
                                     extendedKeyUsages);
}

inline DistinguishedName distinguishedName(const std::string& commonName)
{
    return DistinguishedName::createDn()
        .country("DE")
        .organization("Draeger")
        .commonName(commonName);
}
}
}
}
}
