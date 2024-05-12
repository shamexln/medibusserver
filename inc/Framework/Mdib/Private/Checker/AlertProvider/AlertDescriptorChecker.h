#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks consistency of alert descriptors.
 * @details This checker applies to the Alert Provider role.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1141 [PTSR.30614 .. OSF.15574 .. APKP.Draft.213]:
 * S32 shall provide a CHECKER for ALERT PROVIDERs to verify that the following condition holds true:
 * when pm:AlertConditionDescriptor/\@Priority is updated, pm:AlertConditionState/\@Presence = false
 * and all related pm:AlertSignalState elements are off or acknowledged (pm:AlertSignalState/\@Presence in { Off, Ack }).
 *
 * Note:
 * the change containing the priority change is not supposed to contain changes of the relation between the condition and its signals,
 * i.e. changes of AlertSignal/ConditionSignaled or inserting/removing signals of the condition.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP AlertDescriptorChecker : public Checker
{
public:
    CheckerResult check(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        const MdibTreeStore& mdibTreeStore,
        const MdibChangeSet& changes) override;
};

}
