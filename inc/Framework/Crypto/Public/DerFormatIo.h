#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class DerFormat;
/**
 * @brief Creates readable form (hex view) of given binary DER format.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str,
                                           const DerFormat& der);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form (hex view) of given binary DER format.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::DerFormat& der);
}
}
