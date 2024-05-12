#pragma once

#include <Framework/Crypto/Private/Algorithm.h>

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
 * @brief
 * Creates a digital signature for the given message using the given signature
 * algorithm.
 *
 * @throw Whatever the used signature algoritm may throw.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp sigSetup
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp sign
 *
 * @ingroup Crypto
 */
template <class Signature>
inline Encoding::Bytes sign(
    Signature& signature,
    Encoding::BytesView message)
{
    Impl::apply(signature, message);
    return signature.signature();
}
}
}
}
}
