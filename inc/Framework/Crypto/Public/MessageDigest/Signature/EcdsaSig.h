#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/DerFormat.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL::Crypto
{
class BigNumber;
}
namespace DFL::Crypto::MessageDigest::Signature
{
/**
 * @brief Holds an ECDSA signature.
 *
 * @details
 * see https://en.wikipedia.org/wiki/Elliptic_Curve_Digital_Signature_Algorithm
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP EcdsaSig
{
public:
    /**
     * @brief Type of underlying OpenSSL ECDSA signature.
     */
    using Type = const ::ECDSA_SIG*;
    /**
     * @brief Create an empty ECDSA signature.
     *
     * @snippet Crypto/Test/UnitTest/MessageDigest/TestEcdsaSig.cpp defaultCtor
     */
    EcdsaSig() = default;
    /**
     * @brief Create an ECDSA signature from given DER data.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/MessageDigest/TestEcdsaSig.cpp derCtor
     */
    explicit EcdsaSig(const DerFormat& der);
    /**
     * @brief Create an ECDSA signature from given r and s.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/MessageDigest/TestEcdsaSig.cpp rsCtor
     */
    EcdsaSig(Encoding::BytesView r, Encoding::BytesView s);
    /**
     * @brief Create an ECDSA signature from given r and s.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/MessageDigest/TestEcdsaSig.cpp bnCtor
     */
    EcdsaSig(BigNumber r, BigNumber s);
    /**
     * @brief Copy constructor.
     */
    EcdsaSig(const EcdsaSig& other);
    /**
     * @brief Copy assignment operator.
     */
    EcdsaSig& operator=(const EcdsaSig& other);
    /**
     * @brief Move constructor.
     */
    EcdsaSig(EcdsaSig&&) = default;
    /**
     * @brief Move assignment operator.
     */
    EcdsaSig& operator=(EcdsaSig&&) = default;
    /**
     * @brief Exchanges the contents of attribute with those of other.
     */
    void swap(EcdsaSig& other) noexcept;
    /**
     * @brief Returns the r value of the ECDSA signature.
     */
    BigNumber r() const;
    /**
     * @brief Returns the s value of the ECDSA signature.
     */
    BigNumber s() const;
    /**
     * @brief Returns the underlying OpenSSL ECDSA signature.
     */
    Type ecdsaSig() const noexcept;

private:
    OpenSsl::EcdsaSigPtr m_sig{OpenSsl::EcdsaSigNullptr()};
};

/**
 * @brief Compares two ECDSA signatures.
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const EcdsaSig& lhs, const EcdsaSig& rhs);
DFL_CRYPTO_EXPIMP bool operator!=(const EcdsaSig& lhs, const EcdsaSig& rhs);
/** @} */
/**
 * @brief Exchanges the given ECDSA signatures.
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(EcdsaSig& a, EcdsaSig& b) noexcept;
}
