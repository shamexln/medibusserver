#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL::Crypto::MessageDigest::Signature
{
class EcdsaSig;
/**
 * @brief Creates readable form of given ECDSA signature.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestEcdsaSig.cpp streaming
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str,
                                           const EcdsaSig& ecdsaSig);
}

namespace DFL::Format
{
class Stream;
/**
 * @brief Creates readable form of given ECDSA signature.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestEcdsaSig.cpp streaming
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(
    Stream& str,
    const Crypto::MessageDigest::Signature::EcdsaSig& ecdsaSig);
}
