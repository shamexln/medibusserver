#pragma once

#include <Framework/Crypto/Private/Ral/Type.h>
#include <Framework/Crypto/Public/MessageDigest/Hash/Sha256.h>
#include <Framework/Crypto/Public/MessageDigest/Signature/Sign.h>
#include <Framework/Crypto/Public/MessageDigest/Signature/Signature.h>
#include <Framework/Crypto/Public/MessageDigest/Signature/Verification.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>
#include <Framework/Encoding/Public/BytesViewIo.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StreamEach.h>
#include <Framework/Format/Public/ToString.h>
#include <Framework/Utils/Public/OidIo.h>

#include <string>

namespace DFL
{
namespace Crypto
{
namespace Test
{
namespace Impl
{
const std::string lineSep{'\n'};
const std::string fpRolesSep{';'};
const std::string rolesSep{','};

inline std::string generate(const Crypto::Impl::Ral::Roles& roles)
{
    Format::Stream str{};
    return Format::streamEach(str,
                              roles.cbegin(),
                              roles.cend(),
                              "",
                              "",
                              rolesSep.at(0))
        .cStr();
}

inline std::string generateFingerprint(const Crypto::Impl::Ral::Fingerprint& fp)
{
    return Format::toString(Encoding::BytesView{fp});
}

inline std::string generate(const Crypto::Impl::Ral::RolesByFingerprint& rsfp)
{
    Format::Stream str{};
    const auto& fp = rsfp.first;
    const auto& roles = rsfp.second;
    str << generateFingerprint(fp) << fpRolesSep << generate(roles);
    return str.cStr();
}

inline std::string generate(
    const Crypto::Impl::Ral::ManyRolesByFingerprint& mrsfp)
{
    Format::Stream str{};
    if (mrsfp.empty())
    {
        str << lineSep;
    }
    else
    {
        for (const auto& rsfp : mrsfp)
        {
            str << generate(rsfp) << lineSep;
        }
    }
    return str.cStr();
}

inline std::string generateSignature(
    const Crypto::Impl::Ral::Signature& signature)
{
    return Format::toString(Encoding::BytesView{signature});
}

inline std::string generatePayload(const Crypto::Impl::Ral::Type& ral)
{
    if (ral == Crypto::Impl::Ral::Type{}) return {};
    return ral.comment + lineSep + generate(ral.manyRolesByFingerprint);
}

inline std::string generate(const Crypto::Impl::Ral::Type& ral)
{
    if (ral == Crypto::Impl::Ral::Type{}) return {};

    Format::Stream str{};
    str << generatePayload(ral);
    str << generateSignature(ral.signature) << lineSep;
    return str.cStr();
}

inline Encoding::Bytes createSignature(const PrivateKey& privateKey,
                                       const std::string& message)
{
    MessageDigest::Signature::Signature<MessageDigest::Hash::Sha256> signature{
        privateKey};
    return MessageDigest::Signature::sign(signature, message);
}
}
}
}
}
