#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Alert/AbstractAlertState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionKind.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionPresence.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionPriority.h>
#include <Framework/Mdib/Public/Model/Duration.h>
#include <Framework/Mdib/Public/Model/SafetyClassification.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>

#include <boost/optional.hpp>

#include <cstdint>
#include <memory>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct RankTag;
}

/**
 * @brief Allows finer distinction of \ref AlertConditionPriority "alert condition priorities".
 * @details A ranking is a relationship between a set of items such that,
 * for any two items, the first is either "ranked higher than",
 * "ranked lower than" or "ranked equal to" the second.
 * @ingroup Mdib
 */
using Rank = DFL::StrongTypedef<int32_t, Impl::RankTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/*!
 * @brief Common base for \ref AlertConditionState and \ref LimitAlertConditionState.
 * @ingroup Mdib
 */
class AbstractAlertConditionState: public AbstractAlertState
{
    DFL_MDIB_IMMUTABLE(AbstractAlertConditionState)

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AlertConditionState::actualConditionGenerationDelay() "Actual condition generation delay" to none
         * - \ref AlertConditionState::actualPriority() "Actual priority" to none
         * - \ref AlertConditionState::rank() "Rank" to none
         * - \ref AlertConditionState::presence() "Alert condition presence" to \ref AlertConditionPresence::NotPresent "not present"
         * - \ref AlertConditionState::determinationTime() "Determination time" to none
         *
         * \note Also applies defaults from \ref AbstractAlertState.
         */
        AbstractAlertConditionState() = default;

        /**
         * @brief Full constructor.
         */
        AbstractAlertConditionState(AlertActivation activationState,
                            boost::optional<Duration> actualConditionGenerationDelay,
                            const boost::optional<AlertConditionPriority>& actualPriority,
                            boost::optional<Rank> rank,
                            AlertConditionPresence presence,
                            boost::optional<Timestamp> determinationTime,
                            ExtensionTypes extensions = ExtensionTypes{ });

        ~AbstractAlertConditionState() = default;

    public:
        /**
         * @brief Overrides \ref AlertConditionDescriptor::defaultConditionGenerationDelay.
         */
        const boost::optional<Duration>& actualConditionGenerationDelay() const;

        /**
         * @brief Alert condition presence.
         *
         * ###Note on changing the presence of an alert condition
         * @ref AlertSystem's state has 2 fields that represent the presence of it's alert conditions. A change in condition's
         * presence has to be reflected in this @ref AlertSystemState properties.
         *
         * See: @ref AlertSystemState::presentPhysiologicalAlarmConditions(), @ref AlertSystemState::presentTechnicalAlarmConditions()
         *
         * There is helper functionality that can update these lists before writing a changeset into a Mdib.
         *
         * See: @ref AlertHelper::setAlertSystemConditionPresenceLists()
         */
        AlertConditionPresence presence() const;

        /**
         * @brief   Current priority of the alert condition that has been modified by an escalation or deescalation process.
         * @details If the actual priority is present in an alert condition state, the priority of the related
         *          alert condition descriptor does not reflect the current severity of the potential or actual hazard
         *          that exists if the alert condition is present. If there is no actual priority given, the value is
         *          \c boost::none.
         */
        boost::optional<AlertConditionPriority> actualPriority() const;

        /**
         * @brief   The rank is an optional attribute allowing finer distinction of alert condition priorities.
         * @details If there is no rank available, the value is \c boost::none.
         */
        boost::optional<Rank> rank() const;

        /**
         * @brief  Timepoint when the alert condition has changed its presence the last time.
         * @return If not available, the value is set to \c boost::none.
         */
        const boost::optional<Timestamp>& determinationTime() const;

    private:
        boost::optional<Duration> m_actualConditionGenerationDelay{};
        boost::optional<AlertConditionPriority> m_actualPriority{};
        boost::optional<Rank> m_rank{};
        AlertConditionPresence m_presence{AlertConditionPresence::NotPresent};
        boost::optional<Timestamp> m_determinationTime{};
};

inline AbstractAlertConditionState::AbstractAlertConditionState(AlertActivation activationState,
                                                boost::optional<Duration> actualConditionGenerationDelay,
                                                const boost::optional<AlertConditionPriority>& actualPriority,
                                                boost::optional<Rank> rank,
                                                AlertConditionPresence presence,
                                                boost::optional<Timestamp> determinationTime,
                                                ExtensionTypes extensions) :
        AbstractAlertState(activationState, std::move(extensions)),
        m_actualConditionGenerationDelay(std::move(actualConditionGenerationDelay)),
        m_actualPriority(actualPriority),
        m_rank(std::move(rank)),
        m_presence(presence),
        m_determinationTime(std::move(determinationTime))
{
}

inline const boost::optional<Duration>& AbstractAlertConditionState::actualConditionGenerationDelay() const
{
    return m_actualConditionGenerationDelay;
}

inline AlertConditionPresence AbstractAlertConditionState::presence() const
{
    return m_presence;
}

inline boost::optional<AlertConditionPriority> AbstractAlertConditionState::actualPriority() const
{
    return m_actualPriority;
}

inline boost::optional<Rank> AbstractAlertConditionState::rank() const
{
    return m_rank;
}

inline const boost::optional<Timestamp>& AbstractAlertConditionState::determinationTime() const
{
    return m_determinationTime;
}
} /* namespace Mdib */
} /* namespace DFL */
