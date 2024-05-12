#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Utils/Public/StrongTypedef.h>

namespace S31::SetService
{

namespace Impl
{
struct OperationHandleTag {};
}

/**
 * @brief Handle of the set operation to invoke/was invoked.
 * @details
 * Reference to an operation, when used e.g. in reports as an untyped handle i.e. not refering to a set operation
 * entity with a typed handle.
 * @ingroup S31SetService
 */
using OperationHandle = DFL::StrongTypedef<DFL::Mdib::Handle, Impl::OperationHandleTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

}
