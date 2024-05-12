#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{
/**
 * @brief Checks different requirements for associated context states.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_871 [PTSR.24260 .. OSF.1390 .. BICEPS.R0124]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * There is only one pm:PatientContextState with \@ContextAssociation=Assoc.
 *
 * S32_SRS_872 [PTSR.24261 .. OSF.1391 .. BICEPS.R0133]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * There is only one pm:LocationContextState with \@ContextAssociation=Assoc.
 *
 * S32_SRS_1106 [PTSR.30573 .. OSF.15600 .. BPKP.Draft.1304]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractContextState/\@ContextAssociation = Assoc, then pm:AbstractContextState/pm:Identification contains at least one element.
 *
 * S32_SRS_1129 [PTSR.30586 .. OSF.15614 .. BPKP.Draft.874]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:EnsembleContextState/\@ContextAssociation = Assoc,
 * then pm:EnsembleContextState contains at least one pm:Validator element.
 *
 * S32_SRS_1155 [PTSR.30848 .. OSF.15724 .. BPKP.Draft.1470]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * \@ContextAssociation transitions are changed according to the state diagram shown in S32_SRS_1157.
 *
 * S32_SRS_1158 [PTSR.30850 .. OSF.15726 .. BPKP.Draft.1461]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following conditions hold true:
 * - while pm:AbstractContextState/\@ContextAssociation = Assoc, no element is removed from pm:AbstractContextState/pm:Identification
 * - while pm:AbstractContextState/\@ContextAssociation = Assoc, no element of pm:AbstractContextState/pm:Identification is changed
 *
 * S32_SRS_1162 [PTSR.31155 .. OSF.16126 .. BICEPS.6487]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if a context state's \@ContextAssociation <> No, then the context state is not removed from the MDIB.
 *
 * @ingroup Mdib
 */
class ContextStateChecker : public Checker
{
public:
    CheckerResult check(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        const MdibTreeStore& mdibTreeStore,
        const MdibChangeSet& changes) override;
};
}
