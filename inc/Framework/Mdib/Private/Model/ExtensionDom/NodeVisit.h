#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Node.h>
#include <Framework/Mdib/Private/Model/ExtensionDom/ElementVisit.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const Dom::Node& n)
{
    vis(n.depth());
    switch (n.contentType())
    {
        case Dom::Node::ContentType::Element:
            vis(n.element());
            break;
        case Dom::Node::ContentType::Text:
            vis(n.text());
            break;
        default:
            throw std::runtime_error("Unknown DFL::Mdib::Dom::contentType");
    }
}
}
}
}
