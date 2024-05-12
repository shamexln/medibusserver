#pragma once

#include <Framework/Mdib/Public/Model/Component/Udi.h>

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
void visitMembers(Visitor& vis, const Udi& udi)
{
    vis(udi.deviceIdentifier());
    vis(udi.humanReadableForm());
    vis(udi.issuer());
    vis(udi.jurisdiction());
    vis(udi.extensions());
}
}
}
}
