#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   Categorizes alert signals by the way they can be recognized by the alerted human,
 *          e.g., the nurse.
 * @ingroup Mdib
 */
enum class AlertSignalManifestation
{
            /**
             * @brief   The alert signal manifests in an audible manner, i.e., the alert can be heard.
             * @details Example: an alarm sound.
             */
            Audible,

            /**
             * @brief   The alert signal manifests in a visible manner, i.e., the alert can be seen.
             * @details Example: a red flashing light.
             */
            Visible,

            /**
             * @brief   The alert signal manifests in a tangible manner, i.e., the alert can be felt.
             * @details Example: vibration.
             */
            Tangible,

            /**
             * @brief   The alert signal manifests in a manner not further specified.
             */
            Other
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertSignalManifestation, (Audible)(Visible)(Tangible)(Other))

} /* namespace Mdib */
} /* namespace DFL */
