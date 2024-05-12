#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricDescriptor.h>
#include <Framework/Mdib/Public/Model/Range.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of a \ref NumericMetric.
 * @ingroup Mdib
 */
class NumericMetricDescriptor : public AbstractMetricDescriptor
{
    DFL_MDIB_IMMUTABLE(NumericMetricDescriptor)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref NumericMetricDescriptor::resolution() "Resolution" to \c 1
         * - \ref NumericMetricDescriptor::averagingPeriod() "Averaging period" to none
         * - \ref NumericMetricDescriptor::technicalRanges() "Technical ranges" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractMetricDescriptor.
         */
        NumericMetricDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        NumericMetricDescriptor(SafetyClassification safetyClassification,
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
                                boost::optional<Duration> averagingPeriod,
                                Ranges technicalRanges,
                                ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        NumericMetricDescriptor(SafetyClassification safetyClassification,
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
                                boost::optional<Duration> averagingPeriod,
                                Ranges technicalRanges,
                                ExtensionTypes extensions = ExtensionTypes{ });

        /**
          * @brief The resolution of the means to determine the Metric's value.
          * @details Resolution is the minimum determinable difference between two determined values.
          * @return Resolution value (decimal)
          */
        Decimal resolution() const;

        /**
         * @brief Timespan from where the measured values are used to determine the metric's value by averaging with some algorithm.
         * @details The averaging period defined in the descriptor might be not the currently active averaging period.
         * The active averaging period is part of \ref NumericMetricState.
         * @return Timespan used to average metric values.
         */
        const boost::optional<Duration>& averagingPeriod() const;

        /**
         * @brief The technical possible range of determined values.
         * @return Range of determined values
         */
        const Ranges& technicalRanges() const;

    private:
        Decimal m_resolution = Decimal(1);
        boost::optional<Duration> m_averagingPeriod;
        Ranges m_technicalRanges;
};

inline NumericMetricDescriptor::NumericMetricDescriptor(SafetyClassification safetyClassification,
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
                                                        boost::optional<Duration> averagingPeriod,
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
        m_averagingPeriod(std::move(averagingPeriod)),
        m_technicalRanges(std::move(technicalRanges))
{
}

inline NumericMetricDescriptor::NumericMetricDescriptor(SafetyClassification safetyClassification,
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
                                                        boost::optional<Duration> averagingPeriod,
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
        m_averagingPeriod(std::move(averagingPeriod)),
        m_technicalRanges(std::move(technicalRanges))
{
}

inline Decimal NumericMetricDescriptor::resolution() const
{
    return m_resolution;
}

inline const boost::optional<Duration>& NumericMetricDescriptor::averagingPeriod() const
{
    return m_averagingPeriod;
}

inline const Ranges& NumericMetricDescriptor::technicalRanges() const
{
    return m_technicalRanges;
}

/**
 * @brief Definition of shared pointer type \ref NumericMetricDescriptorSharedPtr for descriptor \ref NumericMetricDescriptor.
 * @ingroup Mdib
 */
using NumericMetricDescriptorSharedPtr = SharedPtr<NumericMetricDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
