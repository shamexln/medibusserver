#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Node.h>

namespace DFL
{
namespace Mdib
{
namespace Dom
{

/**
 * @brief Helper class to simplify building a tree of \ref DFL::Mdib::Dom::Node "Nodes"
 * @details This class facilitates building a sequence of \ref DFL::Mdib::Dom::Node as a tree
 * in depth first traversal order, where the \ref DFL::Mdib::Dom::NodeDepth
 * of a \ref DFL::Mdib::Dom::Node indicates the parent-child or sibling relationship between adjacent %Nodes.
 *
 * The %TreeBuilder is to simplify handling the depth of the next %Node to be added to the tree.
 * @ingroup Mdib
 */
class TreeBuilder
{
    public:
        /**
         * @brief Increase the depth of the \ref DFL::Mdib::Dom::Node tree to add the children of an \ref DFL::Mdib::Dom::Element
         * @details \ref DFL::Mdib::Dom::Element "Elements" and texts added after the method is called
         * will be saved as children of the node added immediately preceding the call.  It is required
         * that for each call there is a preceding %Element already added to the tree.
         */
        void beginChildren();

        /**
         * @brief Decrease the depth of the \ref DFL::Mdib::Dom::Node tree to finish adding children to an \ref DFL::Mdib::Dom::Element
         * @details \ref DFL::Mdib::Dom::Element "Elements" and texts added after the method is called
         * will be saved as siblings of the node added immediately preceding the call to \ref TreeBuilder::beginChildren()
         */
        void endChildren();

        /**
         * @name addElement
         * @brief Add an \ref DFL::Mdib::Dom::Element to the \ref DFL::Mdib::Dom::Nodes tree
         * @{
         */
        void addElement(const Element& elem);
        void addElement(Element&& elem);
        ///@}

        /**
         * @name addText
         * @brief Add a text to the \ref DFL::Mdib::Dom::Nodes tree
         * @{
         */
        void addText(const Locale::Utf8& text);
        void addText(Locale::Utf8&& text);
        ///@}

        /**
         * @brief Extract the built tree.
         * @details This method resets the internal state of the %TreeBuilder back to its
         * initial conditions of an empty node tree, and initial tree depth.
         * @returns The \ref DFL::Mdib::Dom::Nodes which was previously built.
         */
        Nodes extractNodeTree();

    private:
        Nodes m_tree;
        NodeDepth m_depth = NodeDepth(0);
};

inline void TreeBuilder::beginChildren()
{
    if (m_tree.empty()
        || m_tree.back().contentType() != Node::ContentType::Element
        || m_tree.back().depth() != m_depth)
    {
        throw std::runtime_error("TreeBuilder::beginChildren called without a parent Element added to node tree.");
    }

    m_depth++;
}

inline void TreeBuilder::endChildren()
{
    if (m_depth == NodeDepth(0))
    {
        throw std::runtime_error("TreeBuilder::endChildren called at root level of node tree.");
    }

    m_depth--;
}

inline void TreeBuilder::addElement(const Element& elem)
{
    m_tree.emplace_back(NodeDepth(m_depth), elem);
}

inline void TreeBuilder::addElement(Element&& elem)
{
    m_tree.emplace_back(NodeDepth(m_depth), std::move(elem));
}

inline void TreeBuilder::addText(const Locale::Utf8& text)
{
    m_tree.emplace_back(NodeDepth(m_depth), text);
}

inline void TreeBuilder::addText(Locale::Utf8&& text)
{
    m_tree.emplace_back(NodeDepth(m_depth), std::move(text));
}

inline Nodes TreeBuilder::extractNodeTree()
{
    Nodes result;
    result.swap(m_tree);
    m_depth = NodeDepth(0);
    return result;
}

}
}
}
