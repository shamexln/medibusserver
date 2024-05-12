#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/AbstractDescriptor.h>
#include <Framework/Mdib/Public/Model/BodySite.h>
#include <Framework/Mdib/Public/Model/DerivationMethod.h>
#include <Framework/Mdib/Public/Model/Duration.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/MetricAvailability.h>
#include <Framework/Mdib/Public/Model/Metric/MetricCategory.h>
#include <Framework/Mdib/Public/Model/Metric/Relation.h>
#include <Framework/Mdib/Public/Model/Unit.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief An abstract descriptor for a metric.
 * @ingroup Mdib
 */
class AbstractMetricDescriptor: public AbstractDescriptor
{
    DFL_MDIB_IMMUTABLE(AbstractMetricDescriptor)

    public:
        /**
         * @brief Coded value for the unit of a metric.
         */
        const Unit& unit() const;

        /**
         * @brief Optional list of coded values that describe the body sites where the metric is derived from or where it is applied to.
         */
        const BodySites& bodySites() const;

        /**
         * @brief See \ref MetricCategory.
         */
        MetricCategory metricCategory() const;

        /**
         * @brief See \ref DerivationMethod.
         */
        const boost::optional<DerivationMethod>& derivationMethod() const;

        /**
         * @brief See \ref MetricAvailability.
         */
        MetricAvailability metricAvailability() const;

        /**
         * @brief Maximum duration between start and stop time of measurement.
         * @return Maximum time duration between start and stop time or \c boost::none if undeclared.
         */
        const boost::optional<Duration>& maxMeasurementTime() const;

        /**
         * @brief Maximum delay to real time.
         * @details
         * - For a measurement or calculation, the maximum delay to real time is the estimated or known maximum difference between
         *   the point in time when a physical variable value has been present and when the value has been computed and is ready for communication.
         *   This may include an averaging period, but it does not include the communication delay.
         * - For a setting, the maximum delay to real time is the estimated or known maximum difference between the point in time when a setting has
         *   been confirmed to be applicable and the time when the setting becomes effective on the actuator. This does not include any communication delay.
         *
         * @return The maximum delay time or \c boost::none if undeclared.
         */
        const boost::optional<Duration>& maxDelayTime() const;

        /**
         * @brief The maximum time interval between two determination steps of determined values under normal conditions.
         * @details
         * - For metrics with sample arrays as determined values where the availability is not continuous, this is the period of time between
         *   two determination steps, e.g., waveform snippets that are periodically determined.
         * - For metrics with sample arrays as determined values where the availability is continuous, this is the period of time until the next waveform frame is generated.
         *
         * \note The determination period that is defined in the descriptor, might not be the currently active determination period. The active determination
         * period is part of the \ref AbstractMetricState.
         * @return The maximum determination period or \c boost::none if undeclared.
         */
        const boost::optional<Duration>& determinationPeriod() const;

        /**
         * @brief Defines the duration after the measured metric value is not useful anymore.
         * @details Example: a non-invasive blood pressure measured intermittently might only be considered useful for 24 hours. Hence, LifeTimePeriod would be "PT24H".
         * @return The activation duration or \c boost::none if undeclared.
         */
        const boost::optional<Duration>& lifeTimePeriod() const;

        /**
         * @brief Defines the maximum time period \ref AbstractMetricState::activationState is \ref ComponentActivation::On before it changes to any other state.
         * @details ActivationDuration is used to indicate the time that a measurement is performed after it has been activated. Example: if automatically
         * measured NIBP is limited to a certain time period only in order to ensure that blood flow in the arm is ensured, then the activation duration could have
         * a value of, e.g., five minutes.
         * @return The activation duration or \c boost::none if undeclared.
         */
        const boost::optional<Duration>& activationDuration() const;

