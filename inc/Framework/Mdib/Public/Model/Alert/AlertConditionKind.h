#pragma once

#include <Framework/Format/Public/StdContainerIo.h>
#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   Categorizes alert conditions by their origin.
 * @ingroup Mdib
 */
enum class AlertConditionKind
{
    /**
     * @brief   The condition arises from a patient-related variable.
     * @details Examples: "Blood pressure high" or "minute volume low".
     */
    Physiological,

    /**
     * @brief   The condition arises from a monitored equipment-related or alert system-related variable.
     * @details Examples: "battery low" or "sensor unplugged".
     */
    Technical,

    /**
     * @brief   The condition arises from another origin.
     * @details Example: equipment-user advisory conditions like "room temperature high".
     */
    Other
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertConditionKind, (Physiological)(Technical)(Other))

} /* namespace Mdib */
} /* namespace DFL */
