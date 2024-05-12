#pragma once

#include <boost/optional/optional.hpp>
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
 * @brief Describes the static part of a \ref RealTimeSampleArrayMetric.
 * @ingroup Mdib
 */
class RealTimeSampleArrayMetricDescriptor : public AbstractMetricDescriptor
{
    DFL_MDIB_IMMUTABLE(RealTimeSampleArrayMetricDescriptor)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref RealTimeSampleArrayMetricDescriptor::resolution() "Resolution" to \c 0
         * - \ref RealTimeSampleArrayMetricDescriptor::samplePeriod() "Sample period" to 0 second
         * - \ref RealTimeSampleArrayMetricDescriptor::technicalRanges() "Technical ranges" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractMetricDescriptor.
         */
        RealTimeSampleArrayMetricDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        RealTimeSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                            const Duration& samplePeriod,
                                            Ranges technicalRanges,
                                            ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        RealTimeSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                            const Duration& samplePeriod,
                                            Ranges technicalRanges,
                                            ExtensionTypes extensions = ExtensionTypes{ });

        /**
          * @brief The resolution of the means to determine the metric's value.
          * @details Resolution is the minimum determinable difference between two determined values.
          */
        Decimal resolution() const;

        /**
          * @brief The sample period of the real-time sample array.
          * @details I.e., how often waveform samples are generated. The sample period is always given as a period between samples, e.g., 5 milliseconds.
          */
        const Duration& samplePeriod() const;

        /**
         * @brief The technical possible range of determined values.
         * @return Range of determined values
         */
        const Ranges& technicalRanges() const;

    private:
        Decimal m_resolution;
        Duration m_samplePeriod = DFL::Chrono::Seconds(0);
        Ranges m_technicalRanges;
};

inline RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                                                                const Duration& samplePeriod,
                                                                                Ranges technicalRanges,
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
        m_samplePeriod(samplePeriod),
        m_technicalRanges(std::move(technicalRanges))
{
}

inline RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor(SafetyClassification safetyClassification,
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
                                                                                const Duration& samplePeriod,
                                                                                Ranges technicalRanges,
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
        m_samplePeriod(samplePeriod),
        m_technicalRanges(std::move(technicalRanges))
{
}

inline Decimal RealTimeSampleArrayMetricDescriptor::resolution() const
{
    return m_resolution;
}

inline const Duration& RealTimeSampleArrayMetricDescriptor::samplePeriod() const
{
    return m_samplePeriod;
}

inline const Ranges& RealTimeSampleArrayMetricDescriptor::technicalRanges() const
{
    return m_technicalRanges;
}

/**
 * @brief Definition of shared pointer type \ref RealTimeSampleArrayMetricDescriptorSharedPtr for descriptor \ref RealTimeSampleArrayMetricDescriptor.
 * @ingroup Mdib
 */
using RealTimeSampleArrayMetricDescriptorSharedPtr = SharedPtr<RealTimeSampleArrayMetricDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
