#pragma once

#include <Framework/Mdib/Public/Model/CodingSystem.h>

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
void visitMembers(Visitor& vis, const CodingSystem& cs)
{
    vis(cs.id());
    vis(cs.version());
    vis(cs.names());
}
}
}
}
