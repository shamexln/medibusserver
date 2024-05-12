#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks validity of \ref DFL::Mdib::InstanceIdentifier root member and
 * existence of an extension for specific roots without null flavors.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1113 [PTSR.30599 .. OSF.15594 .. BPKP.Draft.886]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * the value of pm:InstanceIdentifier/\@Root matches the form scheme ":" hier-part as defined in RFC 2396
 * except for "biceps.uri.unk" and "sdc.ctxt.loc.detail".
 *
 * Note:
 * In other words, no query and fragment part in URLs.
 *
 * S32_SRS_1178 [PTSR.25329 .. OSF.15903 .. CDOID.48]
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that all of the following conditions hold true:
 * pm:InstanceIdentifier/\@Root != urn:oid:1.3.6.1.4.1.3592.2.73.0
 * pm:InstanceIdentifier/\@Root != urn:oid:1.3.6.1.4.1.3592.2.73.1
 * pm:InstanceIdentifier/\@Root != urn:oid:1.3.6.1.4.1.3592.2.73.2
 * pm:InstanceIdentifier/\@Root != urn:oid:1.3.6.1.4.1.3592.2.73.3
 * pm:InstanceIdentifier/\@Root != urn:oid:1.3.6.1.4.1.3592.2.73.4.
 * 
 * S32_SRS_1347 [PTSR.31239 .. OSF.16135 .. BICEPS.B.227.Documentation(InstanceIdentifier/\@Root)]
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:InstanceIdentifier/\@Root != "biceps.uri.unk"
 *
 * S32_SRS_1184 [PTSR.31233 .. OSF.16105]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractContextState/pm:Identification/\@Root = "1.3.6.1.4.1.3592.2.51",
 * then pm:AbstractContextState/pm:Identification/\@Extension is non-empty.
 *
 * S32_SRS_1258 [PTSR.31101 .. OSF.16099]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractContextState/pm:Identification/\@Root = "1.3.6.1.4.1.3592.2.52",
 * then pm:AbstractContextState/pm:Identification/\@Extension is non-empty.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP InstanceIdentifierChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            const MdibTreeStore& mdibTreeStore,
            const MdibChangeSet& changes) override;
};

}
