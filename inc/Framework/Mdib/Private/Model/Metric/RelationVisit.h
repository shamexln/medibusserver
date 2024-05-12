#pragma once

#include <Framework/Mdib/Public/Model/Metric/Relation.h>

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
void visitMembers(Visitor& vis, const Relation& r)
{
    vis(r.kind());
    vis(r.entries());
    vis(r.code());
    vis(r.identification());
    vis(r.extensions());
}
}
}
}
