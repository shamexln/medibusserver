#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL::Mdib::Impl::PlugIn::MetricProvider
{

/**
 * @brief Checks MetricValue - ActivationState and MetricCategory relations.
 * @details This checker applies to the Metric Provider role.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1168 [PTSR.31252 .. OSF.16112 .. OSFR.160]
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractMetricDescriptor/pm:MetricValue contains \@StartTime and either \@StopTime or \@DeterminationTime,
 * then \@StartTime is less than or equal to \@StopTime and \@DeterminationTime.
 *
 * S32_SRS_1179 [PTSR.31609 .. OSF.16227 .. MPKP.Draft.674]:
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following condition holds true:
 * if @ref DFL::Mdib::ComponentActivation "pm:AbstractMetricState/\@ActivationState" = On, then the metric's pm:MetricValue is present.
 *
 * S32_SRS_1281 [PTSR.21905 .. OSF.719 .. MPKP.Draft.129] 
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following condition holds true:
 * if \@MetricCategory in { Msrmt, Clc }, while \@ActivationState in { StndBy, NotRdy }, \@Value/\@Samples does not change.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP MetricActivationChecker: public Checker
{
    public:
        CheckerResult check(MdibChangeType changeType,
                            const NotNull<MdibSharedPtr>& mdib,
                            const MdibTreeStore& mdibTreeStore,
                            const MdibChangeSet& changes) override;
};

}
