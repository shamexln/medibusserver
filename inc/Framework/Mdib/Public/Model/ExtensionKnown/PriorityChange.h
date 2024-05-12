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
 * @brief Timestamp for changed of AlertConditionState/\@ActualPriority.
 * @details
 * This information might be required by SDC ALERT CONSUMERs to determine the
 * point in time the priority change happened in comparison to the
 * pm:AlertConditionState/\@DeterminationTime used to determine the point in
 * time the pm:AlertConditionState/\@Presence changed. An SDC ALERT PROVIDER
 * shall only use pme:PriorityChange when pm:AlertConditionState/\@Presence =
 * True.
 *
 * @note An SDC ALERT PROVIDER shall set \@ext:MustUnderstand = "false".
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP PriorityChange
{
public:
    /**
     * @brief Constructor with all members.
     */
    explicit PriorityChange(Timestamp determinationTime);

    /**
     * @brief Time of priority change.
     * @details
     * It is set whenever the SDC ALERT PROVIDER uses
     * pm:AlertConditionState/\@ActualPriority while
     * pm:AlertConditionState/\@Presence = True.
     */
    Timestamp determinationTime() const noexcept;

private:
    Timestamp m_determinationTime;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const PriorityChange& lhs,
                                const PriorityChange& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const PriorityChange& lhs,
                                const PriorityChange& rhs) noexcept;

}
}
}
