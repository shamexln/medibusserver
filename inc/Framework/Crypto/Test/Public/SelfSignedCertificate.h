#pragma once

#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/DistinguishedName.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Test/Private/CertificateCreationUtilities.h>
#include <Framework/Crypto/Test/Public/ValidityPeriod.h>

#include <stdexcept>
#include <string>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief Creates a self signed certificate with the given parameters.
 *
 * validFrom will be set to now, validUntil will be set to the maximum allowed time.
 *
 * @ingroup Crypto
 */
Certificate createSelfSignedCertificate(const std::string& commonName,
                                        const PrivateKey& privateKey);
/**
 * @brief Creates a self signed certificate with the given parameters.
 *
 * @ingroup Crypto
 */
Certificate createSelfSignedCertificate(const std::string& commonName,
                                        const PrivateKey& privateKey,
                                        const ValidityPeriod& validityPeriod);

/**
 * @brief Creates a self signed certificate with the given parameters.
 *
 * Can be used to create a certificate with the provided list of Oids as extended key usage.
 *
 * @ingroup Crypto
 */
Certificate createSelfSignedCertificate(const std::string& commonName,
                                        const PrivateKey& privateKey,
                                        const ValidityPeriod& validityPeriod,
                                        const Oids& extendedKeyUsages);

inline Certificate createSelfSignedCertificate(const std::string& commonName,
                                               const PrivateKey& privateKey)
{
    return createSelfSignedCertificate(commonName, privateKey, Impl::getMaximumValidityPeriod());
}

inline Certificate createSelfSignedCertificate(const std::string& commonName,
                                               const PrivateKey& privateKey,
                                               const ValidityPeriod& validityPeriod)
{
    return createSelfSignedCertificate(commonName, privateKey, validityPeriod, Oids{});
}

inline Certificate createSelfSignedCertificate(const std::string& commonName,
                                               const PrivateKey& privateKey,
                                               const ValidityPeriod& validityPeriod,
                                               const Oids& extendedKeyUsages)
{
    return Impl::createSelfSignedCertificate(
        Impl::distinguishedName(commonName),
        privateKey,
        validityPeriod,
        extendedKeyUsages);
}
}
}
}
