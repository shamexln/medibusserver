#pragma once

#include <Framework/Mdib/Public/Model/Root.h>

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
void visitMembers(Visitor& vis, const Root& r)
{
    vis(r.get());
}
}
}
}
