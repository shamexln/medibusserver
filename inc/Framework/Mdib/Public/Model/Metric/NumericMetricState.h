#pragma once

#include <boost/optional/optional.hpp>
#include <utility>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricState.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricValue.h>
#include <Framework/Mdib/Public/Model/Range.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the volatile part of a \ref NumericMetric.
 * @ingroup Mdib
 */
class NumericMetricState: public AbstractMetricState
{
    DFL_MDIB_IMMUTABLE(NumericMetricState)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref NumericMetricState::activeAveragingPeriod() "Active averaging period" to none
         * - \ref NumericMetricState::metricValue() "Metric value" to default \ref NumericMetricValue
         * - \ref NumericMetricState::physiologicalRanges() "Physiological ranges" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractMetricState.
         */
        NumericMetricState();

        /**
         * @brief Full constructor.
         */
        NumericMetricState(ComponentActivation activationState,
                           const boost::optional<Duration>& activeDeterminationPeriod,
                           const boost::optional<Duration>& lifeTimePeriod,
                           const BodySites& bodySites,
                           const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                           boost::optional<Duration> activeAveragingPeriod,
                           const boost::optional<NumericMetricValue>& metricValue,
                           Ranges physiologicalRanges,
                           ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Information of the currently active time period used to average values if it is different from the default value that is defined in the descriptor.
         * @return Time period used to average values or \c boost::none if not configured.
         */
        boost::optional<Duration> activeAveragingPeriod() const;

        /**
         * @brief Current value of the metric.
         * @return Metric value or \c boost::none if not configured.
         */
        const boost::optional<NumericMetricValue>& metricValue() const;

        /**
         * @brief The physiological reasonable range of determined values.
         * @details This is not an alarming range.
         */
        Ranges physiologicalRanges() const;

    private:
        boost::optional<Duration> m_activeAveragingPeriod;
        boost::optional<NumericMetricValue> m_metricValue;
        Ranges m_physiologicalRanges;
};

inline NumericMetricState::NumericMetricState() :
        AbstractMetricState(),
        m_activeAveragingPeriod(boost::none),
        m_metricValue(NumericMetricValue()),
        m_physiologicalRanges(Ranges())
{
}

inline NumericMetricState::NumericMetricState(ComponentActivation activationState,
                                              const boost::optional<Duration>& activeDeterminationPeriod,
                                              const boost::optional<Duration>& lifeTimePeriod,
                                              const BodySites& bodySites,
                                              const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                              boost::optional<Duration> activeAveragingPeriod,
                                              const boost::optional<NumericMetricValue>& metricValue, // NOLINT(modernize-pass-by-value)
                                              Ranges physiologicalRanges,
                                              ExtensionTypes extensions) :
        AbstractMetricState(activationState, activeDeterminationPeriod, lifeTimePeriod, bodySites, physicalConnector, std::move(extensions)),
        m_activeAveragingPeriod(std::move(activeAveragingPeriod)),
        m_metricValue(metricValue),
        m_physiologicalRanges(std::move(physiologicalRanges))
{
}

inline boost::optional<Duration> NumericMetricState::activeAveragingPeriod() const
{
    return m_activeAveragingPeriod;
}

inline const boost::optional<NumericMetricValue>& NumericMetricState::metricValue() const
{
    return m_metricValue;
}

inline Ranges NumericMetricState::physiologicalRanges() const
{
    return m_physiologicalRanges;
}

/**
 * @brief Definition of shared pointer type \ref NumericMetricStateSharedPtr for state \ref NumericMetricState.
 * @ingroup Mdib
 */
using NumericMetricStateSharedPtr = SharedPtr<NumericMetricState>;


} /* namespace Mdib */
} /* namespace DFL */
