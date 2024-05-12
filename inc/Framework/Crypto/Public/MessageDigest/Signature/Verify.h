#pragma once

#include <Framework/Crypto/Private/Algorithm.h>
#include <Framework/Crypto/Private/MessageDigest/Signature.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Signature
{
/**
 * @brief Compares the given signatures in a secure way.
 *
 * @details
 * In order to be invulnerable against timing attacks,
 * a constant time equals is used for comparison of signature values.
 * See https://codahale.com/a-lesson-in-timing-attacks/
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp sigSetup
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp sign
 *
 * @ingroup Crypto
 */
inline bool verify(
    Encoding::BytesView expectedSignature,
    Encoding::BytesView actualSignature)
{
    return Impl::constantTimeEquals(expectedSignature, actualSignature);
}

/**
 * @brief
 * Verifies expectedSignature against a given message using the given
 * verification algorithm.
 *
 * @throw Whatever the used verification algoritm may throw.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp verSetup
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp verify
 *
 * @ingroup Crypto
 */
template <class Verification>
inline bool verify(
    Verification& verification,
    Encoding::BytesView message,
    Encoding::BytesView expectedSignature)
{
    verification.signature(expectedSignature);
    Impl::apply(verification, message);
    return verification.passed();
}
}
}
}
}
