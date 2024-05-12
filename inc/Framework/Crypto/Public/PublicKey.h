#pragma once

#include <Framework/Crypto/Private/EvpPkey.h>
#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/KeyType.h>

#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
class Coordinates;
class Certificate;
class Csr;
class DerFormat;
class PemString;
class PrivateKey;

/**
 * @brief Holds a public key
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP PublicKey
{
public:
    /**
     * @brief Type of underlying OpenSSL private key.
     */
    using Type = const ::EVP_PKEY*;
    /**
     * @brief Creates a prime256v1 elliptic curve public key from given x/y.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp createEcKey
     */
    static PublicKey createEcKey(Encoding::BytesView x, Encoding::BytesView y);
    /**
     * @brief Creates a prime256v1 elliptic curve public key from given
     * coordinates.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp createEcKeyCoord
     */
    static PublicKey createEcKey(const Coordinates& c);
    /**
     * @brief Creates an empty public key.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp defaultCtor
     */
    PublicKey() = default;
    /**
     * @brief Creates a public key from a PEM string.
     *
     * @details
     * Supported PEM formats:
     * - PKCS #1 for RSA keys
     * - PKCS #8 for all keys
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp pemCtor
     */
    explicit PublicKey(const PemString& pem);
    /**
     * @brief Creates a public key from DER data.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp derCtor
     */
    explicit PublicKey(const DerFormat& der);
    /**
     * @brief Returns the public key from a certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp certCtor
     */
    explicit PublicKey(const Certificate& cert);
    /**
     * @brief Returns the public key from a CSR.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp csrCtor
     */
    explicit PublicKey(const Csr& csr);
    /**
     * @brief Returns the public key from a private key.
     *
     * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp privKeyCtor
     */
    explicit PublicKey(const PrivateKey& privateKey);
    /**
     * @brief Returns the type of the used algorithm, e.g. RSA.
     */
    KeyType type() const noexcept;
    /**
     * @brief Returns the underlying OpenSSL private key.
     */
    Type publicKey() const;
    /**
     * @brief Returns true if other is equal to *this, otherwise false.
     */
    bool equals(const PublicKey& other) const noexcept;
    /**
     * @brief Exchanges the contents of the public key with those of other.
     */
    void swap(PublicKey& other) noexcept;

private:
    explicit PublicKey(Impl::EvpPkey pkey);

    Impl::EvpPkey m_pkey{};
};

/**
 * @brief Compares two public keys.
 *
 * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp equalityComparable
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const PublicKey& lhs,
                                  const PublicKey& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const PublicKey& lhs,
                                  const PublicKey& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given public keys.
 *
 * @snippet Crypto/Test/UnitTest/TestPublicKey.cpp swap
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(PublicKey& a, PublicKey& b) noexcept;
}
}
