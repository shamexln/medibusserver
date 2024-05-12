#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Ral/Roles.h>
#include <Framework/Crypto/Private/Ral/Verify.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Utils/Public/ConstContainer.h>
#include <Framework/Utils/Public/Oid.h>
#include <Framework/Utils/Public/Oids.h>

#include <string>
#include <utility>
#include <vector>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
namespace Ral
{
enum class Error
{
    Success, // has to be 0 because std::error_code expect 0 to be success
    RoleNotFound,
    FingerprintNotFound
};
using Fingerprint = Encoding::Bytes;
using Fingerprints = std::vector<Fingerprint>;
using RolesByFingerprint = std::pair<Fingerprint, Roles>;
using ManyRolesByFingerprint = std::vector<RolesByFingerprint>;

class DFL_CRYPTO_EXPIMP Type
{
public:
    Type() = default;
    Type(std::string com, ManyRolesByFingerprint manyRolesByFp, Signature sig);

    void swap(Type& other) noexcept;

    Roles operator[](const Fingerprint& fp) const;

    std::string comment{};
    ManyRolesByFingerprint manyRolesByFingerprint{};
    Signature signature{};
};
DFL_CRYPTO_EXPIMP bool operator==(const Type& a, const Type& b) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const Type& a, const Type& b) noexcept;

DFL_CRYPTO_EXPIMP void swap(Type& a, Type& b) noexcept;

DFL_CRYPTO_EXPIMP Error containsRoleByFingerprint(const Role& role,
                                                  const Fingerprints& fps,
                                                  const Type& ral);
}
}
}
}
