#pragma once

#include <Framework/Format/Public/StdContainerIo.h>
#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   Designation of an alert signal's generation state.
 * @ingroup Mdib
 */
enum class AlertSignalPresence
{
            /**
             * @brief Indicate that an alert signal is currently generated.
             */
            On,

            /**
             * @brief Indicate that an alert signal is currently not generated.
             */
            Off,

            /**
             * @brief Indicate that an alert signal is currently generated even if the alert condition is no
             *        longer present.
             */
            Latched,

            /**
             * @brief   Indicate that an alert signal is currently not generated due to an acknowledgment even if the
             *          alert condition is still present.
             * @details Acknowledged signals are those where an auditory alert signal, that is related to a currently
             *          active alert condition, is inactive until the alert condition is no longer present.
             */
            Acknowledged
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertSignalPresence, (On)(Off)(Latched)(Acknowledged))

} /* namespace Mdib */
} /* namespace DFL */
