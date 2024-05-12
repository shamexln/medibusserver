#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricDescriptor.h>
#include <Framework/Mdib/Public/Model/Metric/AllowedEnumValue.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricDescriptor.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of an \ref EnumStringMetric.
 * @ingroup Mdib
 */
class EnumStringMetricDescriptor: public StringMetricDescriptor
{
    DFL_MDIB_IMMUTABLE(EnumStringMetricDescriptor)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults \ref EnumStringMetricDescriptor::allowedValues() "Allowed enumeration values" to empty sequence.
         *
         * \note Also applies defaults from \ref StringMetricDescriptor.
         */
        EnumStringMetricDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        EnumStringMetricDescriptor(SafetyClassification safetyClassification,
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
                                   AllowedEnumValues allowedValues,
                                   ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        EnumStringMetricDescriptor(SafetyClassification safetyClassification,
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
                                   AllowedEnumValues allowedValues,
                                   ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief A sequence of values that the enumerated string metric accepts as a valid value.
         */
        const AllowedEnumValues& allowedValues() const;

    private:
        AllowedEnumValues m_allowedValues;
};

inline EnumStringMetricDescriptor::EnumStringMetricDescriptor(SafetyClassification safetyClassification,
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
                                                              AllowedEnumValues allowedValues,
                                                              ExtensionTypes extensions) :
        StringMetricDescriptor(safetyClassification,
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
                               std::move(extensions)),
        m_allowedValues(std::move(allowedValues))
{
}

inline EnumStringMetricDescriptor::EnumStringMetricDescriptor(SafetyClassification safetyClassification,
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
                                                              AllowedEnumValues allowedValues,
                                                              ExtensionTypes extensions) :
        StringMetricDescriptor(safetyClassification,
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
                               std::move(extensions)),
        m_allowedValues(std::move(allowedValues))
{
}

inline const AllowedEnumValues& EnumStringMetricDescriptor::allowedValues() const
{
    return m_allowedValues;
}

/**
 * @brief Definition of shared pointer type \ref EnumStringMetricDescriptorSharedPtr for descriptor \ref EnumStringMetricDescriptor.
 * @ingroup Mdib
 */
using EnumStringMetricDescriptorSharedPtr = SharedPtr<EnumStringMetricDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
