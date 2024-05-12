#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{
/**
 * @brief Checks identifications of a \ref DFL::Mdib::PatientContext
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1142 [PTSR.21784 .. OSF.321]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:PatientContextState/\@ContextAssociation = Assoc,
 * then the pm:PatientContextStat contains at least one pm:Identification element with
 * \@Root = 1.3.6.1.4.1.3592.2.51 and \@Extension matching a UUID in accordance to
 * ITU-T Rec. X.667 | ISO/IEC 9834-8:2005, in hex format.
 *
 * @ingroup Mdib
 */
class DraegerPatientIdentificationChecker : public Checker
{
public:
    CheckerResult check(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        const MdibTreeStore& mdibTreeStore,
        const MdibChangeSet& changes) override;
};
}
