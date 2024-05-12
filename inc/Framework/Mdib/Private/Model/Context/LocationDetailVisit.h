#pragma once

#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>

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
void visitMembers(Visitor& vis, const LocationDetail& ld)
{
    vis(ld.facility());
    vis(ld.building());
    vis(ld.floor());
    vis(ld.pointOfCare());
    vis(ld.room());
    vis(ld.bed());
    vis(ld.extensions());
}
}
}
}
