#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

#include <set>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Consistency check for inferred ensemble context data.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1131 [PTSR.30595 .. OSF.15620 .. BPKP.873]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * an associated pm:EnsembleContextState (\@ContextAssociation = Assoc) is only updated to disassociated (\@ContextAssociation = Dis)
 * when the pm:AbstractContextState from which it infers is not associated (\@ContextAssociation <> Assoc).
 *
 * Note: This implies that the \@BindingMdibVersion of the inferred
 * pm:EnsembleContextState must always be greater than or equal to the
 * \@BindingMdibVersion of the pm:AbstractContextState from which it is
 * inferred.
 * In case an ensemble context descriptors infers location or patient data the
 * pm:EnsembleContextDescriptor/pm:Type/\@Code is set to
 * MDC_IDT_ENSEMBLE_LOCATION_INFERRED or MDC_IDT_ENSEMBLE_PATIENT_INFERRED.
 *
 * S32_SRS_1130 [PTSR.30594 .. OSF.15619 .. BPKP.Draft.877]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if an inferred pm:EnsembleContextState's \@ContextAssociation = Assoc,
 * then the context state that infers the pm:EnsembleContextState contains at least one pm:Validator element.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP InferredEnsembleContextChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            const MdibTreeStore& mdibTreeStore,
            const MdibChangeSet& changes) override;

    private:
        std::set<EnsembleContextIndicatorHandle> m_inferredPatient;
        std::set<EnsembleContextIndicatorHandle> m_inferredLocation;

        CheckerResult checkAllEnsembleStates(const Mdib& mdib,
                                             const MdibChangeSet& changes,
                                             MdibChangeType changeType);
        CheckerResult checkEnsembleState(const Mdib& mdib,
                                         const MdibChangeSet& changes,
                                         MdibChangeType changeType,
                                         const EnsembleContext& entity);
};

}
