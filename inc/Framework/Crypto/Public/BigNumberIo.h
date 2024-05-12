#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <ostream>

namespace DFL::Format
{
class Stream;
}
namespace DFL::Crypto
{
class BigNumber;
/**
 * @brief Streams given bignumber into given stream.
 *
 * @snippet Crypto/Test/UnitTest/TestBigNumber.cpp stream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Format::Stream& operator<<(Format::Stream& str,
                                             const BigNumber& a);
/**
 * @brief Streams given bignumber into given stream.
 *
 * @snippet Crypto/Test/UnitTest/TestBigNumber.cpp stream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str,
                                           const BigNumber& a);
}
