#pragma once

#include <S31/Base/S31Only/Exception.h>
#include <S31/Nomenclature/Public/CryptoFunctions.h>
#include <S31/Nomenclature/Public/Roles.h>
#include <S31/Nomenclature/Public/SdcCryptoStoreHelper.h>
#include <S31/Nomenclature/Public/Whitelist.h>
#include <S31/Nomenclature/Test/Private/CertHelperPemStrings.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/ZonedTime.h>
#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/Whitelist.h>
#include <Framework/Crypto/Test/Public/CertificatePrivateKey.h>
#include <Framework/Crypto/Test/Public/KnownRootCas.h>
#include <Framework/Crypto/Test/Public/TestrootCaSignedCertificate.h>

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @file
 * @brief Provides various helper functions for creating test @ref DFL::Crypto::Certificate "Certificates".
 *
 * @details
 * These functions provide utilities to use with @ref Framework/Crypto/Test/Public/TestrootCaSignedCertificate.h
 * for creating test certificates, and converting them to the data types used by @ref S31::CoreConfiguration
 *
 * @ingroup S31Nomenclature
 */
namespace S31::Utils::Test::CertHelper
{
namespace Impl
{
/// @brief Helper for maintaining a cache that adds new items when the value is not found.
/// @ingroup S31Nomenclature
template<class Map, class Fn>
const typename Map::mapped_type& findOrCreateCachedValue(Map& cache, const typename Map::key_type& key, Fn makeOne)
{
    auto i = cache.find(key);
    if (i == cache.end())
    {
        auto result = cache.insert(std::make_pair(key, makeOne()));
        if (!result.second)
        {
            S31_THROW_EXCEPTION(InternalConsistencyFailure, "Failed to insert to CertHelper cache");
        }
        i = result.first;
    }
    return i->second;
}
}

/// @brief Choices for which collection of @ref DFL::Oids to get from @ref keyUsageRoles()
/// @ingroup S31Nomenclature
enum class ExtendedKeyUsage
{
    WithTlsServerClientAuthenticationRoles,///< Only provide web server and web client roles
    WithoutOperationConsumerRole,          ///< Provide web server and client, and sdc provider and consumer roles
    WithAllRoles,                          ///< Web server and client, sdc service provider and consumer, and sdc operation consumer
    WithAllButClientAuth,                  ///< Same as @ref ExtendedKeyUsage::WithAllRoles exept ClientAuth
    WithAllButServerAuth,                  ///< Same as @ref ExtendedKeyUsage::WithAllRoles exept ServerAuth
    WithoutAnyRoles,                       ///< Empty set of roles
    MissingSdcProviderRole,                ///< Same as @ref ExtendedKeyUsage::WithAllRoles exept missing SdcProvider role
    MissingSdcConsumerRole                 ///< Same as @ref ExtendedKeyUsage::WithAllRoles exept missing SdcConsumer role
};


/// @brief Sequence of shared X509 certificate revocation lists.
/// @ingroup S31Nomenclature
using X509RevocationLists = std::vector<std::shared_ptr<X509_CRL>>;


/**
 * @brief Convert a @ref DFL::Crypto::Certificate to a certificate chain as needed for @ref S31::CoreConfiguration
 *
 * @ingroup S31Nomenclature
 */
inline DFL::Crypto::CertificateChain certToCertificateChain(const DFL::Crypto::Certificate& cert)
{
    return DFL::Crypto::CertificateChain(DFL::Crypto::Convert::toPem(cert));
}


/**
 * @brief Get a @ref DFL::Crypto::PrivateKey for testing
 *
 * @ingroup S31Nomenclature
 */
inline const DFL::Crypto::PrivateKey& generatePrivateKey(const std::string& commonName)
{
    static std::map<std::string, DFL::Crypto::PrivateKey> keyCache;

    return Impl::findOrCreateCachedValue(
        keyCache,
        commonName,
        []()
        {
            return DFL::Crypto::Test::generateCertificatePrivateKey();
        });
}


/**
 * @brief Create a @ref S31::Nomenclature::Whitelist which contains only the wildcard string, for cases where a specific whitelist is not needed.
 * @ingroup S31Nomenclature
 */
inline S31::Nomenclature::Whitelist wildcardWhiteList()
{
    return S31::Nomenclature::Whitelist(DFL::Crypto::Whitelist("*_*_305"));
}
/**
 * @brief Create a @ref S31::Nomenclature::Whitelist which contains all relevant common names for testing
 * @ingroup S31Nomenclature
 */
inline S31::Nomenclature::Whitelist testWhiteList()
{
    const std::string crlf("\r\n");
    return S31::Nomenclature::Whitelist(DFL::Crypto::Whitelist("*_*_305" + crlf + "ITTestRunnerDev" + crlf + "IntegrationTest_" + crlf + "IntegrationTest_MissingConsumerRole" + crlf + "ITTestDevice" + crlf + "ITHttpTestClient"));
}

/**
 * @brief Create a @ref S31::Nomenclature::Whitelist which contains all relevant common names for an independent Test device interacting with PySDC.
 * @ingroup S31Nomenclature
 */
inline S31::Nomenclature::Whitelist pySdcWhiteList()
{
    const std::string crlf("\r\n");
    return S31::Nomenclature::Whitelist(DFL::Crypto::Whitelist("*_*_305" + crlf + "ITTestRunnerDev" + crlf + "PySDC_TEST-RTF_305"));
}

/**
 * @brief Select @ref DFL::Oids that define the roles for a @ref DFL::Crypto::Certificate
 *
 * @ingroup S31Nomenclature
 */
inline DFL::Oids keyUsageRoles(ExtendedKeyUsage keyUsage)
{
    switch (keyUsage)
    {
        case ExtendedKeyUsage::WithTlsServerClientAuthenticationRoles:
            return DFL::Oids{
                S31::Nomenclature::TlsWebServerAuthentication,
                S31::Nomenclature::TlsWebClientAuthentication
            };

        case ExtendedKeyUsage::WithoutOperationConsumerRole:
            return DFL::Oids{
                S31::Nomenclature::TlsWebServerAuthentication,
                S31::Nomenclature::TlsWebClientAuthentication,
                S31::Nomenclature::SdcServiceProvider,
                S31::Nomenclature::SdcServiceConsumer,
                S31::Nomenclature::DraegerSpecificSdcConsumer
            };

        case ExtendedKeyUsage::WithAllRoles:
            return DFL::Oids{
                S31::Nomenclature::TlsWebServerAuthentication,
                S31::Nomenclature::TlsWebClientAuthentication,
                S31::Nomenclature::SdcServiceProvider,
                S31::Nomenclature::SdcServiceConsumer,
                S31::Nomenclature::SdcOperationConsumer,
                S31::Nomenclature::DraegerSpecificSdcConsumer
            };

        case ExtendedKeyUsage::WithAllButClientAuth:
            return DFL::Oids{
                S31::Nomenclature::TlsWebServerAuthentication,
                S31::Nomenclature::SdcServiceProvider,
                S31::Nomenclature::SdcServiceConsumer,
                S31::Nomenclature::SdcOperationConsumer,
                S31::Nomenclature::DraegerSpecificSdcConsumer
            };

        case ExtendedKeyUsage::WithAllButServerAuth:
            return DFL::Oids{
                S31::Nomenclature::TlsWebClientAuthentication,
                S31::Nomenclature::SdcServiceProvider,
                S31::Nomenclature::SdcServiceConsumer,
                S31::Nomenclature::SdcOperationConsumer,
                S31::Nomenclature::DraegerSpecificSdcConsumer
            };

        case ExtendedKeyUsage::WithoutAnyRoles:
            return DFL::Oids{};

        case ExtendedKeyUsage::MissingSdcProviderRole:
            return DFL::Oids{
                S31::Nomenclature::TlsWebServerAuthentication,
                S31::Nomenclature::TlsWebClientAuthentication,
                S31::Nomenclature::SdcServiceConsumer,
                S31::Nomenclature::SdcOperationConsumer,
                S31::Nomenclature::DraegerSpecificSdcConsumer
            };

        case ExtendedKeyUsage::MissingSdcConsumerRole:
            return DFL::Oids{
                S31::Nomenclature::TlsWebServerAuthentication,
                S31::Nomenclature::TlsWebClientAuthentication,
                S31::Nomenclature::SdcServiceProvider,
                S31::Nomenclature::SdcOperationConsumer,
                S31::Nomenclature::DraegerSpecificSdcConsumer
            };

        default:
            S31_THROW_EXCEPTION(InternalDataMappingFailed, "Unknown value");
    }
}

/**
 * @brief A default @ref DFL::Crypto::Test::ValidityPeriod
 *
 * @details Provides certificate validity starting from one day ago,
 * valid until one year from now.
 *
 * @ingroup S31Nomenclature
 */
inline ::DFL::Crypto::Test::ValidityPeriod validForOneYear()
{
    using namespace ::DFL::Chrono;
    return ::DFL::Crypto::Test::ValidityPeriod()
            .validFrom(SystemClock::now() - Days{1})
            .validFor(Years{1});
}

/**
 * @brief Creates certificate chain for given key (signed with test root).
 *
 * @details Same as leafCertWithAllRoles(), but does not use a cache
 * optimization, and allows specifying a custom set of roles.
 *
 * @ingroup S31Nomenclature
 */
inline DFL::Crypto::CertificateChain leafCertNoCache(const std::string& commonName, const DFL::Crypto::PrivateKey& privateKey, const DFL::Oids& roles)
{
    const auto& cert = DFL::Crypto::Test::createTestrootCaSignedLeafCertificate(
            commonName,
            DFL::Crypto::PublicKey(privateKey),
            validForOneYear(),
            roles);

    return DFL::Crypto::CertificateChain(DFL::Crypto::Convert::toPem(cert));
}

/**
 * @brief Creates certificate chain for given key (signed with test root).
 *
 * @details Same as leafCertWithAllRoles() but not using a cache.
 *
 * @ingroup S31Nomenclature
 */
inline DFL::Crypto::CertificateChain leafCertWithAllRolesNoCache(const std::string& commonName, const DFL::Crypto::PrivateKey& privateKey)
{
    return leafCertNoCache(commonName, privateKey, keyUsageRoles(ExtendedKeyUsage::WithAllRoles));
}

/**
 * @brief Helper for most common use case in tests.
 *
 * @details
 * Create a certificate using @ref DFL::Crypto::Test::createTestrootCaSignedLeafCertificate()
 * with valid dates for one year and supporting all roles
 * (as defined with @ref ExtendedKeyUsage::WithAllRoles) in it's EKU.
 *
 * @note This function provides an optimization by keeping a cache to avoid re-creating very
 * often used certificates.  But this must only be used for 'all roles' certificates to avoid
 * finding a cached certificate with incorrect set of roles.
 *
 * @ingroup S31Nomenclature
 */
inline DFL::Crypto::CertificateChain leafCertWithAllRoles(const std::string& commonName, const DFL::Crypto::PrivateKey& privateKey)
{
    static std::map<std::string, DFL::Crypto::Certificate> certCache;

    auto&& cert = Impl::findOrCreateCachedValue(
        certCache,
        commonName,
        [&privateKey, &commonName]()
        {
            return DFL::Crypto::Test::createTestrootCaSignedLeafCertificate(
                    commonName,
                    DFL::Crypto::PublicKey(privateKey),
                    validForOneYear(),
                    keyUsageRoles(ExtendedKeyUsage::WithAllRoles));
        });

    return DFL::Crypto::CertificateChain(DFL::Crypto::Convert::toPem(cert));
}

/**
 * @brief Helper function to create a mock remote certificate.
 * @details Create a single Certificate signed by Draeger Test root, using the provided
 * common name and role Oids. Valid for 1 year. Private key is hidden, so certificate
 * can only be used as a communication peer mock.
 * @ingroup S31Nomenclature
 */
inline DFL::Crypto::Certificate mockRemoteCertificate(const std::string& commonName, const DFL::Oids& roles)
{
    static const auto privateKey = DFL::Crypto::Test::generateCertificatePrivateKey();

    return DFL::Crypto::Test::createTestrootCaSignedLeafCertificate(
            commonName,
            DFL::Crypto::PublicKey(privateKey),
            validForOneYear(),
            roles);
}

/**
 * @brief Utility to create a certificate revocation list from a certificate
 *
 * @ingroup S31Nomenclature
 */
inline X509RevocationLists createCertificateRevocation(const DFL::Crypto::Certificate& cert)
{
    // Note: this function should be removed when DFL::Crypto::Test implements utility to
    // create certificate revocation lists for testing. The rootCaCertKey, and rootCaCertString
    // are expecting to be equal to the test root Ca cert and key from DFL::Crypto

    typedef std::unique_ptr<::ASN1_INTEGER, decltype(&::ASN1_INTEGER_free)> Asn1IntegerPtr;
    typedef std::unique_ptr<::X509_CRL    , decltype(&::X509_CRL_free)    > X509CrlPtr;
    typedef std::unique_ptr<::X509_REVOKED, decltype(&::X509_REVOKED_free)> X509RevokedPtr;

    using namespace DFL::Crypto;

    auto caKey = PrivateKey(PemString(S31::Nomenclature::Test::Impl::rootCaCertKey));
    auto caCert = Certificate(PemString(S31::Nomenclature::Test::Impl::rootCaCertString));

    auto crl = X509CrlPtr(::X509_CRL_new(), ::X509_CRL_free);

    if (!X509_CRL_set_version(crl.get(), 1))
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, "Cannot set crl version");
    }

    auto tm = OpenSsl::Asn1TimeNew();
    if (!tm)
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, "Cannot create time for crl");
    }
    X509_gmtime_adj(tm.get(), 0);
    X509_CRL_set_lastUpdate(crl.get(), tm.get());

    static int crlSerial = 1;
    auto serial = Asn1IntegerPtr(::ASN1_INTEGER_new(), ::ASN1_INTEGER_free);
    ASN1_INTEGER_set(serial.get(), crlSerial++);
    X509_CRL_add1_ext_i2d(crl.get(), NID_crl_number, serial.get(), 0, 0);

    X509_gmtime_adj(tm.get(), 24 * 60 * 60);
    X509_CRL_set_nextUpdate(crl.get(), tm.get());

    if (!X509_CRL_set_issuer_name(crl.get(), X509_get_subject_name(caCert.certificate())))
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, "Unable to set the issuer name for the new CRL");
    }

    auto revoked = X509RevokedPtr(::X509_REVOKED_new(), ::X509_REVOKED_free);
    if (!revoked)
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, "Unable to create an X509_REVOKED object");
    }

    auto* certX509 = const_cast<::X509*>(cert.certificate());
    if (!X509_REVOKED_set_serialNumber(revoked.get(), X509_get_serialNumber(certX509)))
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, "Unable to set serial number");
    }

    // cert was one second ago revoked
    X509_gmtime_adj(tm.get(), -1);
    if (!X509_REVOKED_set_revocationDate(revoked.get(), tm.get()))
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, "Unable to set revocation date");
    }

    X509_CRL_add0_revoked(crl.get(), revoked.release());

    X509_CRL_sort(crl.get());
    // const_cast: OpenSSL is not entirely const-correct and DFL::Crypto doesn't want to expose a non-const pointer to EVP_PKEY
    X509_CRL_sign(crl.get(), const_cast<EVP_PKEY*>(caKey.privateKey()), EVP_sha1());

    return X509RevocationLists{ std::move(crl) };
}

