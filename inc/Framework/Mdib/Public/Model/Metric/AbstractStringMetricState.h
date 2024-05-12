#pragma once

#include <Framework/Mdib/Public/Model/ComponentActivation.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricState.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricValue.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Base class for all string metrics.
 * @ingroup Mdib
 */
class AbstractStringMetricState: public AbstractMetricState
{
    DFL_MDIB_IMMUTABLE(AbstractStringMetricState)

    protected:
        /**
         * @brief Default constructor that sets \ref StringMetricState::metricValue() "Metric value" to default \ref StringMetricValue.
         * @details \note Also applies defaults from \ref AbstractMetricState.
         */
        AbstractStringMetricState();

        /**
         * @brief Full constructor.
         */
        AbstractStringMetricState(ComponentActivation activationState,
                          const boost::optional<Duration>& activeDeterminationPeriod,
                          const boost::optional<Duration>& lifeTimePeriod,
                          const BodySites& bodySites,
                          const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                          const boost::optional<StringMetricValue>& metricValue,
                          ExtensionTypes extensions = ExtensionTypes{ });

        ~AbstractStringMetricState() = default;

    public:
        /**
         * @brief Current value of the metric.
         * @return Current metric value or \c boost::none if not configured.
         */
        const boost::optional<StringMetricValue>& metricValue() const;

    private:
        boost::optional<StringMetricValue> m_metricValue;
};

inline AbstractStringMetricState::AbstractStringMetricState() :
        AbstractMetricState(),
        m_metricValue(StringMetricValue())
{
}

inline AbstractStringMetricState::AbstractStringMetricState(ComponentActivation activationState,
                                            const boost::optional<Duration>& activeDeterminationPeriod,
                                            const boost::optional<Duration>& lifeTimePeriod,
                                            const BodySites& bodySites,
                                            const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                            const boost::optional<StringMetricValue>& metricValue, // NOLINT(modernize-pass-by-value)
                                            ExtensionTypes extensions) :
        AbstractMetricState(activationState, activeDeterminationPeriod, lifeTimePeriod, bodySites, physicalConnector, std::move(extensions)),
        m_metricValue(metricValue)
{
}

inline const boost::optional<StringMetricValue>& AbstractStringMetricState::metricValue() const
{
    return m_metricValue;
}

} /* namespace Mdib */
} /* namespace DFL */
