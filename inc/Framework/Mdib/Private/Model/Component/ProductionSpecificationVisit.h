#pragma once

#include <Framework/Mdib/Public/Model/Component/ProductionSpecification.h>

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
void visitMembers(Visitor& vis, const ProductionSpecification& ps)
{
    vis(ps.specType());
    vis(ps.productionSpec());
    vis(ps.componentId());
}
}
}
}
