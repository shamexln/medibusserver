#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief The metric category makes it possible to distinguish between different manifestations of a metric like measurements, settings or recommendations.
 * @details Example: if the respiratory rate can be adjusted and the ventilator is smart and provides a recommendation, there are
 * likely be at least three metrics with a type of "Respiratory Rate":
 *
 * - Metric with metric category set to \ref MetricCategory::Measurement. This metric is the actual measured value.
 * - Metric with metric category set to \ref MetricCategory::Setting. This metric is the adjustable value.
 * - Metric with metric category set to \ref MetricCategory::Recommendation. This metric is the recommended value derived from some smart algorithm.
 *
 * @ingroup Mdib
 */
enum class MetricCategory
{
    /// None of the other categories is valid for the metric.
    Unspecified,
    /// The metric has been derived by measurement.
    Measurement,
    /// The metric has been derived by calculation only.
    Calculation,
    /// The metric has a value that is adjustable by some (local or remote) control means.
    Setting,
    /// The metric has a value that is adjustable by some (local or remote) control means. It modifies other values only temporarily for preview purposes until it is committed to the related metric from the setting category.
    Presetting,
    /// The metric is a proposal for a setting or presetting.
    Recommendation
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MetricCategory, (Unspecified)(Measurement)(Calculation)(Setting)(Presetting)(Recommendation))

} /* namespace Mdib */
} /* namespace DFL */
