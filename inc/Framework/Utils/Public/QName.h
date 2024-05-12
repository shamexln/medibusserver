#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace DFL
{
namespace Impl
{
struct NamePrefixTag;
struct NamespaceUriTag;
}
/**
 * @brief Type for a \ref QName prefix string.
 * @ingroup Utils
 */
using NamePrefix = DFL::StrongTypedef<std::string, Impl::NamePrefixTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Alias for Namespace URI
 * @ingroup Utils
 */
using NamespaceUri = DFL::StrongTypedef<std::string, Impl::NamespaceUriTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief A name that may be qualified with an %XML namespace.
 * @details This class provides a qualified name of an XML element, attribute, or identifier.
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP QName
{
    public:
        /**
         * @brief Construct an empty QName.
         */
        QName();

        /**
         * @brief Construct a QName with only an unqualified local name.
         */
        explicit QName(std::string localName);

        /**
         * @brief Construct a QName from namespace, prefix and unqualified local name.
         */
        QName(NamespaceUri namespaceUri, NamePrefix prefix, std::string localName);

        /**
         * @name Namespace Uri
         * @brief The namespace uri
         */
        const NamespaceUri& namespaceUri() const noexcept;

        /**
         * @name Prefix
         * @brief The prefix string
         */
        const NamePrefix& prefix() const noexcept;

        /**
         * @name LocalName
         * @brief The unqualified local name
         */
        const std::string& localName() const noexcept;

        /**
         * @brief Checks the QName for emptiness
         */
         bool empty() const noexcept;

    private:
        NamespaceUri m_namespaceUri{};
        NamePrefix m_prefix{};
        std::string m_localName{};
};

/**
 * @brief Compares two QNames semantically, i.e. neglecting the prefix.
 * @details
 * The following test snippets shows the difference between equal and
 * semantically equal:
 * @snippet Utils/Test/UnitTest/TestQName.cpp EqualVsSemantic
 * @return true if lhs and rhs are semantically equal.
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP isSemanticallyEqual(const QName& lhs,
                                          const QName& rhs) noexcept;

/**
 * @brief Equal and unequal operator compare all members.
 * @ingroup Utils
 */
///@{
bool DFL_UTILS_EXPIMP operator==(const QName& lhs, const QName& rhs) noexcept;
bool DFL_UTILS_EXPIMP operator!=(const QName& lhs, const QName& rhs) noexcept;
///@}

}
