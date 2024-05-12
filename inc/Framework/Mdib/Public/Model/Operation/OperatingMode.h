#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Operating mode of an operation that defines if an operation is accessible.
 * @ingroup Mdib
 */

enum class OperatingMode
{
    /// Object is disabled.
    Disabled,
    /// Object is enabled.
    Enabled,
    /// Object is not available for interaction. This means that it is defined but currently not in a mode so that it can be interacted with.
    NotAvailable
};
DFL_ENUM_CLASS_STREAM_OPERATOR(OperatingMode, (Disabled)(Enabled)(NotAvailable))

} /* namespace Mdib */
} /* namespace DFL */
