#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractStringMetricState.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the volatile part of an \ref EnumStringMetric.
 * @ingroup Mdib
 */
class EnumStringMetricState: public AbstractStringMetricState
{
    DFL_MDIB_IMMUTABLE(EnumStringMetricState)

    public:
        /**
         * @brief Applies defaults from \ref StringMetricState.
         */
        EnumStringMetricState() = default;

        /**
         * @brief Full constructor.
         */
        EnumStringMetricState(ComponentActivation activationState,
                              const boost::optional<Duration>& activeDeterminationPeriod,
                              const boost::optional<Duration>& lifeTimePeriod,
                              const BodySites& bodySites,
                              const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                              const boost::optional<StringMetricValue>& metricValue,
                              ExtensionTypes extensions = ExtensionTypes{ });
};

inline EnumStringMetricState::EnumStringMetricState(ComponentActivation activationState,
                                                    const boost::optional<Duration>& activeDeterminationPeriod,
                                                    const boost::optional<Duration>& lifeTimePeriod,
                                                    const BodySites& bodySites,
                                                    const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                                    const boost::optional<StringMetricValue>& metricValue,
                                                    ExtensionTypes extensions) :
        AbstractStringMetricState(activationState, activeDeterminationPeriod, lifeTimePeriod, bodySites, physicalConnector, metricValue, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref EnumStringMetricStateSharedPtr for state \ref EnumStringMetricState.
 * @ingroup Mdib
 */
using EnumStringMetricStateSharedPtr = SharedPtr<EnumStringMetricState>;

}
}
