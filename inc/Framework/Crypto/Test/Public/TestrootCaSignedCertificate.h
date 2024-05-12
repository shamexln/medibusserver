#pragma once

#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/PublicKey.h>
#include <Framework/Crypto/Test/Private/CertificateCreationUtilities.h>
#include <Framework/Crypto/Test/Public/ValidityPeriod.h>

#include <string>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief Creates a Testroot CA signed leaf certificate with the given parameters.
 *
 * ValidityPeriod will be set to maximum allowed time starting from one day in the past.
 *
 * @ingroup Crypto
 */
::DFL::Crypto::Certificate createTestrootCaSignedLeafCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey);

/**
 * @brief Creates a Testroot CA signed leaf certificate with the given parameters.
 *
 * @ingroup Crypto
 */
::DFL::Crypto::Certificate createTestrootCaSignedLeafCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod);

/**
 * @brief Creates a Testroot CA signed leaf certificate with the given parameters and list of Oids for extended key usage.
 *
 * @ingroup Crypto
 */
::DFL::Crypto::Certificate createTestrootCaSignedLeafCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod,
        const Oids& extendedKeyUsages);

/**
 * @brief Creates a Testroot CA signed intermediate CA certificate with the given parameters.
 *
 * ValidityPeriod will be set to maximum allowed time starting from one day in the past.
 *
 * @ingroup Crypto
 */
::DFL::Crypto::Certificate createTestrootCaSignedIntermediateCaCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey);

/**
 * @brief Creates a Testroot CA signed intermediate CA certificate with the given parameters.
 *
 * @ingroup Crypto
 */
::DFL::Crypto::Certificate createTestrootCaSignedIntermediateCaCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod);

/**
 * @brief Creates a Testroot CA signed intermediate CA certificate with the given parameters and list of Oids for extended key usage.
 *
 * @ingroup Crypto
 */
::DFL::Crypto::Certificate createTestrootCaSignedIntermediateCaCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod,
        const Oids& extendedKeyUsages);

inline ::DFL::Crypto::Certificate createTestrootCaSignedLeafCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey)
{
    return createTestrootCaSignedLeafCertificate(
            commonName,
            publicKey,
            Impl::getMaximumValidityPeriod());
}

inline ::DFL::Crypto::Certificate createTestrootCaSignedLeafCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod)
{
    return createTestrootCaSignedLeafCertificate(
            commonName,
            publicKey,
            validityPeriod,
            Oids{});
}

inline ::DFL::Crypto::Certificate createTestrootCaSignedLeafCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod,
        const Oids& extendedKeyUsages)
{
    return Impl::createTestrootCaSignedCertificate(
                Impl::distinguishedName(commonName),
                publicKey,
                validityPeriod,
                Impl::certType::leafCertificate,
                extendedKeyUsages);
}

inline ::DFL::Crypto::Certificate createTestrootCaSignedIntermediateCaCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey)
{
    return createTestrootCaSignedIntermediateCaCertificate(
            commonName,
            publicKey,
            Impl::getMaximumValidityPeriod());
}

inline ::DFL::Crypto::Certificate createTestrootCaSignedIntermediateCaCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod)
{
    return createTestrootCaSignedIntermediateCaCertificate(
            commonName,
            publicKey,
            validityPeriod,
            Oids{});
}

inline ::DFL::Crypto::Certificate createTestrootCaSignedIntermediateCaCertificate(
        const std::string& commonName,
        const ::DFL::Crypto::PublicKey& publicKey,
        const ValidityPeriod& validityPeriod,
        const Oids& extendedKeyUsages)
{
    return Impl::createTestrootCaSignedCertificate(
            Impl::distinguishedName(commonName),
            publicKey,
            validityPeriod,
            Impl::certType::intermediateCaCertificate,
            extendedKeyUsages);
}

}
}
}
