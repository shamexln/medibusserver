#pragma once

#include <Framework/Crypto/Test/Private/CertificateCreationUtilities.h>
#include <Framework/Crypto/Test/Public/ValidityPeriod.h>

namespace DFL
{
namespace Crypto
{
namespace Test
{

/**
 * @brief Signs a public key with a given CA cert and private key.
 *
 * @details
 * Use this function to sign a public key (subject) with a specific
 * CA certificate (issuer) and the corresponding key.
 * For self-signed certificates use \ref DFL::Crypto::Test::createSelfSignedCertificate()
 * while for Draeger device test root signed certificates use
 * \ref DFL::Crypto::Test::createTestrootCaSignedLeafCertificate().
 *
 * @param issuerCert The issuer public key
 * @param issuerPrivateKey The issuer private key (required for signing)
 * @param dn Subject distinguished name
 * @param publicKey The subjects public key
 * @param validityPeriod Expiration begin and end
 * @param extendedKeyUsages X.509v3 extended key usages roles
 * @return Newly created leaf certificate.
 * @ingroup Crypto
 */
inline Certificate createCaSignedCertificate(const Certificate& issuerCert,
                                             const PrivateKey& issuerPrivateKey,
                                             const DistinguishedName& dn,
                                             const PublicKey& publicKey,
                                             const ValidityPeriod& validityPeriod,
                                             const Oids& extendedKeyUsages)
{
    return Impl::createCaSignedCertificate(issuerCert, issuerPrivateKey,
            dn, publicKey, validityPeriod, Impl::certType::leafCertificate, extendedKeyUsages);
}

/**
 * @brief Signs a public key with a given CA cert and private key.
 *
 * @details
 * Use this function to sign a public key (subject) with a specific
 * CA certificate (issuer) and the corresponding key.
 * For self-signed certificates use \ref DFL::Crypto::Test::createSelfSignedCertificate()
 * while for Draeger device test root signed certificates use
 * \ref DFL::Crypto::Test::createTestrootCaSignedLeafCertificate().
 *
 * @param issuerCert The issuer public key
 * @param issuerPrivateKey The issuer private key (required for signing)
 * @param dn Subject distinguished name
 * @param publicKey The subjects public key
 * @param validityPeriod Expiration begin and end
 * @param extendedKeyUsages X.509v3 extended key usages roles
 * @return Newly created intermediate certificate.
 * @ingroup Crypto
 */
inline Certificate createCaSignedIntermediate(const Certificate& issuerCert,
                                              const PrivateKey& issuerPrivateKey,
                                              const DistinguishedName& dn,
                                              const PublicKey& publicKey,
                                              const ValidityPeriod& validityPeriod,
                                              const Oids& extendedKeyUsages)
{
    return Impl::createCaSignedCertificate(issuerCert, issuerPrivateKey,
            dn, publicKey, validityPeriod, Impl::certType::intermediateCaCertificate, extendedKeyUsages);
}


}
}
}
