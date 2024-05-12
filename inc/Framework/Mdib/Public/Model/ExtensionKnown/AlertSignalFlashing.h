#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Handle.h>

namespace DFL
{
namespace Mdib
{
namespace Ext
{
/**
 * @brief
 * @details
 * Is used by an SDC ALERT PROVIDER in order to allow an SDC ALERT CONSUMER to
 * use this list for visualizing its own parameter boxes. If this extension is
 * not given it has to be assumed that the default flashing behavior can be used
 * by the SDC ALERT CONSUMER (i.e. flashing when a
 * pm:AlertSignalState/\@Presence = true, not flashing when
 * pm:AlertSignalState/\@Presence = false, during Audio Pause only flash for
 * "new" signals).
 *
 * This list is also required, if accurate flashing states for SDC ALERT
 * CONSUMERs that join while Audio Pause situations are already active are
 * needed.
 *
 * Example usage in code:
 * @snippet Mdib/Test/UnitTest/TestParticipantModelExtensions.cpp AlertSignalFlashingUsage
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP AlertSignalFlashing
{
public:
    /**
     * @brief Empty list of handles.
     */
    AlertSignalFlashing() = default;

    /**
     * @brief Constructor with all members.
     */
    explicit AlertSignalFlashing(Handles flashingSignals);

    /**
     * @brief All Handles of all visual alert signals of the PoC Medical Device
     * that currently contribute to the flashing of its parameter boxes.
     */
    const Handles& flashingSignals() const noexcept;

private:
    Handles m_flashingSignals;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const AlertSignalFlashing& lhs,
                                const AlertSignalFlashing& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const AlertSignalFlashing& lhs,
                                const AlertSignalFlashing& rhs) noexcept;

}
}
}
