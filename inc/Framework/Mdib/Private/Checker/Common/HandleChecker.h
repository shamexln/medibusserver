#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks validity of \ref Handle member in entity types.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1303:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * the handles of pm:AbstractOperationDescriptor/\@OperationTarget are valid.
 *
 * @ingroup Mdib
 */
class HandleChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
