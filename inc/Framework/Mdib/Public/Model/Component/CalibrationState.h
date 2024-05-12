#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Calibration state of a component.
 * @ingroup Mdib
 */
enum class CalibrationState
{
    /// Defines that a component is not calibrated.
    NotCalibrated,
    /// Defines that a component requires a calibration.
    CalibrationRequired,
    /// Defines that a component is calibrated.
    Calibrated,
    /// Defines that a calibration for a component is running.
    Running,
    /// The calibration state is defined by other means.
    Other

};
DFL_ENUM_CLASS_STREAM_OPERATOR(CalibrationState, (NotCalibrated)(CalibrationRequired)(Calibrated)(Running)(Other))

} /* namespace Mdib */
} /* namespace DFL */