        /**
         * @brief See \ref Relation.
         */
        const Relations& relations() const;

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AbstractMetricDescriptor::unit() "Unit" to \ref Unit::UNSPECIFIED "Unspecified"
         * - \ref AbstractMetricDescriptor::bodySites() "Body sites" to empty sequence
         * - \ref AbstractMetricDescriptor::metricCategory() "Metric category" to \ref MetricCategory::Unspecified "unspecified"
         * - \ref AbstractMetricDescriptor::derivationMethod() "Derivation method" to none
         * - \ref AbstractMetricDescriptor::metricAvailability() "Metric availability" to \ref MetricAvailability::Continuous "continuous"
         * - \ref AbstractMetricDescriptor::maxMeasurementTime() "Maximum measurement time" to none
         * - \ref AbstractMetricDescriptor::maxDelayTime() "Maximum delay time" to none
         * - \ref AbstractMetricDescriptor::determinationPeriod() "Determination period" to none
         * - \ref AbstractMetricDescriptor::lifeTimePeriod() "Lifetime period" to none
         * - \ref AbstractMetricDescriptor::activationDuration() "Activation duration" to none
         * - \ref AbstractMetricDescriptor::activationDuration() "Activation duration" to none
         * - \ref AbstractMetricDescriptor::relations() "Relations" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractDescriptor.
         */
        AbstractMetricDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        AbstractMetricDescriptor(SafetyClassification safetyClassification,
                                 boost::optional<CodedValue>&& type,
                                 const Unit& unit,
                                 const BodySites& bodySites,
                                 MetricCategory metricCategory,
                                 const boost::optional<DerivationMethod>& derivationMethod,
                                 MetricAvailability metricAvailability,
                                 boost::optional<Duration> maxMeasurementTime,
                                 boost::optional<Duration> maxDelayTime,
                                 boost::optional<Duration> determinationPeriod,
                                 boost::optional<Duration> lifeTimePeriod,
                                 boost::optional<Duration> activationDuration,
                                 const Relations& relations,
                                 ExtensionTypes&& extensions);

        /**
         * @brief Full constructor.
         */
        AbstractMetricDescriptor(SafetyClassification safetyClassification,
                                 const boost::optional<CodedValue>& type,
                                 const Unit& unit,
                                 const BodySites& bodySites,
                                 MetricCategory metricCategory,
                                 const boost::optional<DerivationMethod>& derivationMethod,
                                 MetricAvailability metricAvailability,
                                 boost::optional<Duration> maxMeasurementTime,
                                 boost::optional<Duration> maxDelayTime,
                                 boost::optional<Duration> determinationPeriod,
                                 boost::optional<Duration> lifeTimePeriod,
                                 boost::optional<Duration> activationDuration,
                                 const Relations& relations,
                                 ExtensionTypes&& extensions);

    private:
        Unit m_unit = Unit::UNSPECIFIED;
        BodySites m_bodySites;
        MetricCategory m_metricCategory = MetricCategory::Unspecified;
        boost::optional<DerivationMethod> m_derivationMethod;
        MetricAvailability m_metricAvailability = MetricAvailability::Continuous;
        boost::optional<Duration> m_maxMeasurementTime;
        boost::optional<Duration> m_maxDelayTime;
        boost::optional<Duration> m_determinationPeriod;
        boost::optional<Duration> m_lifeTimePeriod;
        boost::optional<Duration> m_activationDuration;
        Relations m_relations;
};

