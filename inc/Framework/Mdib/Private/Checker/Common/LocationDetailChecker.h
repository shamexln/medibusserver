#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks validity of \ref DFL::Mdib::LocationDetail.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1257 [PTSR.25209 .. OSF.1812 .. SDC.9.4.1.3]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:LocationContextState/pm:LocationDetail includes non-empty values for \@PoC, \@Facility and \@Bed.
 *
 * @ingroup Mdib
 */
class LocationDetailChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
