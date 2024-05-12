#pragma once

#include <Framework/Crypto/Private/Ral/Type.h>
#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/PublicKey.h>

#include <string>

namespace DFLTest
{
namespace Crypto
{
namespace UnitTest
{
namespace Ral
{
struct TestSet
{
    static const std::string lineSep;
    static const std::string fpRolesSep;
    static const std::string rolesSep;

    static TestSet signedWithFakeKey();
    static TestSet signedWithRealKey();

    std::string m_strComment{};
    std::string m_strFp{};
    std::string m_strRoles{};
    std::string m_strRolesByFp{};
    std::string m_strManyRolesByFp{};
    std::string m_strPayload{};
    std::string m_strSignature{};
    std::string m_strRal{};
    ::DFL::Crypto::Certificate m_certificate;
    ::DFL::Crypto::Impl::Ral::Fingerprint m_expectedFp{};
    ::DFL::Crypto::Impl::Ral::Roles m_expectedRoles{};
    ::DFL::Crypto::Impl::Ral::RolesByFingerprint m_expectedRolesByFp{};
    ::DFL::Crypto::Impl::Ral::ManyRolesByFingerprint m_expectedManyRolesByFp{};
    ::DFL::Crypto::Impl::Ral::Signature m_expectedSig{};
    ::DFL::Crypto::Impl::Ral::Type m_type{};
    ::DFL::Crypto::PrivateKey m_privateKey{};
    ::DFL::Crypto::PublicKey m_publicKey{};

private:
    TestSet() = default;
};
}
}
}
}
