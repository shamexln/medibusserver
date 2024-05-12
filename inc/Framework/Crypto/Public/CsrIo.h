#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class Csr;
/**
 * @brief Creates readable form of given csr.
 *
 * @snippet Crypto/Test/UnitTest/TestCsr.cpp ostream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const Csr& csr);
/**
 * @brief Constructs csr from pem-string within istream.
 *
 * @snippet Crypto/Test/UnitTest/TestCsr.cpp istream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::istream& operator>>(std::istream& str, Csr& csr);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given csr.
 *
 * @snippet Crypto/Test/UnitTest/TestCsr.cpp fstream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::Csr& csr);
}
}
