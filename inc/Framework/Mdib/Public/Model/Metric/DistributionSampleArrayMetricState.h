#pragma once

#include <boost/optional/optional.hpp>
#include <utility>
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
 * @brief State of a \ref DistributionSampleArrayMetricDescriptor.
 * @details Contains a list of sample values. This sample array is used to transport spatial range information.
 * @ingroup Mdib
 */
class DistributionSampleArrayMetricState: public AbstractMetricState
{
    DFL_MDIB_IMMUTABLE(DistributionSampleArrayMetricState)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref DistributionSampleArrayMetricState::metricValue() "Metric value" to default \ref SampleArrayValue
         * - \ref DistributionSampleArrayMetricState::physiologicalRanges() "Physiological ranges" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractMetricState.
         */
        DistributionSampleArrayMetricState();

        /**
         * @brief Full constructor.
         */
        DistributionSampleArrayMetricState(ComponentActivation activationState,
                                           const boost::optional<Duration>& activeDeterminationPeriod,
                                           const boost::optional<Duration>& lifeTimePeriod,
                                           const BodySites& bodySites,
                                           const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                           const boost::optional<SampleArrayValue>& metricValue,
                                           Ranges physiologicalRanges,
                                           ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Current value of the metric.
         * @return Metric value or \c boost::none if not configured.
         */
        const boost::optional<SampleArrayValue>& metricValue() const;

        /**
         * @brief The physiological reasonable range of determined values.
         * @details This is not an alarming range.
         */
        const Ranges& physiologicalRanges() const;

    private:
        boost::optional<SampleArrayValue> m_metricValue;
        Ranges m_physiologicalRanges;
};

inline DistributionSampleArrayMetricState::DistributionSampleArrayMetricState() :
        AbstractMetricState(),
        m_metricValue(SampleArrayValue()),
        m_physiologicalRanges(Ranges())
{
}

inline DistributionSampleArrayMetricState::DistributionSampleArrayMetricState(ComponentActivation activationState,
                                                                              const boost::optional<Duration>& activeDeterminationPeriod,
                                                                              const boost::optional<Duration>& lifeTimePeriod,
                                                                              const BodySites& bodySites,
                                                                              const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                                                              const boost::optional<SampleArrayValue>& metricValue, // NOLINT(modernize-pass-by-value)
                                                                              Ranges physiologicalRanges,
                                                                              ExtensionTypes extensions) :
        AbstractMetricState(activationState, activeDeterminationPeriod, lifeTimePeriod, bodySites, physicalConnector, std::move(extensions)),
        m_metricValue(metricValue),
        m_physiologicalRanges(std::move(physiologicalRanges))
{
}

inline const boost::optional<SampleArrayValue>& DistributionSampleArrayMetricState::metricValue() const
{
    return m_metricValue;
}

inline const Ranges& DistributionSampleArrayMetricState::physiologicalRanges() const
{
    return m_physiologicalRanges;
}

/**
 * @brief Definition of shared pointer type \ref DistributionSampleArrayMetricStateSharedPtr for state \ref DistributionSampleArrayMetricState.
 * @ingroup Mdib
 */
using DistributionSampleArrayMetricStateSharedPtr = SharedPtr<DistributionSampleArrayMetricState>;


} /* namespace Mdib */
} /* namespace DFL */
