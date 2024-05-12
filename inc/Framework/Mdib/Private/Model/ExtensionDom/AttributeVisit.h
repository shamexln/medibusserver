#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Attribute.h>
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
void visitMembers(Visitor& vis, const Dom::Attribute& a)
{
    vis(a.name());
    vis(a.value());
}
}
}
}
