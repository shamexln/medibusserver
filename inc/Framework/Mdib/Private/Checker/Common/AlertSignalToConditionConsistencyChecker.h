#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{
/**
 * @brief Checks \ref AlertSignalDescriptor::conditionSignaledHandle() to validate
 * that the referenced \ref AlertCondition exists and is contained by an appropriate \ref AlertSystem
 * according to BICEPS
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1299 [PTSR.34085 .. OSF.16731 .. BICEPS.B.103.Documentation(AlertSignalDescriptor/\@ConditionSignaled)]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * the ALERT CONDITION signaled by an AlertSignalDescriptor/ConditionSignaled is in the same ALERT SYSTEM or in an
 * ALERT SYSTEM in the bpkp:BICEPS CONTAINMENT SUBTREE of the ALERT SIGNALs ALERT SYSTEM.
 *
 * Note:
 * This \ref Checker validates that any \ref AlertCondition that is removed is not still referenced by an \ref AlertSignal.
 * It also checks that any \ref AlertSignal that is inserted or updated will not reference an
 * \ref AlertCondition that does not exist, or is not in an appropriate \ref AlertSystem.
 *
 * \remark Example from the standard: assume an \ref Mds possesses two \ref Vmd "Vmds" and an \ref AlertSystem A,
 * and each of these \ref Vmd "Vmds" possess itself an \ref AlertSystem (B and C). An \ref AlertSignal from the
 * \ref AlertSystem A of the \ref Mds is allowed to reference an \ref AlertCondition from the \ref AlertSystem "AlertSystems"
 * A, B and C. In contrast to this an \ref AlertSignal from the \ref AlertSystem B is allowed to reference only
 * \ref AlertCondition "AlertConditions" from the \ref AlertSystem B and not from the \ref AlertSystem A or C.
 *
 * @ingroup Mdib
 */
class AlertSignalToConditionConsistencyChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            const MdibTreeStore& mdibTreeStore,
            const MdibChangeSet& changes) override;
};
}
