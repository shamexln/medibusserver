#pragma once

#include <initializer_list>
#include <iterator>
#include <utility>

namespace DFL
{
namespace Utils
{
/**
 * @brief
 * Constant container which meets the C++ named requirement Container.
 *
 * @details
 * This class shall support customer in writing container-like types.
 * In contrast to the STL containers, it is designed to be used as base class:
 *
 * @snippet Utils/Test/UnitTest/TestIsContainer.cpp GoodContainerType
 *
 * For details on the C++ named requirement Container,
 * see <https://en.cppreference.com/w/cpp/named_req/Container>.
 *
 * @ingroup Utils
 */
template <class Container>
class ConstContainer
{
public:
    /**
     * @name Container specific types
     * @{
     */
    using value_type = typename Container::value_type;
    using const_reference = typename Container::const_reference;
    using reference = typename Container::reference;
    using const_iterator = typename Container::const_iterator;
    using iterator = typename Container::iterator;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;
    /** @} */
    /**
     * @brief Constructs an empty container.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp defaultCtor
     */
    ConstContainer() = default;
    /**
     * @brief
     * Constructs the container with the contents of the initializer list init.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp initListCtor
     */
    explicit ConstContainer(const std::initializer_list<value_type>& init)
        : m_underlying{init.begin(), init.end()}
    {
    }
    /**
     * @brief Constructs the container with the contents of cont.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp containerCtor
     */
    explicit ConstContainer(Container cont)
        : m_underlying{std::move(cont)}
    {
    }
    /**
     * @brief Constructs the container with the contents of cont.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp otherContainerCtor
     */
    template <class OtherContainer>
    explicit ConstContainer(const OtherContainer& cont)
        : m_underlying{std::begin(cont), std::end(cont)}
    {
    }
    /**
     * @brief
     * Constructs the container with the contents of the range [first, last).
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp iterCtor
     */
    template <class InputIt>
    ConstContainer(InputIt first, InputIt last)
        : m_underlying{first, last}
    {
    }
    /**
     * @brief
     * Returns a constant iterator to the first element of the container.
     *
     * @details
     * If the container is empty, the returned iterator will be equal to end().
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp iterCtor
     */
    const_iterator begin() const noexcept
    {
        using std::begin;
        return begin(m_underlying);
    }
    /**
     * @brief
     * Returns a constant iterator to the element following the last element of
     * the container.
     *
     * @details
     * This element acts as a placeholder; attempting to access it results in
     * undefined behavior.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp iterCtor
     */
    const_iterator end() const noexcept
    {
        using std::end;
        return end(m_underlying);
    }
    /**
     * @brief
     * Returns a constant iterator to the first element of the container.
     *
     * @details
     * If the container is empty, the returned iterator will be equal to end().
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp iterCtor
     */
    const_iterator cbegin() const noexcept
    {
        return begin();
    }
    /**
     * @brief
     * Returns a constant iterator to the element following the last element of
     * the container.
     *
     * @details
     * This element acts as a placeholder; attempting to access it results in
     * undefined behavior.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp iterCtor
     */
    const_iterator cend() const noexcept
    {
        return end();
    }
    /**
     * @brief Exchanges the contents of the container with those of other.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp swappable
     */
    void swap(ConstContainer& other) noexcept
    {
        using std::swap;
        swap(m_underlying, other.m_underlying);
    }
    /**
     * @brief Returns the number of elements in the container.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp initListCtor
     */
    size_type size() const noexcept
    {
        return m_underlying.size();
    }
    /**
     * @brief
     * Returns the maximum number of elements the container is able to hold.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp initListCtor
     */
    size_type max_size() const noexcept
    {
        return m_underlying.max_size();
    }
    /**
     * @brief Returns true if the container is empty.
     *
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
     * @snippet Utils/Test/UnitTest/TestConstContainer.cpp initListCtor
     */
    bool empty() const noexcept
    {
        return m_underlying.empty();
    }

protected:
    /**
     * @brief Type of underlying container.
     */
    using underlying_type = Container;
    /**
     * @brief Returns underlying container.
     */
    const Container& underlying() const noexcept
    {
        return m_underlying;
    }

private:
    Container m_underlying{};
};

/**
 * @brief Compares the contents of two containers.
 *
 * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
 * @snippet Utils/Test/UnitTest/TestConstContainer.cpp equalityComparable
 *
 * @ingroup Utils
 * @{
 */
template <class Container>
inline bool operator==(const ConstContainer<Container>& lhs,
                       const ConstContainer<Container>& rhs) noexcept
{
    if (lhs.size() != rhs.size()) return false;
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}
template <class Container>
inline bool operator!=(const ConstContainer<Container>& lhs,
                       const ConstContainer<Container>& rhs) noexcept
{
    return !(lhs == rhs);
}
/** @} */
/**
 * @brief Exchanges the contents of the given containers.
 *
 * @ingroup Utils
 */
template <class Container>
inline void swap(ConstContainer<Container>& a,
                 ConstContainer<Container>& b) noexcept
{
    a.swap(b);
}
}
}
