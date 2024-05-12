#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Availability of a metric.
 * @ingroup Mdib
 */
enum class MetricAvailability
{
    /// Stopping or ceasing for a time; alternately ceasing and beginning again. Example: non-invasive blood pressure measurement.
    Intermittent,
    /// Without break, cessation, or interruption; without intervening time.
    Continuous
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MetricAvailability, (Intermittent)(Continuous))

} /* namespace Mdib */
} /* namespace DFL */
