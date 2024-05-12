#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

#include <set>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Consistency check for binding version data.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1199 [PTSR.31879 .. OSF.15353 .. BPKP.Draft.1636 / SDC.R0013]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractContextState/\@ContextAssociation = Assoc,
 * then the pm:AbstractContextState provides \@BindingMdibVersion and \@BindingStartTime.
 *
 * S32_SRS_1200 [PTSR.31880 .. OSF.16354 .. BPKP.Draft.1637]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractContextState/\@ContextAssociation = Assoc,
 * then the pm:AbstractContextState does not provide \@UnbindingMdibVersion and \@BindingEndTime.
 *
 * S32_SRS_1201 [PTSR.31881 .. OSF.16355 .. BPKP.Draft.1638 / SDC.R0072 / SDC.R0013]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractContextState/\@ContextAssociation = Dis,
 * then the pm:AbstractContextState provides \@BindingMdibVersion, \@BindingStartTime, \@UnbindingMdibVersion, and \@BindingEndTime.
 *
 * S32_SRS_1202 [PTSR.31882 .. OSF.16356 .. BPKP.Draft.1639]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractContextState/\@ContextAssociation = Pre,
 * then the pm:AbstractContextState does not provide \@BindingMdibVersion, \@BindingStartTime, \@UnbindingMdibVersion, and \@BindingEndTime.
 *
 * Overview of all checks implemented:
 * If NotAssociated, then BindingMdibVersion, BindingStartTime, UnbindingMdibVersion or BindingEndTime must not be set.
 * If PreAssociated, then BindingMdibVersion, BindingStartTime, UnbindingMdibVersion or BindingEndTime must not be set.
 *
 * If Associated, then BindingMdibVersion and BindingStartTime must be set.
 * If Associated, then UnbindingMdibVersion and BindingEndTime must not be set.
 * When transitioning to Associated, BindingMdibVersion must be set to the next MdibVersion. When BindingMdibVersion is not set, it will be set to the correct version by the @ref DFL::Mdib::Impl::PlugIn::BindingVersionModifier "Modifier".
 * When transitioning to Associated, BindingStartTime must be set. When BindingStartTime is not set, it will be set to the current time by the @ref DFL::Mdib::Impl::PlugIn::BindingVersionModifier "Modifier".
 *
 * If Disassociated, then BindingMdibVersion, BindingStartTime, UnbindingMdibVersion and BindingEndTime must be set.
 * When transitioning to Disassociated, UnbindingMdibVersion must be set to the next MdibVersion. When UnbindingMdibVersion is not set, it will be set to the correct version by the @ref DFL::Mdib::Impl::PlugIn::BindingVersionModifier "Modifier".
 * When transitioning to Disassociated, BindingEndTime must be set. When BindingEndTime is not set, it will be set to the current time by the @ref DFL::Mdib::Impl::PlugIn::BindingVersionModifier "Modifier".
 *
 * BindingMdibVersion can only be inserted in the transition to Associated.
 * BindingMdibVersion can only be cleared in the transition to or when PreAssociated or NotAssociated.
 * BindingMdibVersion can only be updated in the transition to Associated.
 *
 * BindingStartTime can only be inserted in the transition to Associated.
 * BindingStartTime can only be cleared in the transition to or when PreAssociated or NotAssociated.
 * BindingStartTime can only be updated in the transition to Associated.
 *
 * UnbindingMdibVersion can only be inserted in the transition to Disassociated.
 * UnbindingMdibVersion can only be cleared in the transition to or when Associated, PreAssociated or NotAssociated.
 * UnbindingMdibVersion can only be updated in the transition to Disassociated.
 *
 * BindingEndTime can only be inserted in the transition to Disassociated.
 * BindingEndTime can only be cleared in the transition to or when Associated, PreAssociated or NotAssociated.
 * BindingEndTime can only be updated in the transition to Disassociated.
 *
 * If BindingMdibVersion < UnbindingMdibVersion, then BindingStartTime <= BindingEndTime.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP BindingVersionChecker: public Checker
{
public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            const MdibTreeStore& mdibTreeStore,
            const MdibChangeSet& changes) override;
};

}
