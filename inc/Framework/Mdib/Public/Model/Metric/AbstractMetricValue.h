#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Metric/Annotation.h>
#include <Framework/Mdib/Public/Model/Metric/MetricQuality.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Abstract value of a metric.
 * @ingroup Mdib
 */
class AbstractMetricValue: public Impl::HasExtensions
{
    public:
        /**
         * @brief The quality state of the determined value of a metric.
         */
        const MetricQuality& metricQuality() const;

        /**
         * @brief A list of \ref CodedValue objects that describe the metric value's annotations.
         */
        const Annotations& annotations() const;

        /**
         * @brief Time when measurement activity was started.
         * @return Timestamp of when the measurement started or \c boost::none if undefined.
         */
        const boost::optional<Timestamp>& startTime() const;

        /**
         * @brief Time when measurement activity was stopped.
         * @return Timestamp of when the measurement stopped or \c boost::none if undefined.
         */
        const boost::optional<Timestamp>& stopTime() const;

        /**
         * @brief Time when determined value has been derived from measurement.
         * @return Timestamp of measurement derivation or \c boost::none if undefined.
         */
        const boost::optional<Timestamp>& determinationTime() const;

    protected:
        /**
         * @brief Defaults to an invalid metric value.
         */
        AbstractMetricValue() = default;

        /**
         * @brief Full constructor (without extensions).
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
        AbstractMetricValue(Arg1&& metricQuality,
                            Arg2&& annotations,
                            Arg3&& startTime,
                            Arg4&& stopTime,
                            Arg5&& determinationTime);

        /**
         * @brief Full constructor (with extensions).
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
        AbstractMetricValue(Arg1&& metricQuality,
                            Arg2&& annotations,
                            Arg3&& startTime,
                            Arg4&& stopTime,
                            Arg5&& determinationTime,
                            Arg6&& extensions);

    private:
        MetricQuality m_metricQuality;
        Annotations m_annotations;
        boost::optional<Timestamp> m_startTime;
        boost::optional<Timestamp> m_stopTime;
        boost::optional<Timestamp> m_determinationTime;
};

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline AbstractMetricValue::AbstractMetricValue(Arg1&& metricQuality,
                                                Arg2&& annotations,
                                                Arg3&& startTime,
                                                Arg4&& stopTime,
                                                Arg5&& determinationTime) :
        m_metricQuality(std::forward<Arg1>(metricQuality)),
        m_annotations(std::forward<Arg2>(annotations)),
        m_startTime(std::forward<Arg3>(startTime)),
        m_stopTime(std::forward<Arg4>(stopTime)),
        m_determinationTime(std::forward<Arg5>(determinationTime))
{
}

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline AbstractMetricValue::AbstractMetricValue(Arg1&& metricQuality,
                                                Arg2&& annotations,
                                                Arg3&& startTime,
                                                Arg4&& stopTime,
                                                Arg5&& determinationTime,
                                                Arg6&& extensions) :
        Impl::HasExtensions(std::forward<Arg6>(extensions)),
        m_metricQuality(std::forward<Arg1>(metricQuality)),
        m_annotations(std::forward<Arg2>(annotations)),
        m_startTime(std::forward<Arg3>(startTime)),
        m_stopTime(std::forward<Arg4>(stopTime)),
        m_determinationTime(std::forward<Arg5>(determinationTime))
{
}

inline const MetricQuality& AbstractMetricValue::metricQuality() const
{
    return m_metricQuality;
}

inline const Annotations& AbstractMetricValue::annotations() const
{
    return m_annotations;
}

inline const boost::optional<Timestamp>& AbstractMetricValue::startTime() const
{
    return m_startTime;
}

inline const boost::optional<Timestamp>& AbstractMetricValue::stopTime() const
{
    return m_stopTime;
}

inline const boost::optional<Timestamp>& AbstractMetricValue::determinationTime() const
{
    return m_determinationTime;
}

} /* namespace Mdib */
} /* namespace DFL */
