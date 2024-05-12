#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Calibration method.
 * @ingroup Mdib
 */
enum class CalibrationType
{
    /// Offset calibration.
    Offset,
    /// Gain calibration.
    Gain,
    /// Two point calibration.
    TwoPoint,
    /// Unspecified calibration type.
    Unspecified
};
DFL_ENUM_CLASS_STREAM_OPERATOR(CalibrationType, (Offset)(Gain)(TwoPoint)(Unspecified))

} /* namespace Mdib */
} /* namespace DFL */
