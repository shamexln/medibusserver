#pragma once

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/QName.h>
#include <Framework/Mdib/Public/Model/ExtensionDom/Node.h>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief MustUnderstand attribute value for an \ref DFL::Mdib::ExtensionType
 * @details In cases where an extension modifies the meaning of the element that contains it, a MustUnderstand
 * attribute is senseful. This means that the data cannot safely be processed unless the application knows
 * the meaning of the extension.
 * @ingroup Mdib
 */
enum class MustUnderstand
{
    False,
    True,
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MustUnderstand, (False)(True))

/**
 * @brief Type for modeling extensions of any kind.
 * @details Extensions enhance objects with any kind of information which cannot be otherwise represented
 * by BICEPS. The %ExtensionType class provides access to the qualified name of an extension which
 * includes the namespace where the extension is defined, as well as whether or not the \ref MustUnderstand is
 * provided and true.
 * @ingroup Mdib
 */
class ExtensionType
{
    public:
        /// @brief Construct an extension with from a tree of \ref DFL::Mdib::Dom::Node "Nodes" and the value of the \ref MustUnderstand attribute
        ExtensionType(Dom::Nodes nodeTree, MustUnderstand mustUnderstand);

        /// @brief Convenience constructor for an extension with only a single element.
        ExtensionType(const QName& qualifiedName,
                      MustUnderstand mustUnderstand,
                      Dom::Attributes attributes = Dom::Attributes());

        /// @brief Convenience constructor for an extension with only a single element.
        ExtensionType(QName&& qualifiedName,
                      MustUnderstand mustUnderstand,
                      Dom::Attributes attributes = Dom::Attributes());

        /// @brief The qualified name of the extension root element
        const QName& qualifiedName() const;

        /// @brief Indicates whether the %MustUnderstand attribute of the extension is "true"
        bool mustUnderstand() const noexcept;

        /// @brief The attributes of the extension root element
        const Dom::Attributes& attributes() const;

        /// @brief Tree of \ref DFL::Mdib::Dom::Node "Nodes" modeling the extension
        const Dom::Nodes& nodeTree() const noexcept;

    private:
        Dom::Nodes m_nodeTree;
        MustUnderstand m_mustUnderstand = MustUnderstand::False;
};

inline ExtensionType::ExtensionType(Dom::Nodes nodeTree, MustUnderstand mustUnderstand) :
        m_nodeTree(std::move(nodeTree)),
        m_mustUnderstand(mustUnderstand)
{
    if (m_nodeTree.empty() || m_nodeTree.front().contentType() != Dom::Node::ContentType::Element)
    {
        throw std::runtime_error("First node in nodeTree must be the root element for the extension.");
    }
}

inline ExtensionType::ExtensionType(const QName& qualifiedName, MustUnderstand mustUnderstand, Dom::Attributes attributes) :
        m_nodeTree{ Dom::Node(Dom::NodeDepth(0), Dom::Element(qualifiedName, std::move(attributes))) },
        m_mustUnderstand(mustUnderstand)
{
}

inline ExtensionType::ExtensionType(QName&& qualifiedName, MustUnderstand mustUnderstand, Dom::Attributes attributes) :
        m_nodeTree{ Dom::Node(Dom::NodeDepth(0), Dom::Element(std::move(qualifiedName), std::move(attributes))) },
        m_mustUnderstand(mustUnderstand)
{
}

inline const QName& ExtensionType::qualifiedName() const
{
    return m_nodeTree.front().element().name();
}

inline bool ExtensionType::mustUnderstand() const noexcept
{
    return m_mustUnderstand == MustUnderstand::True;
}

inline const Dom::Attributes& ExtensionType::attributes() const
{
    return m_nodeTree.front().element().attributes();
}

inline const Dom::Nodes& ExtensionType::nodeTree() const noexcept
{
    return m_nodeTree;
}

/**
 * @brief Equal operator compares all members
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case all members equals.
 */
inline bool operator==(const ExtensionType& lhs, const ExtensionType& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }

    return lhs.nodeTree() == rhs.nodeTree()
           && lhs.mustUnderstand() == rhs.mustUnderstand();
}

/**
 * @brief Not equal operator compares all members
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case at least one member does not equal.
 */
inline bool operator!=(const ExtensionType& lhs, const ExtensionType& rhs) noexcept
{
    return !(lhs == rhs);
}

/**
 * @brief Sequence of @ref ExtensionType.
 * @ingroup Mdib
 */
using ExtensionTypes = std::vector<ExtensionType>;

}
}
