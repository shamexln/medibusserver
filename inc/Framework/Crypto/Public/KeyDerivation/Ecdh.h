#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>

namespace DFL::Crypto
{
class PrivateKey;
class PublicKey;
}
namespace DFL::Crypto::KeyDerivation
{
/**
 * @brief Provides shared secret creation based on ECDH.
 *
 * @details
 * For details on Elliptic Curve Diffie Hellman (ECDH) see
 * https://en.wikipedia.org/wiki/Elliptic-curve_Diffie%E2%80%93Hellman.
 *
 * @warning
 * The shared secret should not be used directly as a symmetric key,
 * but it can be used as entropy for a key derivation function.
 *
 * @snippet Crypto/Test/UnitTest/KeyDerivation/TestEcdh.cpp ecdh
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Ecdh
{
public:
    /**
     * @brief Returns a shared secret from given keys.
     *
     * @details
     * privateKey and peerPublicKey must be of type EC.
     *
     * @throw std::runtime_error in case of an error.
     */
    Encoding::Bytes operator()(const PrivateKey& privateKey,
                               const PublicKey& peerPublicKey) const;
};
}
