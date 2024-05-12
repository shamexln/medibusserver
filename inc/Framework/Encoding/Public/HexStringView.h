#pragma once

#include <Framework/Encoding/Private/ExpImp.h>
#include <Framework/Encoding/Private/HexString.h>

#include <boost/numeric/conversion/cast.hpp>

#include <iterator>
#include <memory>
#include <string>
#include <type_traits>

namespace DFL
{
namespace Encoding
{
class HexString;
/**
 * @brief Models an STL container which refers to a constant contiguous sequence
 * of hexadecimal characters.
 *
 * @details
 * Hexadecimal characters are: 0-9, a-f, A-F.
 *
 * @note
 * This class is a non-owning container, i. e. an object of this class holds a
 * pointer to a source object. In order to prevent a dangling pointer,
 * the source object has to live longer than the view object.
 *
 * @ingroup Encoding
 */
class DFL_ENCODING_EXPIMP HexStringView
{
public:
    /**
     * @name Container specific types
     * @{
     */
    using value_type = char;
    using const_pointer = const value_type*;
    using pointer = value_type*;
    using const_reference = const value_type&;
    using reference = value_type&;
    using const_iterator = const_pointer;
    using iterator = pointer;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    /** @} */

    /**
     * @brief
     * Creates an empty hex string view with data()==nullptr and size()==0.
     *
     * @snippet Encoding/Test/UnitTest/TestHexStringView.cpp defaultCtor
     */
    HexStringView() = default;
    /**
     * @brief Creates a hex string view from the given data and size.
     *
     * @throw std::runtime_error
     * if data contains non-hexadecimal characters.
     *
     * @snippet Encoding/Test/UnitTest/TestHexStringView.cpp dataSizeCtor
     */
    explicit HexStringView(const char* data, size_t size);
    /**
     * @brief Creates a hex string view from the given cstr.
     *
     * @throw std::runtime_error
     * if cstr contains non-hexadecimal characters.
     *
     * @snippet Encoding/Test/UnitTest/TestHexStringView.cpp cstrCtor
     */
    explicit HexStringView(const char* cstr);
    /**
     * @brief Creates a hex string view from the given str.
     *
     * @throw std::runtime_error
     * if  contains non-hexadecimal characters.
     *
     * @snippet Encoding/Test/UnitTest/TestHexStringView.cpp strCtor
     */
    explicit HexStringView(const std::string& str);
    /**
     * @brief Creates a hex string view from the given hexString.
     *
     * @snippet Encoding/Test/UnitTest/TestHexStringView.cpp hexStrCtor
     */
    /*implicit*/ HexStringView(const HexString& hexString);
    /**
     * @brief Creates a hex string view from the range [first, last).
     *
     * @tparam ContigIt
     * Must satisfy contiguous_iterator concept, otherwise undefined behavior.
     *
     * @snippet Encoding/Test/UnitTest/TestHexStringView.cpp iterCtor
     *
     * @throw boost::bad_numeric_cast if last < first
     */
    template <class ContigIt>
    HexStringView(ContigIt first, ContigIt last);
    /**
     * @brief Returns a constant pointer to the first hexadecimal character.
     */
    const_pointer data() const noexcept;
    /**
     * @brief Returns the number of hexadecimal characters.
     */
    size_type size() const noexcept;
    /**
     * @brief Returns the maximum number of bytes.
     */
    size_type max_size() const noexcept;
    /**
     * @brief Returns true if the hex string view is empty.
     */
    bool empty() const noexcept;
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
     * Calling front on an empty hex string view results in undefined behavior.
     */
    const_reference front() const;
    /**
     * @brief Returns a constant reference to the last hexadecimal character.
     *
     * @details
     * Calling back on an empty hex string view results in undefined behavior.
     */
    const_reference back() const;
    /**
     * @brief Returns a constant iterator to the first hexadecimal character.
     */
    const_iterator begin() const noexcept;
    /**
     * @brief
     * Returns a constant iterator to the hexadecimal character following the
     * last hexadecimal character.
     *
     * @details
     * This hexadecimal character acts as a placeholder, attempting to access it
     * results in undefined behavior.
     */
    const_iterator end() const noexcept;
    /**
     * @brief Returns a constant iterator to the first hexadecimal character.
     */
    const_iterator cbegin() const noexcept;
    /**
     * @brief
     * Returns a constant iterator to the hexadecimal character following the
     * last hexadecimal character.
     *
     * @details
     * This hexadecimal character acts as a placeholder, attempting to access it
     * results in undefined behavior.
     */
    const_iterator cend() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the first hexadecimal character of
     * the reversed hex string view.
     *
     * @details
     * It corresponds to the last hexadecimal character of the non-reversed
     * string.
     */
    const_reverse_iterator rbegin() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the character following the last
     * hexadecimal character of the reversed hex string view.
     *
     * @details
     * It corresponds to the character preceding the first hexadecimal character
     * of the non-reversed hex string view. This hexadecimal character acts as a
     * placeholder, attempting to access it results in undefined behavior.
     */
    const_reverse_iterator rend() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the first hexadecimal character of
     * the reversed hex string view.
     *
     * @details
     * It corresponds to the last hexadecimal character of the non-reversed
     * string.
     */
    const_reverse_iterator crbegin() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the character following the last
     * hexadecimal character of the reversed hex string view.
     *
     * @details
     * It corresponds to the character preceding the first hexadecimal character
     * of the non-reversed hex string view. This hexadecimal character acts as a
     * placeholder, attempting to access it results in undefined behavior.
     */
    const_reverse_iterator crend() const noexcept;
    /**
     * @brief Exchanges the contents of hex string view with those of other.
     */
    void swap(HexStringView& other) noexcept;

private:
    const_pointer m_data{nullptr};
    size_type m_size{};
};
template <class ContigIt>
inline HexStringView::HexStringView(ContigIt first, ContigIt last)
    // it might not be possible to dereference an iterator on an empty range,
    // e.g. dereferencing begin on an empty string with debug builds, hence the
    // range check
    : m_data{(first == last) ? nullptr : std::addressof(*first)}
    , m_size{boost::numeric_cast<size_type>(std::distance(first, last))}
{
    // use contiguous_iterator concept:
    // https://en.cppreference.com/w/cpp/iterator/contiguous_iterator
    // once C++20 is available
    static_assert(
        std::is_base_of<
            std::random_access_iterator_tag,
            typename std::iterator_traits<ContigIt>::iterator_category>::value,
        "iterator has to refer to a contiguous sequence e.g. std::array, "
        "std::vector");
    Impl::ensureHexString(m_data, m_size);
}
/**
 * @brief Compares two hex string views case-insensitive.
 * @ingroup Encoding
 * @{
 */
DFL_ENCODING_EXPIMP bool operator==(const HexStringView& lhs,
                                    const HexStringView& rhs) noexcept;
DFL_ENCODING_EXPIMP bool operator!=(const HexStringView& lhs,
                                    const HexStringView& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given hex string views.
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP void swap(HexStringView& a, HexStringView& b) noexcept;
}
}
