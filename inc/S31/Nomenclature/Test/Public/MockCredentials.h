#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Nomenclature/Test/Public/CertHelper.h>

namespace S31::Nomenclature::Test
{

// Can be used if a soap struct needs somewhere roles and whitelisting.
inline Credentials mockCredentials(const DFL::Oids& roles)
{
    auto cert = Utils::Test::CertHelper::mockRemoteCertificate("MockCommonName", roles);
    auto ral = Utils::Test::CertHelper::makeProvideFunction(DFL::Crypto::RoleAuthorizationList{});

    return Credentials(
            PeerCertificate{cert},
            WhiteListingState::ExplicitlyWhitelistedByCommonName,
            std::move(ral),
            RootCertificate{});
}

}
