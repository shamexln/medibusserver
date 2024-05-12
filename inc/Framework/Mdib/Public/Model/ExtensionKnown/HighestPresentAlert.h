#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>

namespace DFL::Mdib::Ext
{

/**
 * @brief Extension for an Mds AlertSystemState to add highest present alert
 * signal information.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP HighestPresentAlert
{
public:
    /**
     * @brief Construct a new Highest Present Alert object.
     *
     * @param highestPresentAlertSignal Handle of the highest visual alert
     * signal (slot = 0).
     * @param alertPriority Priority of the signaled condition as "color"
     * string. Values are "Red", "Yellow", "Cyan", and "Grey" for \ref
     * DFL::Mdib::AlertConditionPriority High, Medium, Low, and None.
     * The colors derived from 60601-1-8 Table 2 (Characteristics of alarm
     * indicator lights).
     * In case there is no visual alert signal present the value is "NoSignal"
     */
    HighestPresentAlert(MdsAlertSignalHandle highestPresentAlertSignal,
                        std::string alertPriority);

    /**
     * @brief Creates an instance without a handle (NoSignal priority).
     */
    static HighestPresentAlert noSignal();

    /// @brief Highest present visual signal (slot = 0).
    const MdsAlertSignalHandle&
    handle() const noexcept;

    /// @brief Condition priority of highest present visual signal.
    const std::string& priority() const noexcept;

private:
    MdsAlertSignalHandle m_handle;
    std::string m_priority;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const HighestPresentAlert& lhs,
                                const HighestPresentAlert& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const HighestPresentAlert& lhs,
                                const HighestPresentAlert& rhs) noexcept;
}
