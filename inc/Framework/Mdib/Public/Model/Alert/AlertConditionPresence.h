#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL::Mdib
{
/**
 * @brief   Represents an alert condition's presence.
 * @details Initialization values provide a Hamming distance of 12
 * between Present/Not Present to allow for better corruption detection
 *
 * @ingroup Mdib
 */
enum class AlertConditionPresence
{
    // We are using value with a large hamming distance to allow detection of
    // bit flips.

    /**
     * @brief Designates that the alert condition has been detected.
     */
    Present = 0xABCD,

    /**
     * @brief Designates that the alert condition has not been detected.
     */
    NotPresent = 0xDCBA
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertConditionPresence, (Present)(NotPresent))

}