inline AbstractMetricDescriptor::AbstractMetricDescriptor(SafetyClassification safetyClassification,
                                                          boost::optional<CodedValue>&& type,
                                                          const Unit& unit, // NOLINT(modernize-pass-by-value)
                                                          const BodySites& bodySites, // NOLINT(modernize-pass-by-value)
                                                          MetricCategory metricCategory,
                                                          const boost::optional<DerivationMethod>& derivationMethod,
                                                          MetricAvailability metricAvailability,
                                                          boost::optional<Duration> maxMeasurementTime,
                                                          boost::optional<Duration> maxDelayTime,
                                                          boost::optional<Duration> determinationPeriod,
                                                          boost::optional<Duration> lifeTimePeriod,
                                                          boost::optional<Duration> activationDuration,
                                                          const Relations& relations, // NOLINT(modernize-pass-by-value)
                                                          ExtensionTypes&& extensions) :
        AbstractDescriptor(safetyClassification, std::move(type), std::move(extensions)),
        m_unit(unit),
        m_bodySites(bodySites),
        m_metricCategory(metricCategory),
        m_derivationMethod(derivationMethod),
        m_metricAvailability(metricAvailability),
        m_maxMeasurementTime(std::move(maxMeasurementTime)),
        m_maxDelayTime(std::move(maxDelayTime)),
        m_determinationPeriod(std::move(determinationPeriod)),
        m_lifeTimePeriod(std::move(lifeTimePeriod)),
        m_activationDuration(std::move(activationDuration)),
        m_relations(relations)
{
}

inline AbstractMetricDescriptor::AbstractMetricDescriptor(SafetyClassification safetyClassification,
                                                          const boost::optional<CodedValue>& type,
                                                          const Unit& unit, // NOLINT(modernize-pass-by-value)
                                                          const BodySites& bodySites, // NOLINT(modernize-pass-by-value)
                                                          MetricCategory metricCategory,
                                                          const boost::optional<DerivationMethod>& derivationMethod,
                                                          MetricAvailability metricAvailability,
                                                          boost::optional<Duration> maxMeasurementTime,
                                                          boost::optional<Duration> maxDelayTime,
                                                          boost::optional<Duration> determinationPeriod,
                                                          boost::optional<Duration> lifeTimePeriod,
                                                          boost::optional<Duration> activationDuration,
                                                          const Relations& relations, // NOLINT(modernize-pass-by-value)
                                                          ExtensionTypes&& extensions) :
        AbstractDescriptor(safetyClassification, type, std::move(extensions)),
        m_unit(unit),
        m_bodySites(bodySites),
        m_metricCategory(metricCategory),
        m_derivationMethod(derivationMethod),
        m_metricAvailability(metricAvailability),
        m_maxMeasurementTime(std::move(maxMeasurementTime)),
        m_maxDelayTime(std::move(maxDelayTime)),
        m_determinationPeriod(std::move(determinationPeriod)),
        m_lifeTimePeriod(std::move(lifeTimePeriod)),
        m_activationDuration(std::move(activationDuration)),
        m_relations(relations)
{
}

inline const boost::optional<Duration>& AbstractMetricDescriptor::activationDuration() const
{
    return m_activationDuration;
}

inline const boost::optional<Duration>& AbstractMetricDescriptor::maxMeasurementTime() const
{
    return m_maxMeasurementTime;
}

inline const boost::optional<Duration>& AbstractMetricDescriptor::lifeTimePeriod() const
{
    return m_lifeTimePeriod;
}

inline const Unit& AbstractMetricDescriptor::unit() const
{
    return m_unit;
}

inline const BodySites& AbstractMetricDescriptor::bodySites() const
{
    return m_bodySites;
}

inline MetricCategory AbstractMetricDescriptor::metricCategory() const
{
    return m_metricCategory;
}

inline const boost::optional<DerivationMethod>& AbstractMetricDescriptor::derivationMethod() const
{
    return m_derivationMethod;
}

inline MetricAvailability AbstractMetricDescriptor::metricAvailability() const
{
    return m_metricAvailability;
}

inline const boost::optional<Duration>& AbstractMetricDescriptor::maxDelayTime() const
{
    return m_maxDelayTime;
}

inline const boost::optional<Duration>& AbstractMetricDescriptor::determinationPeriod() const
{
    return m_determinationPeriod;
}

inline const Relations& AbstractMetricDescriptor::relations() const
{
    return m_relations;
}

} /* namespace Mdib */
} /* namespace DFL */
