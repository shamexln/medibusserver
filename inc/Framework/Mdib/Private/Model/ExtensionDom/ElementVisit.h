#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Element.h>
#include <Framework/Mdib/Private/Model/ExtensionDom/AttributeVisit.h>
#include <Framework/Mdib/Private/Model/ExtensionDom/QNameVisit.h>

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
template<class Visitor>
void visitMembers(Visitor& vis, const Dom::Element& e)
{
    vis(e.name());
    vis(e.attributes());
}
}}
}
