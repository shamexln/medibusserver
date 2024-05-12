#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricDescriptor.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of a \ref StringMetric.
 * @ingroup Mdib
 */
class StringMetricDescriptor: public AbstractMetricDescriptor
{
    DFL_MDIB_IMMUTABLE(StringMetricDescriptor)

    public:
        /**
         * @brief Default constructor that applies defaults from \ref AbstractMetricDescriptor.
         */
        StringMetricDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        StringMetricDescriptor(SafetyClassification safetyClassification,
                               boost::optional<CodedValue>&& type,
                               const Unit& unit,
                               const BodySites& bodySites,
                               MetricCategory metricCategory,
                               const boost::optional<DerivationMethod>& derivationMethod,
                               MetricAvailability metricAvailability,
                               const boost::optional<Duration>& maxMeasurementTime,
                               const boost::optional<Duration>& maxDelayTime,
                               const boost::optional<Duration>& determinationPeriod,
                               const boost::optional<Duration>& lifeTimePeriod,
                               const boost::optional<Duration>& activationDuration,
                               const Relations& relations,
                               ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        StringMetricDescriptor(SafetyClassification safetyClassification,
                               const boost::optional<CodedValue>& type,
                               const Unit& unit,
                               const BodySites& bodySites,
                               MetricCategory metricCategory,
                               const boost::optional<DerivationMethod>& derivationMethod,
                               MetricAvailability metricAvailability,
                               const boost::optional<Duration>& maxMeasurementTime,
                               const boost::optional<Duration>& maxDelayTime,
                               const boost::optional<Duration>& determinationPeriod,
                               const boost::optional<Duration>& lifeTimePeriod,
                               const boost::optional<Duration>& activationDuration,
                               const Relations& relations,
                               ExtensionTypes extensions = ExtensionTypes{ });
};

inline StringMetricDescriptor::StringMetricDescriptor(SafetyClassification safetyClassification,
                                                      boost::optional<CodedValue>&& type,
                                                      const Unit& unit,
                                                      const BodySites& bodySites,
                                                      MetricCategory metricCategory,
                                                      const boost::optional<DerivationMethod>& derivationMethod,
                                                      MetricAvailability metricAvailability,
                                                      const boost::optional<Duration>& maxMeasurementTime,
                                                      const boost::optional<Duration>& maxDelayTime,
                                                      const boost::optional<Duration>& determinationPeriod,
                                                      const boost::optional<Duration>& lifeTimePeriod,
                                                      const boost::optional<Duration>& activationDuration,
                                                      const Relations& relations,
                                                      ExtensionTypes extensions) :
        AbstractMetricDescriptor(safetyClassification,
                                 std::move(type),
                                 unit,
                                 bodySites,
                                 metricCategory,
                                 derivationMethod,
                                 metricAvailability,
                                 maxMeasurementTime,
                                 maxDelayTime,
                                 determinationPeriod,
                                 lifeTimePeriod,
                                 activationDuration,
                                 relations,
                                 std::move(extensions))
{
}

inline StringMetricDescriptor::StringMetricDescriptor(SafetyClassification safetyClassification,
                                                      const boost::optional<CodedValue>& type,
                                                      const Unit& unit,
                                                      const BodySites& bodySites,
                                                      MetricCategory metricCategory,
                                                      const boost::optional<DerivationMethod>& derivationMethod,
                                                      MetricAvailability metricAvailability,
                                                      const boost::optional<Duration>& maxMeasurementTime,
                                                      const boost::optional<Duration>& maxDelayTime,
                                                      const boost::optional<Duration>& determinationPeriod,
                                                      const boost::optional<Duration>& lifeTimePeriod,
                                                      const boost::optional<Duration>& activationDuration,
                                                      const Relations& relations,
                                                      ExtensionTypes extensions) :
        AbstractMetricDescriptor(safetyClassification,
                                 type,
                                 unit,
                                 bodySites,
                                 metricCategory,
                                 derivationMethod,
                                 metricAvailability,
                                 maxMeasurementTime,
                                 maxDelayTime,
                                 determinationPeriod,
                                 lifeTimePeriod,
                                 activationDuration,
                                 relations,
                                 std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref StringMetricDescriptorSharedPtr for descriptor \ref StringMetricDescriptor.
 * @ingroup Mdib
 */
using StringMetricDescriptorSharedPtr = SharedPtr<StringMetricDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
