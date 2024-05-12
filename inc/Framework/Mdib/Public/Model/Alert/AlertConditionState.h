#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AbstractAlertConditionState.h>

namespace DFL
{
namespace Mdib
{
/*!
 * @brief AlertConditionState for non-limit conditions.
 * @ingroup Mdib
 */
class AlertConditionState: public AbstractAlertConditionState
{
    DFL_MDIB_IMMUTABLE(AlertConditionState)

    public:
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
        AlertConditionState() = default;

        /**
         * @brief Full constructor.
         */
        AlertConditionState(AlertActivation activationState,
                            boost::optional<Duration> actualConditionGenerationDelay,
                            const boost::optional<AlertConditionPriority>& actualPriority,
                            boost::optional<Rank> rank,
                            AlertConditionPresence presence,
                            boost::optional<Timestamp> determinationTime,
                            ExtensionTypes extensions = ExtensionTypes{ });

};

inline AlertConditionState::AlertConditionState(AlertActivation activationState,
                                                boost::optional<Duration> actualConditionGenerationDelay,
                                                const boost::optional<AlertConditionPriority>& actualPriority,
                                                boost::optional<Rank> rank,
                                                AlertConditionPresence presence,
                                                boost::optional<Timestamp> determinationTime,
                                                ExtensionTypes extensions)
    : AbstractAlertConditionState(activationState,
                                  actualConditionGenerationDelay,
                                  actualPriority,
                                  std::move(rank),
                                  presence,
                                  std::move(determinationTime),
                                  std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref AlertConditionStateSharedPtr for state \ref AlertConditionState.
 * @ingroup Mdib
 */
using AlertConditionStateSharedPtr = SharedPtr<AlertConditionState>;

} /* namespace Mdib */
} /* namespace DFL */
