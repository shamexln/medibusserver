#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class Whitelist;
/**
 * @brief Creates readable form of given list.
 *
 * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp ostream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const Whitelist& list);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given list.
 *
 * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp format
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::Whitelist& list);
}
}
