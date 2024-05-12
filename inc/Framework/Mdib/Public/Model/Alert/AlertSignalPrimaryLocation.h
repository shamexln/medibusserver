#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   Defines where the primary alert signal is generated.
 * @ingroup Mdib
 */
enum class AlertSignalPrimaryLocation
{
        /**
         * @brief   The alert signal is perceivable on the machine where the alert condition has been detected.
         */
        Local,

        /**
         * @brief   The alert signal is perceivable on a remote machine.
         */
        Remote
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertSignalPrimaryLocation, (Local)(Remote))

} /* namespace Mdib */
} /* namespace DFL */
