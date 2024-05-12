#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Level of validity of a measured value.
 * @ingroup Mdib
 */
enum class MeasurementValidity
{
    /// A measured value that is correct from the perspective of the measuring device.
    Valid,
    /// A measured value where the validity has been confirmed by an external actor, e.g., an operator, other than the medical device.
    ValidatedData,
    /// Indicates that a new measurement is just being taken and therefore the measured value is not available.
    MeasurementOngoing,
    /// A measured value where correctness can not be guaranteed.
    Questionable,
    /// A measured value where correctness can not be guaranteed, because a calibration is currently going on.
    CalibrationOngoing,
    /// A measured value that is incorrect from the perspective of the measuring device.
    Invalid,
    /// A measured value where correctness can not be guaranteed as it is above all defined technical ranges for that metric.
    Overflow,
    /// A measured value where correctness can not be guaranteed as it is below all defined technical ranges for that metric.
    Underflow,
    /// No value can be derived, e.g., if a sensor is not placed correctly.
    NotAvailable
};

DFL_ENUM_CLASS_STREAM_OPERATOR(MeasurementValidity, (Valid)(ValidatedData)(MeasurementOngoing)(Questionable)(CalibrationOngoing)(Invalid)(Overflow)(Underflow)(NotAvailable))
}
}
