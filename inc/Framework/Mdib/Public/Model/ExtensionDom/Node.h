#pragma once

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Mdib/Public/Model/ExtensionDom/Element.h>

#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Dom
{
namespace Impl
{
struct NodeDepthTag;
}

/**
 * @brief Identifies the depth of a node in a tree of \ref DFL::Mdib::Dom::Node
 * @details Depth of 0 (zero) indicates the root of a tree.
 * @ingroup Mdib
 */
using NodeDepth = DFL::StrongTypedef<unsigned int,
                                     Impl::NodeDepthTag,
                                     DFL::Skill::TotallyOrdered,
                                     DFL::Skill::Streamable,
                                     DFL::Skill::UnitStepable>;

/**
 * @brief Models an xml element or text value which is part of an extension to
 * %BICEPS.
 * @details Each node identifies its content as either an \ref
 * DFL::Mdib::Dom::Element or text value. %Nodes are ordered in depth first
 * traversal order (i.e. a parent node is immediately followed by its first
 * child node).
 *
 * @startuml
 *   rectangle "1" as N1
 *   rectangle "2" as N2
 *   rectangle "3" as N3
 *   rectangle "4" as N4
 *   rectangle "5" as N5
 *   N1 --> N2
 *   N2 --> N3
 *   N2 --> N4
 *   N1 --> N5
 * @enduml
 *
 * A depth field distinguishes a parent node from its children. Adjacent nodes
 * with equal depth are siblings.
 * @ingroup Mdib
 */
class Node
{
    public:
        /**
         * @brief Describes the content of the %Node
         */
        enum class ContentType
        {
            Element,
            Text
        };

        /**
         * @brief Construct with an @ref DFL::Mdib::Dom::Element
         */
        Node(NodeDepth depth, const Element& element);

        /**
         * @brief Construct with an @ref DFL::Mdib::Dom::Element
         */
        Node(NodeDepth depth, Element&& element);

        /**
         * @brief Construct with text value
         */
        Node(NodeDepth depth, Locale::Utf8 text);

        /**
         * @brief The depth of a %Node indicates its relationship to its
         * neighbors in the node tree sequence.
         */
        NodeDepth depth() const noexcept;

        /**
         * @brief The type of content (element or text) in the node
         */
        ContentType contentType() const;

        /**
         * @brief The \ref DFL::Mdib::Dom::Element content.
         * @note This method must not be used if \ref Node::contentType() is not
         * %Element.
         */
        const Element& element() const;

        /**
         * @brief The text value content.
         * @note This method must not be used if \ref Node::contentType() is not
         * %Text
         */
        const Locale::Utf8& text() const;

        /**
         * @brief Equal operator compares all members
         * @return \c true in case all members equals.
         */
        friend bool operator==(const Node& lhs, const Node& rhs) noexcept;

    private:
        NodeDepth m_depth;
        std::variant<Element, Locale::Utf8> m_content;
};

/**
 * @brief A sequence of \ref DFL::Mdib::Dom::Node
 * @ingroup Mdib
 */
using Nodes = std::vector<Node>;

inline Node::Node(NodeDepth depth, const Element& element) :
        m_depth(depth),
        m_content(element)
{
}

inline Node::Node(NodeDepth depth, Element&& element) :
        m_depth(depth),
        m_content(std::move(element))
{
}

inline Node::Node(NodeDepth depth, Locale::Utf8 text) :
        m_depth(depth),
        m_content(std::move(text))

{
}

inline NodeDepth Node::depth() const noexcept
{
    return m_depth;
}

inline Node::ContentType Node::contentType() const
{
    switch (m_content.index())
    {
        case 0:
            return ContentType::Element;
        case 1:
            return ContentType::Text;
        default:
            throw std::runtime_error("Unknown contentType");
    }
}

inline const Element& Node::element() const
{
    return std::get<Element>(m_content);
}

inline const Locale::Utf8& Node::text() const
{
    return std::get<Locale::Utf8>(m_content);
}

/**
 * @brief Not equal operator compares all members
 * @return \c true in case all members are equal.
 */
inline bool operator==(const Node& lhs, const Node& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }
    if (lhs.m_depth != rhs.m_depth)
    {
        return false;
    }
    try
    {
        // std::variant::operator== might throw exception
        return lhs.m_content == rhs.m_content;
    }
    catch (...)
    {
        return false;
    }
}

/**
 * @brief Not equal operator compares all members
 * @return \c true in case at least one member does not equal.
 */
inline bool operator!=(const Node& lhs, const Node& rhs) noexcept
{
    return !(lhs == rhs);
}

}
}
}
