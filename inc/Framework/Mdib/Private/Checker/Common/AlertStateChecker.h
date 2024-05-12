#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{
/**
 * @brief Checks consistency of Alert States.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_846 [PTSR.24406 .. OSF.1405 .. BICEPS.R0116]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * The value of pm:AlertSystemState/\@ActivationState results in a value of \@ActivationState
 * for all child pm:AlertConditionState and pm:AlertSignalState according to BICEPS/Table 8.
 *
 * S32_SRS_848 [PTSR.24408 .. OSF.1407 .. BICEPS.R0029]
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AlertConditionState/\@Presence switches to “true”,
 * then pm:AlertConditionState/\@ActivationState=On
 * and pm:AlertSystemState/\@ActivationState=On for the parent AlertSystem.
 *
 * S32_SRS_1290:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AlertConditionState/\@Presence changes then pm:AlertConditionState/\@DeterminationTime must be provided.
 *
 * S32_SRS_1291 [PTSR.24410 .. OSF.1409 .. BICEPS.R0113]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AlertConditionState/\@Presence is true for any physiological alarm condition or technical alarm condition,
 * then the HANDLE of the corresponding ALERT CONDITION is added to
 * pm:AlertSystemState/\@PresentPhysiologicalAlarmConditions or pm:AlertSystemState/\@PresentTechnicalAlarmConditions,
 * respectively.
 *
 * S32_SRS_1292:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AlertSystemState/\@SelfCheckCount changes then pm:AlertSystemState/\@LastSelfCheck must be provided.
 *
 * S32_SRS_1293:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * SDC SERVICE PROVIDER can not reset pm:AlertSystemState/\@SelfCheckCount.
 *
 * S32_SRS_1294:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * a LimitAlertConditionState with /\@ActivationState not equal to Off provides
 * Limits/Upper (if the condition type is MDC_EVT_HI_GT_LIM) or
 * Limits/Lower (if the condition type is MDC_EVT_LO_LT_LIM or MDC_EVT_DESAT).
 *
 * S32_SRS_1295 [PTSR.24411 .. OSF.1410 .. BICEPS.R0139]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * a change to pm:AlertConditionState/\@Presence of an ALERT CONDITION is always delivered together with an ALERT SYSTEM
 * state update within one msg:AbstractAlertReport MESSAGE.
 *
 * @ingroup Mdib
 */
class AlertStateChecker : public Checker
{
public:
    CheckerResult check(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        const MdibTreeStore& mdibTreeStore,
        const MdibChangeSet& changes) override;
};

}
