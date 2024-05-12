#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/ExtensionDom/Node.h>
#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Dom
{

/**
 * @brief Helper class for iterating over a tree of \ref DFL::Mdib::Dom::Node "Nodes"
 * @details This class provides methods to get to a child, sibling or parent
 * node relative to its current position in the tree.
 *
 * @startuml
 *   object Navigator
 *   together {
 *       object "Node" as E0
 *       E0 : depth = 0
 *       E0 : content = Element
 *
 *       object "Node" as E1
 *       E1 : depth = 1
 *       E1 : content = Element
 *
 *       object "Node" as E1T1
 *       E1T1 : depth = 2
 *       E1T1 : content = Text
 *
 *       object "Node" as E2
 *       E2 : depth = 1
 *       E2 : content = Element
 *
 *       object "Node" as E2E1
 *       E2E1 : depth = 2
 *       E2E1 : content = Element
 *
 *       object "Node" as E2E2
 *       E2E2 : depth = 2
 *       E2E2 : content = Element
 *
 *       object "Node" as E2E3
 *       E2E3 : depth = 2
 *       E2E3 : content = Element
 *
 *       object "Node" as E3
 *       E3 : depth = 1
 *       E3 : content = Element
 *   }
 *
 *   E0 -right- E1
 *   E1 -right- E1T1
 *   E1T1 -right- E2
 *   E2 -right- E2E1
 *   E2E1 -right- E2E2
 *   E2E2 -right- E2E3
 *   E2E3 -right- E3
 *
 *   Navigator ..> E0 : parent()
 *   Navigator ..> E1 : prevSibling()
 *   Navigator --> E2 : current
 *   Navigator ..> E2E1 : firstChild()
 *   Navigator ..> E2E3 : lastChild()
 *   Navigator ..> E3 : nextSibling()
 * @enduml
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP Navigator
{
    public:
        /**
         * @brief %Iterator type
         */
        using Iterator = Nodes::const_iterator;

        /**
         * @brief Construct a navigator referencing to the beginning of a \ref DFL::Mdib::Dom::Nodes "Node tree"
         */
        explicit Navigator(const Nodes& tree);

        /**
         * @brief Construct a navigator referencing to a position in a \ref DFL::Mdib::Dom::Nodes "Node tree"
         */
        explicit Navigator(const Nodes& tree, Iterator position);

        /**
         * @brief Navigate to the first child of the current node, returning empty if there are no children
         */
        Navigator firstChild() const;

        /**
         * @brief Navigate to the last child of the current node, returning empty if there are no children
         */
        Navigator lastChild() const;

        /**
         * @brief Navigate to the next sibling of the current node, returning empty if the current node is the last child
         */
        Navigator nextSibling() const;

        /**
         * @brief Navigate to the previous sibling of current node, returning empty if the current node is the first child
         */
        Navigator prevSibling() const;

        /**
         * @brief Navigate to the parent of the current node, returning empty if the current node is a root (has no parent)
         */
        Navigator parent() const;

        /**
         * @brief reports whether the navigator is not empty (current node is valid)
         */
        explicit operator bool() const;

        /**
         * @brief dereference the current node
         */
        const Node& operator*() const;

        /**
         * @brief pointer to the current node
         */
        const Node* operator->() const;

    private:
        /**
         * @brief Default constructor creates an empty navigator
         */
        Navigator() = default;

        /**
         * @brief Construct a navigator that refers to a particular node in the tree
         */
        Navigator(Iterator begin, Iterator end, Iterator current);

        /**
         * @brief Helper method to get the depth of the current node.
         */
        NodeDepth currentDepth() const;

        Iterator m_treeBegin;
        Iterator m_treeEnd;
        Iterator m_current;
};

inline Navigator::operator bool() const
{
    return m_current != m_treeEnd;
}

inline const Node& Navigator::operator*() const
{
    return *m_current;
}

inline const Node* Navigator::operator->() const
{
    return &*m_current;
}

inline NodeDepth Navigator::currentDepth() const
{
    return m_current->depth();
}

}
}
}
