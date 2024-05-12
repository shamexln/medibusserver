#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Activation state of an MDIB component.
 * @ingroup Mdib
 */
enum class ComponentActivation
{
    /// The component is operating.
    On,
    /// The component is not ready to be operated and not operating, but initialization is ongoing.
    NotReady,
    /// The component is ready to be operated, but not operating yet.
    StandBy,
    /// The component is inactive.
    Off,
    /// The component is ceasing from being ready to be operated or operating, but not yet inactive.
    Shutdown,
    /// The component has detected a failure and is not ready to be operated.
    Failure
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ComponentActivation, (On)(NotReady)(StandBy)(Off)(Shutdown)(Failure))

} /* namespace Mdib */
} /* namespace DFL */
