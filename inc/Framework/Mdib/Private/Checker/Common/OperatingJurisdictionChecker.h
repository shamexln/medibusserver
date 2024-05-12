#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{
/**
 * @brief Checks if [Mds/Vmd]StateOperatingJurisdiction is contained in [Mds/Vmd]Descriptor/ApprovedJurisdiction.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_905 [PTSR.28015 .. OSF.15175 .. BICEPS.B.284.Documentation(MdsState/OperatingJurisdiction) (REPLACEMENT REQ)]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:MdsState/pm:OperatingJurisdiction is contained in pm:MdsDescriptor/pm:ApprovedJurisdictions.
 *
 * S32_SRS_907 [PTSR.27999 .. OSF.15199 .. BICEPS.B.402.Documentation(VmdState/OperatingJurisdiction) (REPLACEMENT REQ)]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:VmdState/pm:OperatingJurisdiction is contained in pm:VmdDescriptor/pm:ApprovedJurisdictions.
 *
 * Note:
 * According to a comment in Doors, the original BICEPS Requirement is not strict enough
 * and allows reaching undesirable states. The replacement requirement forbids that.
 * Further note that the S32 Requirement is even more strict than the BICEPS, OSF and Modular Requirement.
 * The latter only require that there is no OperatingJurisdiction in case there is no ApprovedJurisdiction.
 *
 * @ingroup Mdib
 */
class OperatingJurisdictionChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
