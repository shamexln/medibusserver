#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks for required type information.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1302 [PTSR.26309 .. OSF.1951 .. SDC.R0080]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:AbstractDesriptor/pm:Type is defined for ELEMENTs of the following TYPEs
 * or any TYPE derived from the listed TYPEs if used:
 *  - pm:AbstractComplexDeviceComponentDescriptor
 *  - pm:ChannelDescriptor
 *  - pm:AbstractOperationDescriptor
 *  - pm:AlertConditionDescriptor
 *  - pm:AbstractMetricDescriptor.
 *
 * NOTE—R0080 defines that certain optional pm:AbstractDescriptor/pm:Type are
 * mandatory to ease semantic interpretation of the ELEMENTs.
 *
 * @ingroup Mdib
 */
class TypeChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
