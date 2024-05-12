#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Decimals.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricValue.h>
#include <Framework/Mdib/Public/Model/Metric/Sample.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Type that contains sequences of values, i.e., sample arrays.
 * @details The \ref MetricQuality element relates to all samples.
 *
 * \ref Timestamp (see base: \ref AbstractMetricValue) refers to the first value of the array. The individual
 * timestamps of the values can thus be computed from the sample rate (see \ref RealTimeSampleArrayMetricDescriptor::samplePeriod).
 *
 * If \ref MetricQuality cannot be applied to all samples due to, e.g., some invalid values, it is allowed to
 * set \ref MetricQuality::validity to \ref MeasurementValidity::Questionable or \ref MeasurementValidity::Invalid for the whole sample array.
 *
 * Note the semantics of annotations as described in \ref Differences_to_IEEE_model "Differences to IEEE model".
 *
 * @ingroup Mdib
 */
class SampleArrayValue: public AbstractMetricValue
{
    public:

        /**
         * @brief Constructor that defaults all values.
         */
        SampleArrayValue() = default;

        /**
         * @brief Full constructor.
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
        SampleArrayValue(Arg1&& metricQuality,
                         Arg2&& annotations,
                         Arg3&& startTime,
                         Arg4&& stopTime,
                         Arg5&& determinationTime,
                         Arg6&& samples);

        /**
         * @brief Full constructor.
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
        SampleArrayValue(Arg1&& metricQuality,
                         Arg2&& annotations,
                         Arg3&& startTime,
                         Arg4&& stopTime,
                         Arg5&& determinationTime,
                         Arg6&& samples,
                         Arg7&& extensions);

        /**
         * @brief Defines the real-time sample array value type, which is a sequence of \ref Sample "samples".
         */
        const Samples& samples() const;

    private:
        Samples m_samples;
};

/**
 * @brief Equal compare of \ref SampleArrayValue.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are equal.
 */
DFL_MDIB_EXPIMP bool operator==(const SampleArrayValue& lhs, const SampleArrayValue& rhs);

/**
 * @brief Not equal compare of \ref SampleArrayValue.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are not equal.
 */
DFL_MDIB_EXPIMP bool operator!=(const SampleArrayValue& lhs, const SampleArrayValue& rhs);

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline SampleArrayValue::SampleArrayValue(Arg1&& metricQuality,
                                          Arg2&& annotations,
                                          Arg3&& startTime,
                                          Arg4&& stopTime,
                                          Arg5&& determinationTime,
                                          Arg6&& samples):
        AbstractMetricValue(std::forward<Arg1>(metricQuality),
                            std::forward<Arg2>(annotations),
                            std::forward<Arg3>(startTime),
                            std::forward<Arg4>(stopTime),
                            std::forward<Arg5>(determinationTime)),
        m_samples(std::forward<Arg6>(samples))
{
}

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline SampleArrayValue::SampleArrayValue(Arg1&& metricQuality,
                                          Arg2&& annotations,
                                          Arg3&& startTime,
                                          Arg4&& stopTime,
                                          Arg5&& determinationTime,
                                          Arg6&& samples,
                                          Arg7&& extensions):
        AbstractMetricValue(std::forward<Arg1>(metricQuality),
                            std::forward<Arg2>(annotations),
                            std::forward<Arg3>(startTime),
                            std::forward<Arg4>(stopTime),
                            std::forward<Arg5>(determinationTime),
                            std::forward<Arg7>(extensions)),
        m_samples(std::forward<Arg6>(samples))
{
}


inline const Samples& SampleArrayValue::samples() const
{
    return m_samples;
}

} /* namespace Mdib */
} /* namespace DFL */
