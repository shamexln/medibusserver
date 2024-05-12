#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{
/**
 * @brief Checker for maximum one MDS per MDIB.
 *
 * @details
 * This checker applies to all roles.
 *
 * It covers the following Requirement:
 *
 * S32_SRS_1282 [PTSR.30993 .. OSF.16054]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the
 * following condition holds true: the MDIB contains zero or exactly one MDS.
 *
 * @ingroup Mdib
 */
class MdsCardinalityChecker: public Checker
{
public:
    CheckerResult check(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr> &mdib,
        const MdibTreeStore &mdibTreeStore,
        const MdibChangeSet &changes) override;
};
}
