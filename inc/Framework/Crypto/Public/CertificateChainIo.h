#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class CertificateChain;
/**
 * @brief Creates readable form of given chain.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp ostream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const CertificateChain& chain);
/**
 * @brief Constructs chain from pem-string within istream.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp istream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::istream& operator>>(std::istream& str, CertificateChain& chain);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given chain.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp format
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::CertificateChain& chain);
}
}
