#pragma once

#include <Framework/Crypto/Private/Ral/Type.h>
#include <Framework/Crypto/Private/Ral/Verify.h>
#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Test/Private/RalBuilder.h>

#include <Framework/Utils/Public/Oids.h>

#include <string>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief Generates a RAL string from given attributes.
 *
 * Details on the string format can be found in
 * @ref DFL::Crypto::RoleAuthorizationList.
 *
 * @snippet Crypto/Sample/Sample.cpp Ral
 *
 * @ingroup Crypto
 */
class RalBuilder
{
public:
    /**
     * @brief Sets the given comment.
     */
    RalBuilder& comment(const std::string& c)
    {
        m_ral.comment = c;
        return *this;
    }
    /**
     * @brief Appends the given roles.
     */
    RalBuilder& roles(const Certificate& c, const Oids& r)
    {
        m_ral.manyRolesByFingerprint.push_back(
            Crypto::Impl::Ral::RolesByFingerprint{c.fingerprint(), r});
        return *this;
    }
    /**
     * @brief Sets the signature using the given private key.
     *
     * @pre comment and roles have been called.
     */
    RalBuilder& signature(const ::DFL::Crypto::PrivateKey& pk)
    {
        m_ral.signature = Crypto::Impl::Ral::Signature{
            Impl::createSignature(pk, Impl::generatePayload(m_ral))};
        return *this;
    }
    /**
     * @brief Generates a RAL string from the given attributes.
     *
     * @pre comment, roles and signature have been called.
     */
    std::string str() const
    {
        return Impl::generate(m_ral);
    }

private:
    Crypto::Impl::Ral::Type m_ral{};
};
}
}
}
