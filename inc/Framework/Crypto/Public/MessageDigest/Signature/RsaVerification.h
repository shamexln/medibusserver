#pragma once

#include <Framework/Crypto/Public/MessageDigest/Signature/Verification.h>
#include <Framework/Crypto/Public/PublicKey.h>

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
 * @brief Represents a RSA public key
 *
 * @deprecated Use DFL::Crypto::PublicKey instead.
 *
 * @ingroup Crypto
 */
using RsaPublicKey DFL_ATTRIBUTE_DEPRECATED(
    "Use DFL::Crypto::PublicKey instead") = ::DFL::Crypto::PublicKey;

/**
 * @brief Verifies digital signatures using a RSA public key.
 *
 * @tparam Hash hash function like Sha256.
 *
 * @details
 * For details on digital signatures
 * see https://en.wikipedia.org/wiki/Digital_signature
 *
 * @deprecated Use DFL::Crypto::MessageDigest::Signature::Verification instead.
 *
 * @ingroup Crypto
 */
template <class Hash>
using RsaVerification DFL_ATTRIBUTE_DEPRECATED(
    "Use DFL::Crypto::MessageDigest::Signature::Verification instead") =
    Verification<Hash>;
}
}
}
}
