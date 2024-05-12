#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class Certificates;
/**
 * @snippet Crypto/Test/UnitTest/TestCertificates.cpp ostream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str,
                                           const Certificates& certs);
}
namespace Format
{
class Stream;
/**
 * @snippet Crypto/Test/UnitTest/TestCertificates.cpp format_stream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str,
                                     const Crypto::Certificates& certs);
}
}
