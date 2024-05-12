#pragma once

#include <Framework/Mdib/Public/Model/Operation/ActivateArgument.h>

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
void visitMembers(Visitor& vis, const ActivateArgument& aa)
{
    vis(aa.name());
    vis(aa.dataType());
}
}
}
}
