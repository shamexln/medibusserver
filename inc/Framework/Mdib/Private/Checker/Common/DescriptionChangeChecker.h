#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Check description changes.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1254 [PTSR.31004 .. OSF.16036]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * a description modification change set does not include two or more entities that have the same handle.
 *
 * Note:
 * This checks the same for context states which are the multistates - which in the change set also have insert vs. update semantics. With
 * this checker a context state can be only either inserted or updated.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP DescriptionChangeChecker : public Checker
{
public:
    CheckerResult check(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        const MdibTreeStore& mdibTreeStore,
        const MdibChangeSet& changes) override;
};
}
