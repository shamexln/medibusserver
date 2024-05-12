#pragma once

#include <Framework/Mdib/Public/Model/Operation/OperationGroup.h>

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
void visitMembers(Visitor& vis, const OperationGroup& og)
{
    vis(og.operatingMode());
    vis(og.operations());
    vis(og.type());
    vis(og.extensions());
}
}
}
}
