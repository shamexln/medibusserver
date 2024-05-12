#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/StaticAssert.h>

#include <Framework/Format/Public/Stream.h>

#include <boost/array.hpp>
#include <boost/config.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <algorithm>
#include <exception>
#include <iterator>

namespace DFL
{
/**
 * @brief An immutable, owning STL compliant container for holding bytes.
 *
 * Being an owning container means that all data given to this
 * buffer in the ctor is copied into the internal storage of this class.
 * Immutable means that once a buffer is constructed you cannot change
 * any values it holds. This class is espacially useful when dealing with
 * c-array APIs. It provides a smooth transition between c++-containers and
 * c-arrays. Thus this container can be constructed in various different ways.
 * From c-array, stl-containers, iterator-ranges, ...
 * @snippet Utils/Test/UnitTest/TestBuffer.cpp Data
 * @snippet Utils/Test/UnitTest/TestBuffer.cpp Construction
 * A size missmatch is either detected at compile time ...
 * @snippet Utils/Test/UnitTest/TestBuffer.cpp CompileCheck
 * ... or at runtime
 * @snippet Utils/Test/UnitTest/TestBuffer.cpp SizeMismatch
 * Another compile time check ensures that the type held by
 * the source container is one byte.
 * During construction the data from the source container
 * is copied into the internal storage of the buffer class.
 * Afterwards the data can no longer be modified.
 * Iterators are provided for retrieving the values.
 * And for iterfacing with c-array a pointer to the held data
 * and a size accessor are provided.
 *
 * @tparam bytes Number of bytes this buffer can hold.
 *
 * @ingroup Utils
 */
template <std::size_t bytes>
class Buffer
{
    DFL_STATIC_ASSERT_MSG(bytes > 0,
                          "number of bytes has to be greater than 0");

public:
    /**
     * @brief Type of the internal storage.
     */
    using Data = boost::array<unsigned char, bytes>;
    /**
     * @name Container specific types
     * @{
     */
    using value_type = typename Data::value_type;
    using const_reference = typename Data::const_reference;
    using reference = typename Data::reference;
    using const_pointer = const value_type*;
    using pointer = value_type*;
    using const_iterator = typename Data::const_iterator;
    using iterator = typename Data::iterator;
    using const_reverse_iterator = typename Data::const_reverse_iterator;
    using reverse_iterator = typename Data::reverse_iterator;
    using difference_type = typename Data::difference_type;
    using size_type = typename Data::size_type;
    /** @} */
    /**
     * @brief Constructs empty buffer.
     */
    Buffer() = default;
    /**
     * @brief Constructs buffer from an array-like data type.
     */
    constexpr explicit Buffer(const Data& d) noexcept;
    /**
     * @brief Constructs buffer from a pointer and a size.
     */
    template <class PointerType>
    Buffer(PointerType p,
           std::size_t sourceSize,
           typename boost::enable_if<boost::is_pointer<PointerType>>::type*
               dummy = nullptr);
    /**
     * @brief Constructs buffer from a container using begin and end on it.
     */
    template <class Container>
    explicit Buffer(const Container& c);
    /**
     * @brief Constructs buffer from given input-iterator range.
     */
    template <class InputIter>
    Buffer(InputIter b, InputIter e);
    /**
     * @brief True if empty otherwise false.
     */
    constexpr bool empty() const noexcept;
    /**
     * @brief Returns number of bytes held by this buffer.
     */
    constexpr size_type size() const noexcept;
    /**
     * @brief Returns maximum number of bytes held by this buffer.
     */
    constexpr size_type max_size() const noexcept;
    /**
     * @brief Gives access to the c-like array held by this buffer.
     *
     * @note Since many c-APIs are not that const correct it might be
     * neccessary to cast away the constness of the returned pointer.
     * But only if this buffer is used to provide input data to the
     * c-API.
     */
    constexpr const_pointer data() const noexcept;
    /**
     * @brief True if two buffers are equal otherwise false.
     */
    constexpr bool equals(const Buffer& other) const noexcept;
    /**
     * @brief Begin of the held data.
     */
    constexpr const_iterator begin() const noexcept;
    /**
     * @brief End of the held data.
     */
    constexpr const_iterator end() const noexcept;
    /**
     * @brief Begin of the held data.
     */
    constexpr const_iterator cbegin() const noexcept;
    /**
     * @brief End of the held data.
     */
    constexpr const_iterator cend() const noexcept;
    /**
     * @brief Reversed begin of the held data.
     */
    constexpr const_reverse_iterator rbegin() const noexcept;
    /**
     * @brief Reversed end of the held data.
     */
    constexpr const_reverse_iterator rend() const noexcept;
    /**
     * @brief Reversed begin of the held data.
     */
    constexpr const_reverse_iterator crbegin() const noexcept;
    /**
     * @brief Reversed end of the held data.
     */
    constexpr const_reverse_iterator crend() const noexcept;
    /**
     * @brief Exchanges the contents of the buffer with those of other.
     */
    void swap(Buffer& other) noexcept;

private:
    static void throwOnSizeMissmatch(std::size_t sourceSize,
                                     std::size_t targetSize);
    Data m_data{};
};
/**
 * @brief True if two buffers are equal otherwise false.
 * @ingroup Utils
 */
template <std::size_t bytes>
constexpr bool operator==(const Buffer<bytes>& a,
                                const Buffer<bytes>& b) noexcept;
/**
 * @brief True if two buffers are not equal otherwise false.
 * @ingroup Utils
 */
template <std::size_t bytes>
constexpr bool operator!=(const Buffer<bytes>& a,
                                const Buffer<bytes>& b) noexcept;
/**
 * @brief Exchanges the contents of the given buffer.
 * @ingroup Utils
 */
template <std::size_t bytes>
void swap(Buffer<bytes>& a, Buffer<bytes>& b) noexcept;
}

