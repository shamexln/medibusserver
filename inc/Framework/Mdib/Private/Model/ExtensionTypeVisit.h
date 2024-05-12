#pragma once

#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Mdib/Private/Model/ExtensionDom/NodeVisit.h>

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
void visitMembers(Visitor& vis, const ExtensionType& et)
{
    vis(et.nodeTree());
    vis(et.mustUnderstand());
}
}
}
}
