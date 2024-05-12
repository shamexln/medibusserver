#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricState.h>
#include <Framework/Mdib/Public/Model/Metric/SampleArrayValue.h>
#include <Framework/Mdib/Public/Model/Range.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the volatile part of a \ref RealTimeSampleArrayMetric.
 * @ingroup Mdib
 */
class RealTimeSampleArrayMetricState : public AbstractMetricState
{
    DFL_MDIB_IMMUTABLE(RealTimeSampleArrayMetricState)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref RealTimeSampleArrayMetricState::metricValue() "Metric value" to default \ref SampleArrayValue
         * - \ref RealTimeSampleArrayMetricState::physiologicalRanges() "Physiological ranges" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractMetricState.
         */
        RealTimeSampleArrayMetricState();

        /**
         * @brief Full constructor (without extensions)
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
        RealTimeSampleArrayMetricState(Arg1&& activationState,
                                       Arg2&& activeDeterminationPeriod,
                                       Arg3&& lifeTimePeriod,
                                       Arg4&& bodySites,
                                       Arg5&& physicalConnector,
                                       Arg6&& metricValue,
                                       Arg7&& physiologicalRanges);

        /**
         * @brief Full constructor (with extensions)
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
        RealTimeSampleArrayMetricState(Arg1&& activationState,
                                       Arg2&& activeDeterminationPeriod,
                                       Arg3&& lifeTimePeriod,
                                       Arg4&& bodySites,
                                       Arg5&& physicalConnector,
                                       Arg6&& metricValue,
                                       Arg7&& physiologicalRanges,
                                       Arg8&& extensions);

        /**
         * @brief Current value of the metric.
         * @return Metric value or \c boost::none if not configured.
         */
        const boost::optional<SampleArrayValue>& metricValue() const;

        /**
         * @brief The physiological reasonable range of determined values.
         * @details This is not an alarming range.
         * @return Range of determined values
         */
        const Ranges& physiologicalRanges() const;

    private:
        boost::optional<SampleArrayValue> m_metricValue;
        Ranges m_physiologicalRanges;
};

inline RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState() :
        AbstractMetricState(),
        m_metricValue(SampleArrayValue()),
        m_physiologicalRanges(Ranges())
{
}

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState(Arg1&& activationState,
                                                                      Arg2&& activeDeterminationPeriod,
                                                                      Arg3&& lifeTimePeriod,
                                                                      Arg4&& bodySites,
                                                                      Arg5&& physicalConnector,
                                                                      Arg6&& metricValue,
                                                                      Arg7&& physiologicalRanges) :
      AbstractMetricState(std::forward<Arg1>(activationState),
                          std::forward<Arg2>(activeDeterminationPeriod),
                          std::forward<Arg3>(lifeTimePeriod),
                          std::forward<Arg4>(bodySites),
                          std::forward<Arg5>(physicalConnector)),
      m_metricValue(std::forward<Arg6>(metricValue)),
      m_physiologicalRanges(std::forward<Arg7>(physiologicalRanges))
{
}

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
inline RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState(Arg1&& activationState,
                                                                      Arg2&& activeDeterminationPeriod,
                                                                      Arg3&& lifeTimePeriod,
                                                                      Arg4&& bodySites,
                                                                      Arg5&& physicalConnector,
                                                                      Arg6&& metricValue,
                                                                      Arg7&& physiologicalRanges,
                                                                      Arg8&& extensions) :
      AbstractMetricState(std::forward<Arg1>(activationState),
                          std::forward<Arg2>(activeDeterminationPeriod),
                          std::forward<Arg3>(lifeTimePeriod),
                          std::forward<Arg4>(bodySites),
                          std::forward<Arg5>(physicalConnector),
                          std::forward<Arg8>(extensions)),
      m_metricValue(std::forward<Arg6>(metricValue)),
      m_physiologicalRanges(std::forward<Arg7>(physiologicalRanges))
{
}

inline const boost::optional<SampleArrayValue>& RealTimeSampleArrayMetricState::metricValue() const
{
    return m_metricValue;
}

inline const Ranges& RealTimeSampleArrayMetricState::physiologicalRanges() const
{
    return m_physiologicalRanges;
}

/**
 * @brief Definition of shared pointer type \ref RealTimeSampleArrayMetricStateSharedPtr for state \ref RealTimeSampleArrayMetricState.
 * @ingroup Mdib
 */
using RealTimeSampleArrayMetricStateSharedPtr = SharedPtr<RealTimeSampleArrayMetricState>;


} /* namespace Mdib */
} /* namespace DFL */
