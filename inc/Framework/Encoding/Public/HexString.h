#pragma once

#include <Framework/Encoding/Private/ExpImp.h>
#include <Framework/Encoding/Private/HexString.h>

#include <Framework/Utils/Public/ConstContainer.h>

#include <string>

namespace DFL
{
namespace Encoding
{
/**
 * @brief Models an STL container holding a constant contiguous sequence of
 * hexadecimal characters.
 *
 * @details
 * Hexadecimal characters are: 0-9, a-f, A-F.
 *
 * @snippet Encoding/Test/UnitTest/TestHexString.cpp defaultCtor
 *
 * @ingroup Encoding
 */
class DFL_ENCODING_EXPIMP HexString : public Utils::ConstContainer<std::string>
{
public:
    /**
     * @name Container specific types
     * @{
     */
    using const_pointer = underlying_type::const_pointer;
    using pointer = underlying_type::const_pointer;
    using const_reverse_iterator = underlying_type::const_reverse_iterator;
    using reverse_iterator = underlying_type::const_reverse_iterator;
    /** @} */

    /**
     * @brief Creates an empty hex string.
     *
     * @snippet Encoding/Test/UnitTest/TestHexString.cpp defaultCtor
     */
    HexString() = default;
    /**
     * @brief Creates a hex string from the given str.
     *
     * @throw std::runtime_error
     * if str contains non-hexadecimal characters.
     *
     * @snippet Encoding/Test/UnitTest/TestHexString.cpp strCtor
     */
    explicit HexString(const std::string& str);
    /**
     * @brief Creates a hex string from the range [first, last).
     *
     * @snippet Encoding/Test/UnitTest/TestHexString.cpp iterCtor
     */
    template <class InputIt>
    explicit HexString(InputIt first, InputIt last);
    /**
     * @brief Returns a constant pointer to the first hexadecimal character.
     */
    const_pointer data() const noexcept;
    /**
     * @brief Returns a constant reference to the idx-th hexadecimal character.
     *
     * @details The behavior is undefined if idx is out of range.
     */
    const_reference operator[](size_type idx) const noexcept;
    /**
     * @brief Returns a constant reference to the first hexadecimal character.
     *
     * @details
     * Calling front on an empty hex string results in undefined behavior.
     */
    const_reference front() const;
    /**
     * @brief Returns a constant reference to the last hexadecimal character.
     *
     * @details
     * Calling back on an empty hex string results in undefined behavior.
     */
    const_reference back() const;
    /**
     * @brief
     * Returns a constant reverse iterator to the first hexadecimal character of
     * the reversed hex string.
     *
     * @details
     * It corresponds to the last hexadecimal character of the non-reversed
     * string.
     */
    const_reverse_iterator rbegin() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the character following the last
     * hexadecimal character of the reversed hex string.
     *
     * @details
     * It corresponds to the character preceding the first hexadecimal character
     * of the non-reversed hex string. This hexadecimal character acts as a
     * placeholder, attempting to access it results in undefined behavior.
     */
    const_reverse_iterator rend() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the first hexadecimal character of
     * the reversed hex string.
     *
     * @details
     * It corresponds to the last hexadecimal character of the non-reversed
     * string.
     */
    const_reverse_iterator crbegin() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the character following the last
     * hexadecimal character of the reversed hex string.
     *
     * @details
     * It corresponds to the character preceding the first hexadecimal character
     * of the non-reversed hex string. This hexadecimal character acts as a
     * placeholder, attempting to access it results in undefined behavior.
     */
    const_reverse_iterator crend() const noexcept;
};
template <class InputIt>
inline HexString::HexString(InputIt first, InputIt last)
    : Utils::ConstContainer<std::string>{first, last}
{
    Impl::ensureHexString(underlying().data(), underlying().size());
}

/**
 * @brief Compares two hex string case-insensitive.
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP bool operator==(const HexString& lhs,
                                    const HexString& rhs) noexcept;
/**
 * @brief Compares two hex string case-insensitive.
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP bool operator!=(const HexString& lhs,
                                    const HexString& rhs) noexcept;
}
}
