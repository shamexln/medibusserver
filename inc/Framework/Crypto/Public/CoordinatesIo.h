#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <ostream>

namespace DFL::Format
{
class Stream;
}
namespace DFL::Crypto
{
class Coordinates;
/**
 * @brief Streams given coordinates into given stream.
 *
 * @snippet Crypto/Test/UnitTest/TestCoordinates.cpp stream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Format::Stream& operator<<(Format::Stream& str,
                                             const Coordinates& a);
/**
 * @brief Streams given coordinates into given stream.
 *
 * @snippet Crypto/Test/UnitTest/TestCoordinates.cpp stream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str,
                                           const Coordinates& a);
}
