#pragma once

#include <Framework/Crypto/Public/MessageDigest/Signature/Signature.h>
#include <Framework/Crypto/Public/PrivateKey.h>

#include <Framework/Config/Public/Attributes.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Signature
{
/**
 * @brief Represents a RSA private key
 *
 * @deprecated Use DFL::Crypto::PrivateKey instead.
 *
 * @ingroup Crypto
 */
using RsaPrivateKey DFL_ATTRIBUTE_DEPRECATED(
    "Use DFL::Crypto::PrivateKey instead") = ::DFL::Crypto::PrivateKey;

/**
 * @brief Provides digital signatures of bytes using a RSA private key.
 *
 * @tparam Hash hash function like Sha256.
 *
 * @details
 * For details on digital signatures
 * see https://en.wikipedia.org/wiki/Digital_signature
 *
 * @deprecated Use DFL::Crypto::MessageDigest::Signature::Signature instead.
 *
 * @ingroup Crypto
 */
template <class Hash>
using RsaSignature DFL_ATTRIBUTE_DEPRECATED(
    "Use DFL::Crypto::MessageDigest::Signature::Signature instead") =
    Signature<Hash>;
}
}
}
}
