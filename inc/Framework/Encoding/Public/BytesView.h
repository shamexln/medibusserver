#pragma once

#include <Framework/Encoding/Private/ExpImp.h>
#include <Framework/Encoding/Public/Byte.h>
#include <Framework/Encoding/Public/Bytes.h>

#include <iterator>
#include <memory>
#include <string>
#include <string_view>

namespace DFL::Encoding
{
/**
 * @brief Models an STL container which refers to a contiguous sequence
 * of constant raw bytes.
 *
 * @note
 * This class is a non-owning container, i. e. an object of this class holds a
 * pointer to a source object. In order to prevent a dangling pointer,
 * the source object has to live longer than the view object.
 *
 * @ingroup Encoding
 */
class DFL_ENCODING_EXPIMP BytesView
{
public:
    /**
     * @name Container specific types
     * @{
     */
    using value_type = Byte;
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
     * @brief Creates an empty bytes view with data()==nullptr and size()==0.
     *
     * @snippet Encoding/Test/UnitTest/TestBytesView.cpp defaultCtor
     */
    BytesView() = default;
    /**
     * @brief Creates a bytes view with the given data and size.
     *
     * @snippet Encoding/Test/UnitTest/TestBytesView.cpp dataSizeCtor
     */
    explicit BytesView(const_pointer data, size_type size);
    /**
     * @brief Creates a bytes view with the given data and size.
     *
     * @snippet Encoding/Test/UnitTest/TestBytesView.cpp charDataSizeCtor
     */
    explicit BytesView(const char* data, size_type size);
    /**
     * @brief Creates a bytes view from the given string view.
     *
     * @snippet Encoding/Test/UnitTest/TestBytesView.cpp stringViewCtor
     */
    /*implicit*/ BytesView(std::string_view str);
    /**
     * @brief Creates a bytes view from the given cstr.
     *
     * @details
     * The given string will be reinterpreted as bytes without conversion.
     *
     * @snippet Encoding/Test/UnitTest/TestBytesView.cpp cstrCtor
     */
    /*implicit*/ BytesView(const char* cstr);
    /**
     * @brief Creates a bytes view from the given str.
     *
     * @details
     * The given string will be reinterpreted as bytes without conversion.
     *
     * @snippet Encoding/Test/UnitTest/TestBytesView.cpp strCtor
     */
    /*implicit*/ BytesView(const std::string& str);
    /**
     * @brief Creates a bytes view from the given bytes.
     *
     * @snippet Encoding/Test/UnitTest/TestBytesView.cpp bytesCtor
     */
    /*implicit*/ BytesView(const Bytes& bytes);
    /**
     * @brief Returns a constant pointer to the first byte.
     */
    const_pointer data() const noexcept;
    /**
     * @brief Returns the number of bytes.
     */
    size_type size() const noexcept;
    /**
     * @brief Returns the maximum number of bytes.
     */
    size_type max_size() const noexcept;
    /**
     * @brief Returns true if the bytes view is empty.
     */
    bool empty() const noexcept;
    /**
     * @brief Returns a constant reference to the idx-th byte.
     *
     * @details The behavior is undefined if idx is out of range.
     */
    const_reference operator[](size_type idx) const noexcept;
    /**
     * @brief Returns a constant reference to the first byte.
     *
     * @details
     * Calling front on an empty bytes view results in undefined behavior.
     */
    const_reference front() const;
    /**
     * @brief Returns a constant reference to the last byte.
     *
     * @details
     * Calling back on an empty bytes view results in undefined behavior.
     */
    const_reference back() const;
    /**
     * @brief Returns a constant iterator to the first byte.
     */
    const_iterator begin() const noexcept;
    /**
     * @brief
     * Returns a constant iterator to the byte following the
     * last byte.
     *
     * @details
     * This byte acts as a placeholder, attempting to access it
     * results in undefined behavior.
     */
    const_iterator end() const noexcept;
    /**
     * @brief Returns a constant iterator to the first byte.
     */
    const_iterator cbegin() const noexcept;
    /**
     * @brief
     * Returns a constant iterator to the byte following the
     * last byte.
     *
     * @details
     * This byte acts as a placeholder, attempting to access it
     * results in undefined behavior.
     */
    const_iterator cend() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the first byte of
     * the reversed bytes view.
     *
     * @details
     * It corresponds to the last byte of the non-reversed
     * view.
     */
    const_reverse_iterator rbegin() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the byte following the last
     * byte of the reversed bytes view.
     *
     * @details
     * It corresponds to the byte preceding the first byte
     * of the non-reversed bytes view. This byte acts as a
     * placeholder, attempting to access it results in undefined behavior.
     */
    const_reverse_iterator rend() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the first byte of
     * the reversed bytes view.
     *
     * @details
     * It corresponds to the last byte of the non-reversed
     * view.
     */
    const_reverse_iterator crbegin() const noexcept;
    /**
     * @brief
     * Returns a constant reverse iterator to the byte following the last
     * byte of the reversed bytes view.
     *
     * @details
     * It corresponds to the byte preceding the first byte
     * of the non-reversed bytes view. This byte acts as a
     * placeholder, attempting to access it results in undefined behavior.
     */
    const_reverse_iterator crend() const noexcept;
    /**
     * @brief Exchanges the contents of bytes view with those of other.
     */
    void swap(BytesView& other) noexcept;

private:
    const_pointer m_data{nullptr};
    size_type m_size{};
};
/**
 * @brief Compares the content of two byte views.
 * @ingroup Encoding
 * @{
 */
DFL_ENCODING_EXPIMP bool operator==(const BytesView& lhs,
                                    const BytesView& rhs) noexcept;
DFL_ENCODING_EXPIMP bool operator!=(const BytesView& lhs,
                                    const BytesView& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given bytes views.
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP void swap(BytesView& a, BytesView& b) noexcept;
}
