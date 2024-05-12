#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL::Mdib
{

/**
 * @brief   Categorizes alert conditions into priorities.
 * @details Can be used to distinguish the severity of the potential or actual hazard that
 * exists if an alert condition is present.
 *
 * \note The priority is assigned through risk analysis.
 * @ingroup Mdib
 */
enum class AlertConditionPriority
{
    // We are using value with a large hamming distance to allow detection of
    // bit flips.

    /// No awareness for the alert condition is required.
    None = 0x0e23230e,
    /// Awareness for the alert condition is required.
    Low = 0x151b1b15,
    /// Prompt response to remove the alert condition is required.
    Medium = 0x1b15151b,
    /// Immediate response to remove the alert condition is required.
    High = 0x2d0e0e2d
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertConditionPriority, (None)(Low)(Medium)(High))

}
