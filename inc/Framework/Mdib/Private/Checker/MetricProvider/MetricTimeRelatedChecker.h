#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn::MetricProvider
{

/**
 * @brief Checks consistency of time related attributes in Metrics
 * @details This checker applies to the Metric Provider role.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1086 [PTSR.21933 .. OSF.706 .. MPKP.Draft.216]:
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following condition holds true:
 * if for a pm:MetricValue pm:MetricQuality/\@Validity = Ong,\@StartTime is set.
 *
 * S32_SRS_1081 [PTSR.21927 .. OSF.444 .. MPKP.Draft.204]:
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following condition holds true:
 * if pm:AbstractMetricDescriptor/\@MetricAvailability = Cont, then pm:AbstractMetricDescriptor/\@DeterminationPeriod is set.
 *
 * S32_SRS_1083 [PTSR.21928 .. OSF.740 .. MPKP.Draft.210]:
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that at least one of the following conditions holds true:
 * - if pm:AbstractMetricDescriptor/\@MetricCategory in { Msrmt, Clc } with the exception of pm:RealTimeSampleArrayMetricDescriptor,
 * then pm:AbstractMetricDescriptor/\@LifeTimePeriod is set.
 * - if pm:AbstractMetricDescriptor/\@MetricCategory in { Msrmt, Clc } with the exception of pm:RealTimeSampleArrayMetricDescriptor,
 * then pm:AbstractMetricState/\@LifeTimePeriod is set.
 *
 * S32_SRS_1284 [PTSR.21916 .. OSF.679 .. MPKP.Draft.187]:
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following condition holds true:
 * if a metric's \@MetricAvailability = Cont, then the metric's \@Validity != Ong.
 *
 * @ingroup Mdib
 */
class MetricTimeRelatedChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            const MdibTreeStore& mdibTreeStore,
            const MdibChangeSet& changes) override;
};

}
