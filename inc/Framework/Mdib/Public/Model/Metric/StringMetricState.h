#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractStringMetricState.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the volatile part of a \ref StringMetric.
 * @ingroup Mdib
 */
class StringMetricState: public AbstractStringMetricState
{
    DFL_MDIB_IMMUTABLE(StringMetricState)

    public:
        /**
         * @brief Default constructor that sets \ref StringMetricState::metricValue() "Metric value" to none.
         * @details \note Also applies defaults from \ref AbstractMetricState.
         */
        StringMetricState() = default;

        /**
         * @brief Full constructor.
         */
        StringMetricState(ComponentActivation activationState,
                          const boost::optional<Duration>& activeDeterminationPeriod,
                          const boost::optional<Duration>& lifeTimePeriod,
                          const BodySites& bodySites,
                          const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                          const boost::optional<StringMetricValue>& metricValue,
                          ExtensionTypes extensions = ExtensionTypes{ });

};

inline StringMetricState::StringMetricState(ComponentActivation activationState,
                                            const boost::optional<Duration>& activeDeterminationPeriod,
                                            const boost::optional<Duration>& lifeTimePeriod,
                                            const BodySites& bodySites,
                                            const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                            const boost::optional<StringMetricValue>& metricValue, // NOLINT(modernize-pass-by-value)
                                            ExtensionTypes extensions) :
        AbstractStringMetricState(activationState, activeDeterminationPeriod, lifeTimePeriod, bodySites, physicalConnector, metricValue, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref StringMetricStateSharedPtr for state \ref StringMetricState.
 * @ingroup Mdib
 */
using StringMetricStateSharedPtr = SharedPtr<StringMetricState>;

} /* namespace Mdib */
} /* namespace DFL */
