#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class DistinguishedName;
/**
 * @brief Creates readable form of given distinguished name.
 *
 * @snippet Crypto/Test/UnitTest/TestDistinguishedName.cpp Streaming
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const DistinguishedName& dn);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given distinguished name.
 *
 * @snippet Crypto/Test/UnitTest/TestDistinguishedName.cpp Streaming
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::DistinguishedName& dn);
}
}