inline DFL::Crypto::RootCas rootCasWithTestRoots()
{
    // These are the default roots
    auto base = S31::Nomenclature::sdcRootCas();

    std::vector<DFL::Crypto::Certificate> allRootCas;
    std::move(base.begin(), base.end(), std::back_inserter(allRootCas));

    // Only add test roots in case they are not already there.
    if (std::find(allRootCas.begin(), allRootCas.end(), DFL::Crypto::Test::KnownRootCas::draegerTest()) == allRootCas.end())
    {
        allRootCas.push_back(DFL::Crypto::Test::KnownRootCas::draegerTest());
    }
    if (std::find(allRootCas.begin(), allRootCas.end(), DFL::Crypto::Test::KnownRootCas::staging()) == allRootCas.end())
    {
        allRootCas.push_back(DFL::Crypto::Test::KnownRootCas::staging());
    }
    return DFL::Crypto::RootCas{std::move(allRootCas)};
}

inline S31::Nomenclature::ProvideRootCasFunction makeProvideFunction(const DFL::Crypto::RootCas& rootCas)
{
    S31::Nomenclature::ProvideRootCasFunction result = [rootCas](){ return rootCas; };
    return result;
}

inline S31::Nomenclature::ProvidePrivateKeyFunction makeProvideFunction(const boost::optional<DFL::Crypto::PrivateKey>& key)
{
    S31::Nomenclature::ProvidePrivateKeyFunction result = [key](){ return key; };
    return result;
}

