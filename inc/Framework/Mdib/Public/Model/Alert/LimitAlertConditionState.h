#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionMonitoredLimits.h>
#include <Framework/Mdib/Public/Model/Alert/AbstractAlertConditionState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertActivation.h>
#include <Framework/Mdib/Public/Model/Range.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief The volatile part a limit alert condition.
 * @ingroup Mdib
 */
class LimitAlertConditionState: public AbstractAlertConditionState
{
    DFL_MDIB_IMMUTABLE(LimitAlertConditionState)

    public:

        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref LimitAlertConditionState::autoLimitActivationState() "Auto limit activation state" to none
         * - \ref LimitAlertConditionState::monitoredAlertLimits() "Monitored alert limits" to \ref AlertConditionMonitoredLimits::None "none"
         * - \ref LimitAlertConditionState::limits() "Limits" to none
         *
         * \note Also applies defaults from \ref AlertConditionState.
         */
        LimitAlertConditionState() = default;

        /**
         * @brief Constructor.
         */
        LimitAlertConditionState(AlertActivation activationState,
                                 const boost::optional<Duration>& actualConditionGenerationDelay,
                                 const boost::optional<AlertConditionPriority>& actualPriority,
                                 const boost::optional<Rank>& rank,
                                 AlertConditionPresence presence,
                                 const boost::optional<Timestamp>& determinationTime,
                                 const boost::optional<AlertActivation>& autoLimitActivationState,
                                 AlertConditionMonitoredLimits monitoredAlertLimits,
                                 Range limits,
                                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Monitored alert limits of the limit alert condition.
         * @details Note if the \ref AlertConditionState::activationState() attribute is not set to \ref AlertActivation::On, the presence
         * of the limit alert condition is not detected. From a consumer perspective this is equivalent to the case when the
         * \ref AlertConditionState::activationState() is \ref AlertActivation::On and \ref LimitAlertConditionState::monitoredAlertLimits()
         * is \ref AlertConditionMonitoredLimits::None. The difference is that in the latter case the source for the alert condition is still
         * supervised, but the presence flag is not generated even if the limits are violated.
         */
        AlertConditionMonitoredLimits monitoredAlertLimits() const;

        /**
         * @brief Indicates if the limits for the limit alert condition are adjusted automatically.
         * @return State of limit being automatically adjusted or \c boost::none if no auto limit activation state is present.
         */
        boost::optional<AlertActivation> autoLimitActivationState() const;

        /**
         * @brief Limit values of the limit alert condition.
         * @details The unit of the limits in \ref Range is the unit of the referenced \ref AlertCondition.
         * @return The limit range.
         */
        const Range& limits() const;

    private:
        AlertConditionMonitoredLimits m_monitoredAlertLimits{AlertConditionMonitoredLimits::None};
        boost::optional<AlertActivation> m_autoLimitActivationState{};
        Range m_limits{};
};

inline LimitAlertConditionState::LimitAlertConditionState(AlertActivation activationState,
                                                          const boost::optional<Duration>& actualConditionGenerationDelay,
                                                          const boost::optional<AlertConditionPriority>& actualPriority,
                                                          const boost::optional<Rank>& rank,
                                                          AlertConditionPresence presence,
                                                          const boost::optional<Timestamp>& determinationTime,
                                                          const boost::optional<AlertActivation>& autoLimitActivationState,
                                                          AlertConditionMonitoredLimits monitoredAlertLimits,
                                                          Range limits,
                                                          ExtensionTypes extensions) :
        AbstractAlertConditionState(activationState, actualConditionGenerationDelay, actualPriority, rank, presence, determinationTime, std::move(extensions)),
        m_monitoredAlertLimits(monitoredAlertLimits),
        m_autoLimitActivationState(autoLimitActivationState),
        m_limits(std::move(limits))
{
}

inline const Range& LimitAlertConditionState::limits() const
{
    return m_limits;
}

inline boost::optional<AlertActivation> LimitAlertConditionState::autoLimitActivationState() const
{
    return m_autoLimitActivationState;
}

inline AlertConditionMonitoredLimits LimitAlertConditionState::monitoredAlertLimits() const
{
    return m_monitoredAlertLimits;
}

/**
 * @brief Definition of shared pointer type \ref LimitAlertConditionStateSharedPtr for state \ref LimitAlertConditionState.
 * @ingroup Mdib
 */
using LimitAlertConditionStateSharedPtr = SharedPtr<LimitAlertConditionState>;

}
}
