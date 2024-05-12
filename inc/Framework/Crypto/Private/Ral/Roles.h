#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Utils/Public/Oid.h>
#include <Framework/Utils/Public/Oids.h>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
namespace Ral
{
using Role = Oid;
using Roles = Oids;

DFL_CRYPTO_EXPIMP bool contains(const Roles& roles, const Role& role) noexcept;
}
}
}
}
