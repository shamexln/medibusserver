#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checker for activation mode requirements.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_541 [PTSR.24263 .. OSF.1393 .. BICEPS.R0025 (REPLACEMENT REQ)]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:AbstractDeviceComponentState/\@ActivationState = Off if and only if
 * every activation state of the component’s descendants is inactive. Inactive means that
 * every pm:AbstractDeviceComponentState/\@ActivationState is "Off",
 * every pm:AbstractAlertState/\@ActivationState is "Off",
 * every pm:AbstractMetricState/\@ActivationState is "Off",
 * and every pm:AbstractOperationState/\@OperatingMode is "NA" (not available).
 *
 * Note:
 * MetricStates are missing in the original BICEPS requirement.
 * This is fixed with the replacement requirement.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP ActivationStateConsistencyChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}