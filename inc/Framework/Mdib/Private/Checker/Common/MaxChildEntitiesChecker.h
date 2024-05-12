#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checker for maximum child entity rules.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1301:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * the MDIB contains zero or exactly one of the following elements:
 *  - Clock
 *  - SystemContext
 *  - MdsSco
 *  - VmdSco
 *  - MdsAlertSystem
 *  - VmdAlertSystem
 *  - PatientContextDescriptor
 *  - LocationContextDescriptor.
 *
 * This checker enforces these maximum child entity rules.
 *
 * @ingroup Mdib
 */
class MaxChildEntitiesChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
