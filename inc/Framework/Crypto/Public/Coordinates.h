#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/BigNumber.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL::Crypto
{
/**
 * @brief Represents x and y coordinates.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Coordinates
{
public:
    /**
     * @brief Creates coordinates with an empty x and y.
     *
     * @snippet Crypto/Test/UnitTest/TestCoordinates.cpp defaultCtor
     */
    Coordinates() = default;
    /**
     * @brief Creates coordinates from given x and y.
     *
     * @snippet Crypto/Test/UnitTest/TestCoordinates.cpp bytesCtor
     */
    Coordinates(BigNumber x, BigNumber y);
    /**
     * @brief Returns the x coordinates.
     */
    [[nodiscard]] const BigNumber& x() const;
    /**
     * @brief Returns the y coordinates.
     */
    [[nodiscard]] const BigNumber& y() const;
    /**
     * @brief Returns true if x and y coordinates are equal, otherwise false.
     */
    [[nodiscard]] bool equals(const Coordinates& other) const noexcept;
    /**
     * @brief Swaps x and y coordinates between this and other.
     */
    void swap(Coordinates& other) noexcept;

private:
    BigNumber m_x{};
    BigNumber m_y{};
};
/**
 * @brief Returns true if x and y coordinates are equal, otherwise false.
 *
 * @ingroup Crypto
 */
[[nodiscard]] DFL_CRYPTO_EXPIMP bool operator==(const Coordinates& a,
                                                const Coordinates& b) noexcept;
/**
 * @brief Returns true if x and y coordinates are unequal, otherwise false.
 *
 * @ingroup Crypto
 */
[[nodiscard]] DFL_CRYPTO_EXPIMP bool operator!=(const Coordinates& a,
                                                const Coordinates& b) noexcept;
/**
 * @brief Swaps x and y coordinates between a and b.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(Coordinates& a, Coordinates& b) noexcept;
/**
 * @brief Makes Coordinates useable with structure bindings.
 *
 * @snippet Crypto/Test/UnitTest/TestCoordinates.cpp structbind
 *
 * @ingroup Crypto
 */
template <int I>
inline const auto& get(const Coordinates& a)
{
    if constexpr (I == 0)
    {
        return a.x();
    }
    else if constexpr (I == 1)
    {
        return a.y();
    }
}
}
namespace std
{
template <>
struct tuple_size<::DFL::Crypto::Coordinates>
    : std::integral_constant<size_t, 2>
{
};
template <>
struct tuple_element<0, ::DFL::Crypto::Coordinates>
{
    using type = ::DFL::Crypto::BigNumber;
};
template <>
struct tuple_element<1, ::DFL::Crypto::Coordinates>
{
    using type = ::DFL::Crypto::BigNumber;
};
}