inline S31::Nomenclature::ProvideCertificateChainFunction makeProvideFunction(const DFL::Crypto::CertificateChain& chain)
{
    S31::Nomenclature::ProvideCertificateChainFunction result = [chain](){ return chain; };
    return result;
}

inline S31::Nomenclature::ProvideRoleAuthorizationListFunction makeProvideFunction(const DFL::Crypto::RoleAuthorizationList& ral)
{
    S31::Nomenclature::ProvideRoleAuthorizationListFunction result = [ral](){ return ral; };
    return result;
}

inline S31::Nomenclature::WhitelistCheckFunction makeCheckFunction(const S31::Nomenclature::Whitelist& whitelist)
{
    S31::Nomenclature::WhitelistCheckFunction result = [whitelist](const std::string& peer){ return whitelist.check(peer); };
    return result;
}

inline S31::Nomenclature::WhitelistCheckFunction makeCheckFunctionWithWildcardOnly()
{
    return makeCheckFunction(wildcardWhiteList());
}

inline S31::Nomenclature::WhitelistCheckFunction makeCheckFunctionWithTestWhitelist()
{
    return makeCheckFunction(testWhiteList());
}

inline S31::Nomenclature::WhitelistCheckFunction makeCheckFunctionWithPySdcWhitelist()
{
    return makeCheckFunction(pySdcWhiteList());
}

}
