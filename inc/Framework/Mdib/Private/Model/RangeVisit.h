#pragma once

#include <Framework/Mdib/Public/Model/Range.h>

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
void visitMembers(Visitor& vis, const Range& r)
{
    vis(r.lower());
    vis(r.upper());
    vis(r.stepWidth());
    vis(r.relativeAccuracy());
    vis(r.absoluteAccuracy());
    vis(r.extensions());
}
}
}
}
