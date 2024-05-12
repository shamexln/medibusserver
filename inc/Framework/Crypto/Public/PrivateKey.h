#pragma once

#include <Framework/Crypto/Private/EvpPkey.h>
#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/KeyType.h>

#include <Framework/Config/Public/Attributes.h>

#include <cstddef>

namespace DFL
{
namespace Crypto
{
class DerFormat;
class PemString;

/**
 * @brief Holds a private key (which includes a public key)
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP PrivateKey
{
public:
    /**
     * @brief Type of underlying OpenSSL private key.
     */
    using Type = const ::EVP_PKEY*;

    /**
     * @brief Creates an empty private key.
     *
     * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp createEmptyKey
     */
    static PrivateKey createEmptyKey();
    /**
     * @brief Generates a RSA-2048 private key.
     *
     * @details
     * This method can be very expensive!
     * Identical to generateRsaKey().
     *
     * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp generateKey
     *
     * @deprecated Use generateRsaKey or generateEcKey instead.
     */
    DFL_ATTRIBUTE_DEPRECATED("Use generateRsaKey or generateEcKey instead")
    static PrivateKey generateKey();
    /**
     * @brief Generates a RSA-2048 private key.
     *
     * @details This method can be very expensive!
     *
     * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp generateRsaKey
     */
    static PrivateKey generateRsaKey();
    /**
     * @brief Generates a P-256 (Prime256v1) private key.
     *
     * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp generateEcKey
     */
    static PrivateKey generateEcKey();

    /**
     * @brief Creates an empty private key.
     *
     * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp defaultCtor
     */
    PrivateKey() = default;
    /**
     * @brief Creates a private key from the given PEM string.
     *
     * @details
     * Supported PEM formats: PKCS #1 and PKCS #8
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp pemCtor
     */
    explicit PrivateKey(const PemString& pem);
    /**
     * @brief Creates a private key from DER data.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp derCtor
     */
    explicit PrivateKey(const DerFormat& der);

    /**
     * @brief Returns size of key in bits.
     */
    std::size_t sizeInBits() const noexcept;

    /**
     * @brief Returns the type of the used algorithm, e.g. RSA.
     */
    KeyType type() const noexcept;

    /**
     * @brief Returns the underlying OpenSSL private key.
     */
    Type privateKey() const noexcept;
    /**
     * @brief Returns true if other is equal to *this, otherwise false.
     */
    bool equals(const PrivateKey& other) const noexcept;
    /**
     * @brief Exchanges the contents of the private key with those of other.
     */
    void swap(PrivateKey& other) noexcept;

private:
    explicit PrivateKey(Impl::EvpPkey pkey);

    Impl::EvpPkey m_pkey{};
};

/**
 * @brief Compares two private keys.
 *
 * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp equalityComparable
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const PrivateKey& lhs,
                                  const PrivateKey& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const PrivateKey& lhs,
                                  const PrivateKey& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given private keys.
 *
 * @snippet Crypto/Test/UnitTest/TestPrivateKey.cpp swap
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(PrivateKey& a, PrivateKey& b) noexcept;
}
}
