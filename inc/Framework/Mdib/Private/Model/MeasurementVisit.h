#pragma once

#include <Framework/Mdib/Public/Model/Measurement.h>

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
void visitMembers(Visitor& vis, const Measurement& m)
{
    vis(m.value());
    vis(m.unit());
    vis(m.extensions());
}
}
}
}
