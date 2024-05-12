#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn::AlertProvider
{


/**
 * @brief Checks consistency of Alert States.
 * @details This checker applies to the Alert Provider role (* @todo PCSWORK-5822 ModReqs 29805, 29806 changed, 25229 deleted *).
 *
 * It covers the following requirements:
 *
 * S32_SRS_1187 [PTSR.30612 .. OSF.15575 .. APKP.Draft.363]:
 * S32 shall provide a CHECKER for ALERT PROVIDERs to verify that the following condition holds true:
 * pm:AlertSystemState/\@ActivationState != Psd
 *
 * S32_SRS_1241 [PTSR.29805 .. OSF.15364 .. APKP.Draft.366]:
 * S32 shall provide a CHECKER for ALERT PROVIDERs to verify that the following
 * conditions hold true:
 * - if for a pm:AlertSignalState \@ActivationState = Off,
 *   then \@Presence = Off.
 * - if for a pm:AlertSignalState \@ActivationState = Off,
 *   then \@Presence = Off exactly one MDIB version before.
 *
 * S32_SRS_1235 [PTSR.29806 .. OSF.15365 .. APKP.Draft.367]:
 * S32 shall provide a CHECKER for ALERT PROVIDERs to verify that the following
 * conditions hold true:
 * - if for a pm:AlertConditionState \@ActivationState in {Off, Psd},
 *   then \@Presence = false.
 * - if for a pm:AlertConditionState \@ActivationState in {Off, Psd},
 *   then \@Presence = false exactly one MDIB version before.
 *
 * S32_SRS_1262 [PTSR.31570 .. OSF.16201 .. APKP.Draft.210]:
 * S32 shall provide a CHECKER for ALERT PROVIDERs to verify that the following condition holds true:
 * if pm:AlertConditionState/\@Presence = false, then pm:AlertConditionState/ext:Extension does not include a pme:PriorityChange element.
 * 
 * @ingroup Mdib
 */
class AlertStateChecker : public Checker
{
public:
    CheckerResult check(MdibChangeType changeType,
                        const NotNull<MdibSharedPtr>& mdib,
                        const MdibTreeStore& mdibTreeStore,
                        const MdibChangeSet& changes) override;
};

}