#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class Certificate;
/**
 * @brief Creates readable form of given certificate.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str,
                                           const Certificate& certificate);
/**
 * @brief Constructs certificate from pem-string within istream.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::istream& operator>>(std::istream& str,
                                           Certificate& certificate);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given certificate.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::Certificate& certificate);
}
}
