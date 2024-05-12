#pragma once

#include <boost/optional/optional.hpp>
#include <utility>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricDescriptor.h>
#include <Framework/Mdib/Public/Model/Range.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of an \ref DistributionSampleArrayMetric.
 * @ingroup Mdib
 */
class DistributionSampleArrayMetricDescriptor : public AbstractMetricDescriptor
{
    DFL_MDIB_IMMUTABLE(DistributionSampleArrayMetricDescriptor)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref DistributionSampleArrayMetricDescriptor::resolution() "Resolution" to \c 1
         * - \ref DistributionSampleArrayMetricDescriptor::technicalRanges() "Technical ranges" to empty sequence
         * - \ref DistributionSampleArrayMetricDescriptor::domainUnit() "Domain unit" to \ref Unit::UNSPECIFIED "unspecified"
         * - \ref DistributionSampleArrayMetricDescriptor::distributionRange() "Distribution range" to \ref Range::Range() "default range"
         *
         * \note Also applies defaults from \ref AbstractMetricDescriptor.
         */
        DistributionSampleArrayMetricDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        DistributionSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                                Decimal resolution,
                                                Ranges technicalRanges,
                                                const CodedValue& domainUnit,
                                                Range distributionRange,
                                                ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        DistributionSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                                Decimal resolution,
                                                Ranges technicalRanges,
                                                const CodedValue& domainUnit,
                                                Range distributionRange,
                                                ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The resolution of the means to determine the metric's value.
         * @details Resolution is the minimum determinable difference between two determined values.
         */
        Decimal resolution() const;

        /**
         * @brief The maximum range of the values of the distribution sample array.
         */
        const Ranges& technicalRanges() const;

        /**
         * @brief The \ref CodedValue that is used for domain values (x axis).
         */
        const CodedValue& domainUnit() const;

        /**
         * @brief Minimum and maximum domain values. A linear scale is assumed unless a step width is given.
         */
        const Range& distributionRange() const;

    private:
        Decimal m_resolution = Decimal(1);
        Ranges m_technicalRanges;
        CodedValue m_domainUnit = Unit::UNSPECIFIED;
        Range m_distributionRange;
};

inline DistributionSampleArrayMetricDescriptor::DistributionSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                                                                        Decimal resolution,
                                                                                        Ranges technicalRanges,
                                                                                        const CodedValue& domainUnit, // NOLINT(modernize-pass-by-value)
                                                                                        Range distributionRange,
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
                                 std::move(extensions)),
        m_resolution(resolution),
        m_technicalRanges(std::move(technicalRanges)),
        m_domainUnit(domainUnit),
        m_distributionRange(std::move(distributionRange))
{
}

inline DistributionSampleArrayMetricDescriptor::DistributionSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                                                                        Decimal resolution,
                                                                                        Ranges technicalRanges,
                                                                                        const CodedValue& domainUnit, // NOLINT(modernize-pass-by-value)
                                                                                        Range distributionRange,
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
                                 std::move(extensions)),
        m_resolution(resolution),
        m_technicalRanges(std::move(technicalRanges)),
        m_domainUnit(domainUnit),
        m_distributionRange(std::move(distributionRange))
{
}

inline Decimal DistributionSampleArrayMetricDescriptor::resolution() const
{
    return m_resolution;
}

inline const Ranges& DistributionSampleArrayMetricDescriptor::technicalRanges() const
{
    return m_technicalRanges;
}

inline const CodedValue& DistributionSampleArrayMetricDescriptor::domainUnit() const
{
    return m_domainUnit;
}

inline const Range& DistributionSampleArrayMetricDescriptor::distributionRange() const
{
    return m_distributionRange;
}

/**
 * @brief Definition of shared pointer type \ref DistributionSampleArrayMetricDescriptorSharedPtr for descriptor \ref DistributionSampleArrayMetricDescriptor.
 * @ingroup Mdib
 */
using DistributionSampleArrayMetricDescriptorSharedPtr = SharedPtr<DistributionSampleArrayMetricDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
