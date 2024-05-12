#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class PemString;
/**
 * @brief Creates readable form of given PEM string.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const PemString& pem);
/**
 * @brief Constructs PEM string from string within istream.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::istream& operator>>(std::istream& str, PemString& pem);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given PEM string.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::PemString& pem);
}
}
