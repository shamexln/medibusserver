#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Oid.h>

#include <initializer_list>
#include <iterator>
#include <vector>

namespace DFL
{
/**
 * @brief Container to hold several @ref DFL::Oid
 *
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Oids
{
private:
    using underlying_type = std::vector<Oid>;

public:
    /**
     * @name Container specific types
     * @{
     */
    using value_type = underlying_type::value_type;
    using const_pointer = underlying_type::const_pointer;
    using pointer = underlying_type::pointer;
    using const_reference = underlying_type::const_reference;
    using reference = underlying_type::reference;
    using const_iterator = underlying_type::const_iterator;
    using iterator = underlying_type::iterator;
    using const_reverse_iterator = underlying_type::const_reverse_iterator;
    using reverse_iterator = underlying_type::reverse_iterator;
    using difference_type = underlying_type::difference_type;
    using size_type = underlying_type::size_type;
    /** @} */
    /**
     * @brief Constructs an empty Oid container.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp DefaultCtor
     */
    Oids() = default;
    /**
     * @brief Constructs Oids from a list of Oids.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp InitlistCtor
     */
    explicit Oids(const std::initializer_list<Oid>& oids);
    /**
     * @brief Constructs Oids from an existing container of Oids.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp ContainerCtor
     */
    template <class Container>
    explicit Oids(const Container& oids);
    /**
     * @brief Constructs Oids from the range [first, last).
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp IterCtor
     */
    template <class InputIt>
    explicit Oids(InputIt first, InputIt last);
    /**
     * @brief Adds an Oid at the end of the container.
     * @param oid @ref DFL::Oid to be added.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp push_back
     */
    void push_back(const Oid& oid);
    /**
     * @brief Checks whether an oid is present in the container.
     * @param oid @ref DFL::Oid to be checked.
     * @returns true if oid is found else false.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp find
     */
    bool find(const Oid& oid) const;
    /**
     * @brief Clears all entries. Object is empty afterwards.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp clear
     */
    void clear();
    /**
     * @brief True if Oids is empty otherwise false.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp empty
     */
    bool empty() const noexcept;
    /**
     * @brief Compares given oid container with this container.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp cmp
     */
    bool equals(const Oids& other) const noexcept;
    /**
     * @brief Number of items in the container.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp push_back
     */
    size_type size() const noexcept;
    /**
     * @brief Maximum number of items in the container.
     */
    size_type max_size() const noexcept;
    /**
     * @brief Begin of the held data.
     */
    iterator begin() noexcept;
    /**
     * @brief End of the held data.
     */
    iterator end() noexcept;
    /**
     * @brief Begin of the held data.
     */
    const_iterator begin() const noexcept;
    /**
     * @brief End of the held data.
     */
    const_iterator end() const noexcept;
    /**
     * @brief Begin of the held data.
     */
    const_iterator cbegin() const noexcept;
    /**
     * @brief End of the held data.
     */
    const_iterator cend() const noexcept;
    /**
     * @brief Exchanges the contents of the oid container with those of other.
     */
    void swap(Oids& other) noexcept;
    /**
     * @brief Returns a comma separated string representation of oids.
     *
     * @snippet Utils/Test/UnitTest/TestOids.cpp toCommaSeparated
     */
    static std::string toCommaSeparated(const Oids& oids);

private:
    underlying_type m_oids{};
};
template <class Container>
inline Oids::Oids(const Container& oids)
    : m_oids{std::begin(oids), std::end(oids)}
{
}
template <class InputIt>
inline Oids::Oids(InputIt first, InputIt last)
    : m_oids{first, last}
{
}
/**
 * @brief Compares two Oid containers.
 * Two Oids are equal if they contain the same oids in the same order.
 *
 * @snippet Utils/Test/UnitTest/TestOids.cpp cmp
 *
 * @ingroup Utils
 * @{
 */
DFL_UTILS_EXPIMP bool operator==(const Oids& lhs, const Oids& rhs) noexcept;
DFL_UTILS_EXPIMP bool operator!=(const Oids& lhs, const Oids& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the contents of the given oid containers.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP void swap(Oids& a, Oids& b) noexcept;
}
