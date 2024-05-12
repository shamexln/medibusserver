#pragma once

#include <Framework/Mdib/Public/Model/Metric/AllowedEnumValue.h>

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
void visitMembers(Visitor& vis, const AllowedEnumValue& a)
{
    vis(a.value());
    vis(a.type());
    vis(a.identification());
    vis(a.characteristic());
}
}
}
}