namespace DFL
{
template <std::size_t bytes>
inline void Buffer<bytes>::throwOnSizeMissmatch(std::size_t sourceSize,
                                                std::size_t targetSize)
{
    if (sourceSize != targetSize)
    {
        ::DFL::Format::Stream str;
        str << "size of source buffer " << sourceSize
            << " has to match size of target buffer " << targetSize;
        throw std::runtime_error(str.cStr());
    }
}
template <std::size_t bytes>
inline constexpr Buffer<bytes>::Buffer(const Data& d) noexcept
    : m_data(d)
{
}
template <std::size_t bytes>
template <class PointerType>
Buffer<bytes>::Buffer(
    const PointerType p,
    std::size_t sourceSize,
    typename boost::enable_if<boost::is_pointer<PointerType>>::type*)
    : m_data()
{
    DFL_STATIC_ASSERT_MSG(sizeof(*p) == sizeof(value_type),
                          "size of value types does not match");

    throwOnSizeMissmatch(sourceSize, this->size());

    std::copy(p, p + sourceSize, m_data.begin());
}
template <std::size_t bytes>
template <class Container>
inline Buffer<bytes>::Buffer(const Container& c)
    : m_data()
{
    DFL_STATIC_ASSERT_MSG(sizeof(typename Container::value_type) ==
                              sizeof(value_type),
                          "size of value types do not match");

    throwOnSizeMissmatch(std::distance(c.begin(), c.end()), this->size());

    std::copy(c.begin(), c.end(), m_data.begin());
}
template <std::size_t bytes>
template <class InputIter>
inline Buffer<bytes>::Buffer(InputIter b, InputIter e)
    : m_data()
{
    DFL_STATIC_ASSERT_MSG(
        sizeof(typename std::iterator_traits<InputIter>::value_type) ==
            sizeof(value_type),
        "size of value types do not match");

    throwOnSizeMissmatch(std::distance(b, e), this->size());

    std::copy(b, e, m_data.begin());
}
template <std::size_t bytes>
inline constexpr bool Buffer<bytes>::empty() const noexcept
{
    return m_data.empty();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::size_type Buffer<bytes>::size()
    const noexcept
{
    return m_data.size();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::size_type Buffer<
    bytes>::max_size() const noexcept
{
    return m_data.max_size();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_pointer Buffer<
    bytes>::data() const noexcept
{
    return m_data.data();
}
template <std::size_t bytes>
inline constexpr bool Buffer<bytes>::equals(
    const Buffer& other) const noexcept
{
    return m_data == other.m_data;
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_iterator Buffer<
    bytes>::begin() const noexcept
{
    return m_data.begin();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_iterator Buffer<
    bytes>::end() const noexcept
{
    return m_data.end();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_iterator Buffer<
    bytes>::cbegin() const noexcept
{
    return m_data.cbegin();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_iterator Buffer<
    bytes>::cend() const noexcept
{
    return m_data.cend();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_reverse_iterator Buffer<
    bytes>::rbegin() const noexcept
{
    return m_data.rbegin();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_reverse_iterator Buffer<
    bytes>::rend() const noexcept
{
    return m_data.rend();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_reverse_iterator Buffer<
    bytes>::crbegin() const noexcept
{
    return m_data.crbegin();
}
template <std::size_t bytes>
inline constexpr typename Buffer<bytes>::const_reverse_iterator Buffer<
    bytes>::crend() const noexcept
{
    return m_data.crend();
}
template <std::size_t bytes>
inline void Buffer<bytes>::swap(Buffer<bytes>& other) noexcept
{
    m_data.swap(other.m_data);
}
template <std::size_t bytes>
inline constexpr bool operator==(const Buffer<bytes>& a,
                                       const Buffer<bytes>& b) noexcept
{
    return a.equals(b);
}
template <std::size_t bytes>
inline constexpr bool operator!=(const Buffer<bytes>& a,
                                       const Buffer<bytes>& b) noexcept
{
    return !(a == b);
}
template <std::size_t bytes>
inline void swap(Buffer<bytes>& a, Buffer<bytes>& b) noexcept
{
    a.swap(b);
}
}
