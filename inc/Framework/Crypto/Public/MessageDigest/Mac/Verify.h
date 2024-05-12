#pragma once

#include <Framework/Crypto/Private/Algorithm.h>
#include <Framework/Crypto/Private/MessageDigest/Signature.h>

#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Mac
{
/**
 * @brief Compares the given MACs in a secure way.
 *
 * @details
 * In order to be invulnerable against timing attacks,
 * a constant time equals is used for comparison of MAC values.
 * See https://codahale.com/a-lesson-in-timing-attacks/
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestHmac.cpp initUpdateFinal
 *
 * @ingroup Crypto
 */
inline bool verify(
    Encoding::BytesView expectedMac,
    Encoding::BytesView actualMac)
{
    return Impl::constantTimeEquals(expectedMac, actualMac);
}

/**
 * @brief
 * Verifies expectedMac against a given message using the given mac
 * algorithm.
 *
 * @throw Whatever the used mac algoritm may throw.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestHmac.cpp verify
 *
 * @ingroup Crypto
 */
template <class Mac>
inline bool verify(
    Mac& mac,
    Encoding::BytesView message,
    Encoding::BytesView expectedMac)
{
    Impl::apply(mac, message);
    return verify(expectedMac, mac.mac());
}
}
}
}
}
