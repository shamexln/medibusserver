#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class RoleAuthorizationList;
/**
 * @brief Streams the whole RAL string.
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str,
                                           const RoleAuthorizationList& ral);
}
namespace Format
{
class Stream;
/**
 * @brief Streams a summary of the RAL.
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str,
                                     const Crypto::RoleAuthorizationList& ral);
}
}
