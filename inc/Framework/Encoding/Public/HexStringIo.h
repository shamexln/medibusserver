#pragma once

#include <Framework/Encoding/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
namespace Encoding
{
class HexString;
/**
 * @brief Creates readable form of given hex string.
 *
 * @snippet Encoding/Test/UnitTest/TestHexString.h streaming
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP std::ostream& operator<<(
    std::ostream& str, const HexString& hexStr);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given hex string.
 *
 * @snippet Encoding/Test/UnitTest/TestHexString.h streaming
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP Stream& operator<<(
    Stream& str, const Encoding::HexString& hexStr);
}
}
