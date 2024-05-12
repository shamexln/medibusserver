#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Ral/Type.h>

#include <Framework/Encoding/Public/BytesView.h>

#include <boost/utility/string_view.hpp>

#include <vector>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
namespace Ral
{
namespace Parser
{
DFL_CRYPTO_EXPIMP std::vector<boost::string_view> split(boost::string_view txt,
                                                        boost::string_view sep,
                                                        bool includeSep);

DFL_CRYPTO_EXPIMP boost::string_view isComment(boost::string_view txt);
DFL_CRYPTO_EXPIMP Fingerprint isFingerprint(boost::string_view txt);
DFL_CRYPTO_EXPIMP Role isRole(boost::string_view txt);
DFL_CRYPTO_EXPIMP Roles isRoles(boost::string_view txt);
DFL_CRYPTO_EXPIMP RolesByFingerprint
isRolesByFingerprint(boost::string_view txt);
DFL_CRYPTO_EXPIMP ManyRolesByFingerprint
isManyRolesByFingerprint(const std::vector<boost::string_view>& lines);
DFL_CRYPTO_EXPIMP Signature isSignature(boost::string_view txt);
DFL_CRYPTO_EXPIMP Type isRoleAuthorizationList(boost::string_view txt);

struct DFL_CRYPTO_EXPIMP Blocks
{
    Blocks() = default;
    Blocks(boost::string_view comment,
           std::vector<boost::string_view> roles,
           boost::string_view signature);

    boost::string_view m_comment{};
    std::vector<boost::string_view> m_roles{};
    boost::string_view m_signature{};
};
DFL_CRYPTO_EXPIMP Blocks splitBlocks(boost::string_view txt);

struct DFL_CRYPTO_EXPIMP PayloadSignature
{
    PayloadSignature() = default;
    PayloadSignature(Encoding::BytesView payload, Signature signature);

    Encoding::BytesView m_payload{};
    Signature m_signature{};
};
DFL_CRYPTO_EXPIMP PayloadSignature
splitPayloadSignature(boost::string_view txt);
}
}
}
}
}
