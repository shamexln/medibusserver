#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL::Crypto
{
/**
 * @brief Represents an arbitrary big integer number.
 *
 * It wraps an OpenSSL BIGNUM handle which can be constructed from a container
 * of bytes.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP BigNumber
{
public:
    /**
     * @brief Immutable type of underlying OpenSSL handle.
     */
    using Type = const BIGNUM*;
    /**
     * @brief Mutable type of underlying OpenSSL handle.
     */
    using MutableType = BIGNUM*;
    /**
     * @brief Constructs a big number from a container of bytes.
     *
     * @snippet Crypto/Test/UnitTest/TestBigNumber.cpp bytes
     * @snippet Crypto/Test/UnitTest/TestBigNumber.cpp fromBytes
     */
    [[nodiscard]] static BigNumber fromBytes(Encoding::BytesView bytes);
    /**
     * @brief Construct an empty big number.
     *
     * Empty meaning that it isn't a number at all. Not even 0. It is just an
     * empty shell. It does not allocate any resources and thus is cheap. It can
     * be used as a placeholder to be assigned later, e. g. initializing a
     * container of big numbers.
     *
     * @snippet Crypto/Test/UnitTest/TestBigNumber.cpp defaultCtor
     */
    BigNumber();
    /**
     * @brief Take ownership of the wrapped OpenSSL BIGNUM handle.
     */
    explicit BigNumber(OpenSsl::BignumPtr bnPtr);

    BigNumber(const BigNumber& other);
    BigNumber& operator=(const BigNumber& other);

    BigNumber(BigNumber&&) = default;
    BigNumber& operator=(BigNumber&&) = default;
    /**
     * @brief True if given big number equals this big number, otherwise false.
     */
    [[nodiscard]] bool equals(const BigNumber& other) const noexcept;
    /**
     * @brief Returns the wrapped OpenSSL BIGNUM handle.
     *
     * Returns nullptr if called on a default constructed instance.
     */
    [[nodiscard]] Type bignum() const;
    /**
     * @brief Releases the wrapped OpenSSL BIGNUM handle.
     *
     * The caller is now responsible for freeing the handle.
     *
     * @snippet Crypto/Test/UnitTest/TestBigNumber.cpp release
     */
    [[nodiscard]] MutableType release() noexcept;
    /**
     * @brief Swaps the wrapped OpenSSL BIGNUM handle.
     */
    void swap(BigNumber& other) noexcept;

private:
    OpenSsl::BignumPtr m_bn;
};
/**
 * @brief True if given big numbers are equal, otherwise false.
 *
 * @ingroup Crypto
 */
[[nodiscard]] DFL_CRYPTO_EXPIMP bool operator==(const BigNumber& a,
                                                const BigNumber& b) noexcept;
/**
 * @brief True if given big numbers are not equal, otherwise false.
 *
 * @ingroup Crypto
 */
[[nodiscard]] DFL_CRYPTO_EXPIMP bool operator!=(const BigNumber& a,
                                                const BigNumber& b) noexcept;
/**
 * @brief Swaps the wrapped OpenSSL BIGNUM handle.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(BigNumber& a, BigNumber& b) noexcept;
}
