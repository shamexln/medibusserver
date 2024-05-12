#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Store/Table.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/TableItem.h>

#include <Framework/Utils/Public/Application/Identifier.h>
#include <Framework/Utils/Public/Oids.h>

#include <boost/optional/optional.hpp>

#include <string>
#include <vector>

namespace DFL::Component
{
class Key;
}
namespace DFL::Crypto
{
class DistinguishedName;
class PublicKey;
/**
 * @brief Holds an @ref DFL::Application::Identifier plus a container of
 * @ref DFL::Crypto::TableItem without duplicates.
 *
 * It provides an STL container compliant iterator API and
 * access to a specific item is given by using @ref DFL::Component::Key.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Table
{
    friend ::DFL::Crypto::Impl::TableAccess;

public:
    /**
     * @name Table specific types
     * @{
     */
    using Type = std::vector<TableItem>;
    using value_type = typename Type::value_type;
    using OptionalValueType = boost::optional<value_type>;
    using const_reference = typename Type::const_reference;
    using reference = typename Type::reference;
    using const_iterator = typename Type::const_iterator;
    using iterator = typename Type::iterator;
    using difference_type = typename Type::difference_type;
    using size_type = typename Type::size_type;
    /** @} */

    /**
     * @brief True if table is empty otherwise false.
     */
    bool empty() const noexcept;
    /**
     * @brief Number of items in table.
     */
    size_type size() const noexcept;
    /**
     * @brief Maximum number of items in table.
     */
    size_type max_size() const noexcept;
    /**
     * @brief Compares given table with this table.
     *
     * @see bool DFL::Crypto::operator==(const Table&, const Table&)
     */
    bool equals(const Table& other) const noexcept;
    /**
     * @brief Returns an iterator to the first element of the container.
     */
    const_iterator begin() const noexcept;
    /**
     * @brief Returns an iterator to the element following the last element of
     * the container.
     */
    const_iterator end() const noexcept;
    /**
     * @brief Returns an iterator to the first element of the container.
     */
    const_iterator cbegin() const noexcept;
    /**
     * @brief Returns an iterator to the element following the last element of
     * the container.
     */
    const_iterator cend() const noexcept;
    /**
     * @brief Tries to find the entry which contains given component key.
     *
     * Returns none if key could not be found.
     *
     * @snippet Crypto/Test/UnitTest/TestTable.cpp indexOp
     */
    OptionalValueType operator[](const Component::Key& compKey) const;
    /**
     * @brief Exchanges the contents of the table with those of other.
     */
    void swap(Table& other) noexcept;
    /**
     * @brief Provide the (previously set) identifier.
     */
    const Application::Identifier& applicationIdentifier() const noexcept;
    /**
     * @brief Returns a distinguished name which uniquely identifies a
     * certificate requester across all devices.
     *
     * @pre
     * - Material number must be configured via
     *   @ref DFL::Crypto::Environment::config
     * - Common name must be configured via
     *   @ref DFL::Crypto::Store::requestCertificateFor(const
     * DFL::Component::Key& requester, DFL::Crypto::CommonName cn, DFL::Oids
     * roles)
     *
     * @return None if and only if key could not be found.
     *
     * @throw std::runtime_error in case preconditions are violated.
     *
     * @deprecated Use Store::generateCsrFor and Csr::subject.
     *
     * @snippet Crypto/Test/UnitTest/TestTable.cpp distinguishedName
     */
    boost::optional<DistinguishedName> distinguishedName(
        const Component::Key& compKey) const;

private:
    Impl::Table m_implTable{};
};

/**
 * @brief Compares two tables.
 *
 * Two tables are equal if they contain the same table items in the same order
 * and the same serial and material number.
 *
 * @snippet Crypto/Test/UnitTest/TestTable.cpp cmp
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const Table& lhs, const Table& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const Table& lhs, const Table& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given tables.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(Table& a, Table& b) noexcept;
}
