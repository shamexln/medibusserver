#pragma once

#include <Framework/Mdib/Private/GenericRange.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Ordered range of handles.
 * @ingroup Mdib
 */
using OrderedHandleRange = Impl::GenericRange<std::vector<Handle>>;

}
}
