#pragma once

#include <S31/Base/S31Only/Exception.h>
#include <S31/Nomenclature/Public/Roles.h>
#include <S31/Nomenclature/Public/SdcCertificateId.h>
#include <S31/Nomenclature/Test/Public/CertHelper.h>
#include <S31/Utils/Public/CryptoStoreCache.h>

#include <Framework/Crypto/Public/Store.h>
#include <Framework/Crypto/Public/Table.h>
#include <Framework/Crypto/Test/Public/KnownRootCas.h>
#include <Framework/Crypto/Test/Public/MockPersistence.h>
#include <Framework/Crypto/Test/Public/RalBuilder.h>
#include <Framework/Utils/Public/NotNull.h>

namespace S31::Test
{
namespace Impl
{
inline void createSdcTableItemIfNecessary()
{
    auto& cache = S31::Utils::CryptoStoreCache::instance();
    cache.forceSynchronousUpdate();
    // A dummy object (therefore the random commonname) if there is no one.
    // If other tests start using the crypto store then this has to be reworked.
    if (!cache.table()[S31::Nomenclature::sdcCertificateId()])
    {
        DFL::Crypto::Store::requestCertificateFor(S31::Nomenclature::sdcCertificateId(),
                                                  DFL::Crypto::CommonName("SomeThing_107598578917589345"),
                                                  S31::Utils::Test::CertHelper::keyUsageRoles(
                                                      S31::Utils::Test::CertHelper::ExtendedKeyUsage::WithAllRoles));
        cache.forceSynchronousUpdate();
    }
}
}

/// @brief Provide Mock (in-memory) persistence for the Crypto Store
/// @details In order to avoid problems running in test in parallel, or using
/// test shuffling, tests use the Public Crypto Store interface can use this
/// function to setup an in-memory persistence to avoid accessing the filesystem.
/// This will avoid conflicts between multiple processes modifying the same file.
inline DFL::NotNull<std::unique_ptr<DFL::Crypto::Test::ThreadsafeMockPersistence>> setupMockPersistenceForCryptoStore()
{
    return DFL::asNotNull(std::make_unique<DFL::Crypto::Test::ThreadsafeMockPersistence>(DFL::Crypto::Table{}));
}

/// Sets the test root CA to the crypto store.
/// Existing root CAs in the store will be overwritten.
inline void setTestRootInStore()
{
    Impl::createSdcTableItemIfNecessary();

    std::string error;
    if (!DFL::Crypto::Store::rootCasFor(S31::Nomenclature::sdcCertificateId(),
                                   DFL::Crypto::RootCas{DFL::Crypto::Test::KnownRootCas::draegerTest()},
                                   error))
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, error);
    }
    S31::Utils::CryptoStoreCache::instance().forceSynchronousUpdate();
}

/// Returns s RAL that allows the test root for 'operation consumer'
inline DFL::Crypto::RoleAuthorizationList ralWithTestRoot()
{
    const std::string ralStr =
        DFL::Crypto::Test::RalBuilder{}
            .comment("This is a RAL with invalid signature - but still good for testing")
            .roles(DFL::Crypto::Test::KnownRootCas::draegerTest(), DFL::Oids{DFL::Mdib::OperationConsumer.get()})
            .str();

    return DFL::Crypto::RoleAuthorizationList{ralStr};
}

/// Sets the whitelist in the crypto store.
inline void setWhitelistInStore(const std::string& newWhitelist)
{
    Impl::createSdcTableItemIfNecessary();

    std::string error;
    if (!DFL::Crypto::Store::whitelistFor(S31::Nomenclature::sdcCertificateId(),
                                   DFL::Crypto::Whitelist(newWhitelist),
                                   error))
    {
        S31_THROW_EXCEPTION(InternalConsistencyFailure, error);
    }
    S31::Utils::CryptoStoreCache::instance().forceSynchronousUpdate();
}

}
