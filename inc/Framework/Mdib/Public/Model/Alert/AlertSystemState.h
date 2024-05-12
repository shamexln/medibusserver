#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AbstractAlertState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertActivation.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>

#include <boost/optional.hpp>

#include <cstdint>
#include <utility>

namespace DFL::Mdib
{
namespace Impl
{
struct SelfCheckCountTag;
}

/**
 * @brief Number of self checks performed.
 * @ingroup Mdib
 */
using SelfCheckCount = DFL::StrongTypedef<int64_t,
                                          Impl::SelfCheckCountTag,
                                          DFL::Skill::Incrementable,
                                          DFL::Skill::TotallyOrdered,
                                          DFL::Skill::Streamable,
                                          DFL::Skill::BoostSerializable>;

/**
 * @brief Contains the dynamic part of an \ref AlertSystem.
 * @ingroup Mdib
 */
class AlertSystemState: public AbstractAlertState
{
    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AlertSystemState::lastSelfCheck() "Last self check" to none
         * - \ref AlertSystemState::selfCheckCount() "Self check count" to none
         * - \ref AlertSystemState::presentPhysiologicalAlarmConditions() "Present physiological alarm conditions" to empty sequence
         * - \ref AlertSystemState::presentTechnicalAlarmConditions() "Present technical alarm conditions" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractAlertState.
         */
        AlertSystemState() = default;

        /**
         * @brief Full constructor.
         */
        AlertSystemState(AlertActivation activationState,
                         boost::optional<Timestamp> lastSelfCheck,
                         boost::optional<SelfCheckCount> selfCheckCount,
                         HandleSet presentPhysiologicalAlarmConditions,
                         HandleSet presentTechnicalAlarmConditions,
                         ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Timepoint when the \ref AlertSystem has performed a self check the last time.
         * @details LastSelfCheck shall be updated on every \ref AlertSystemDescriptor::selfCheckPeriod().
         * @return Timestamp of last check or \c boost::none if none have occurred.
         */
        [[nodiscard]] const boost::optional<Timestamp>& lastSelfCheck() const;

        /**
         * @brief Number of self checks performed.
         * @details This specification does not prescribe the origin of the value, i.e., whether the counter is incremented
         * since the last boot or whether the counter represents the self checks ever performed.
         * @return The self check count or \c boost::none if no self check count is available.
         */
        [[nodiscard]] boost::optional<SelfCheckCount> selfCheckCount() const;

        /**
         * @brief @ref Handle references to the present physiological alarm conditions that have been determined by the \ref AlertSystem.
         *
         * @see AlertCondition::presence()
         */
        [[nodiscard]] const HandleSet& presentPhysiologicalAlarmConditions() const;

        /**
         * @brief @ref Handle references to the present technical alarm conditions that have been determined by the \ref AlertSystem.
         *
         * @see AlertCondition::presence()
         */
        [[nodiscard]] const HandleSet& presentTechnicalAlarmConditions() const;

    private:
        boost::optional<Timestamp> m_lastSelfCheck{};
        boost::optional<SelfCheckCount> m_selfCheckCount{};
        HandleSet m_presentPhysiologicalAlarmConditions{};
        HandleSet m_presentTechnicalAlarmConditions{};
};

inline AlertSystemState::AlertSystemState(AlertActivation activationState,
                                          boost::optional<Timestamp> lastSelfCheck,
                                          boost::optional<SelfCheckCount> selfCheckCount,
                                          HandleSet presentPhysiologicalAlarmConditions,
                                          HandleSet presentTechnicalAlarmConditions,
                                          ExtensionTypes extensions) :
        AbstractAlertState(activationState, std::move(extensions)),
        m_lastSelfCheck(std::move(lastSelfCheck)),
        m_selfCheckCount(std::move(selfCheckCount)),
        m_presentPhysiologicalAlarmConditions(std::move(presentPhysiologicalAlarmConditions)),
        m_presentTechnicalAlarmConditions(std::move(presentTechnicalAlarmConditions))
{
}

inline const boost::optional<Timestamp>& AlertSystemState::lastSelfCheck() const
{
    return m_lastSelfCheck;
}

inline boost::optional<SelfCheckCount> AlertSystemState::selfCheckCount() const
{
    return m_selfCheckCount;
}

inline const HandleSet& AlertSystemState::presentPhysiologicalAlarmConditions() const
{
    return m_presentPhysiologicalAlarmConditions;
}

inline const HandleSet& AlertSystemState::presentTechnicalAlarmConditions() const
{
    return m_presentTechnicalAlarmConditions;
}

/**
 * @brief Definition of shared pointer type \ref AlertSystemStateSharedPtr for state \ref AlertSystemState.
 * @ingroup Mdib
 */
using AlertSystemStateSharedPtr = SharedPtr<AlertSystemState>;

}
