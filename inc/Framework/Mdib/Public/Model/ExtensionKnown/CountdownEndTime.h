#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>

namespace DFL
{
namespace Mdib
{
namespace Ext
{
/**
 * @brief Used for special situations that when the time that an inactivation
 * state ends can no longer be determined from the \@DeterminationTime and
 * \@InvocationEffectiveTimeout of the belonging pm:AlertConditionState and
 * pm:ActivateOperationState.
 *
 * @details
 * An SDC ALERT PROVIDER shall set it to the latest time that an alert signal
 * inactivation state will end automatically.
 *
 * An example it the audio pause function with a count down when the
 * inactivation will end automatically.
 *
 * @note An SDC ALERT PROVIDER shall set \@ext:MustUnderstand = "true".
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CountdownEndTime
{
public:
    /**
     * @brief Constructor with all members.
     */
    explicit CountdownEndTime(Timestamp endTime) noexcept;

    /**
     * @brief Latest time that an alert signal inactivation state will end
     * automatically.
     */
    Timestamp endTime() const noexcept;

private:
    Timestamp m_endTime;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const CountdownEndTime& lhs,
                                const CountdownEndTime& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const CountdownEndTime& lhs,
                                const CountdownEndTime& rhs) noexcept;

}
}
}
