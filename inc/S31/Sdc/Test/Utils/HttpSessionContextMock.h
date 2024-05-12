#pragma once

#include <S31/Nomenclature/Test/Public/CertHelper.h>
#include <S31/Nomenclature/Test/Public/CryptoStoreHelper.h>
#include <S31/Sdc/Private/Common/Http/HttpSessionContext.h>

#include <Framework/Utils/Public/NotNull.h>

namespace S31::Sdc::Impl::Test
{
/**
 * @brief Dummy HttpSessionContext to use for tests.
 */
inline DFL::NotNull<std::shared_ptr<const S31::Sdc::Impl::HttpSessionContext>> dummyHttpSessionContext()
{
    auto provideRal  = []() { return S31::Test::ralWithTestRoot(); };
    auto roles       = Utils::Test::CertHelper::keyUsageRoles(Utils::Test::CertHelper::ExtendedKeyUsage::WithAllRoles);
    auto credentials = S31::Nomenclature::Credentials{
            S31::Nomenclature::PeerCertificate{
                    S31::Utils::Test::CertHelper::mockRemoteCertificate("TEST_ABCD_305", roles)},
            S31::Nomenclature::WhiteListingState::ExplicitlyWhitelistedByCommonName,
            provideRal,
            S31::Nomenclature::RootCertificate{DFL::Crypto::Test::KnownRootCas::draegerTest()}};

        constexpr std::uint16_t localPort = 6464U;
        constexpr std::uint16_t remotePort = 56464U;
        return DFL::asNotNull(std::make_shared<S31::Sdc::Impl::HttpSessionContext>(
                S31::Sdc::Impl::ConnectionDirection::Incoming,
                "127.0.0.1",
                localPort,
                "127.0.0.2",
                remotePort,
                credentials));
}
}  // namespace S31::Sdc::Impl::Test
