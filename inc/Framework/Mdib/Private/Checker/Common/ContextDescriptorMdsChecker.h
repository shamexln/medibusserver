#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Context descriptors can only be added or removed from the Mdib along with the parent Mds.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1160 [PTSR.24248 .. OSF.1378 .. BICEPS.R0106]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:AbstractContextDescriptor instances are not removed from or added to the MDIB except when the enclosing MDS is removed from or added to the MDIB.
 *
 * @ingroup Mdib
 */
class ContextDescriptorMdsChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
