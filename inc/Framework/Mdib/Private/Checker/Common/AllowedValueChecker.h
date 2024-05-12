#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks if enum metric value is described in allowed values of the @ref DFL::Mdib::EnumStringMetric descriptor.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1108 [funcSpec]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * pm:EnumStringMetricDescriptor has at least one pm:AllowedValue element.
 *
 * S32_SRS_1109 [funcSpec]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if pm:EnumStringMetricState/pm:MetricValue/\@Value exists,
 * then that value is one of the accepted values described in pm:EnumStringDescriptor/pm:AllowedValues.
 *
 * @ingroup Mdib
 */
class AllowedValueChecker : public Checker
{
public:
    CheckerResult check(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        const MdibTreeStore& mdibTreeStore,
        const MdibChangeSet& changes) override;
};
}
