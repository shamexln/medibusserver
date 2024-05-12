#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   Activation state for alert systems.
 * @details Describes the activation state of alert system elements:
 *
 * - The alert system itself: \ref AlertSystemState
 * - The alert condition: \ref AlertConditionState
 * - The alert signal: \ref AlertSignalState
 *
 * @ingroup Mdib
 */
enum class AlertActivation
{
        /// The element is operating.
        On,

        /// The element is not operating.
        Off,

        /// The element itself is temporarily not operating.
        Paused
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertActivation, (On)(Off)(Paused))

} /* namespace Mdib */
} /* namespace DFL */
