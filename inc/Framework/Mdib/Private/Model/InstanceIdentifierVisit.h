#pragma once

#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

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
void visitMembers(Visitor& vis, const InstanceIdentifier& ii)
{
    vis(ii.root());
    vis(ii.extension());
    vis(ii.type());
    vis(ii.identifierNames());
    vis(ii.extensions());
}
}
}
}
