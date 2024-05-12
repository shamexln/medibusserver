#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks consistency of Metric States.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_915 [PTSR.34047 .. OSF.16707 .. BICEPS.B.61.Documentation(pm:MetricQuality/\@Validity)]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if for a pm:MetricValue pm:MetricQuality/\@Validity in { Ong, NA }, then \@Value / \@Samples shall not be set.
 *
 * Note:
 * We have in B.440 MeasurementValidity:
 * - Ong = Measurement Ongoing. Indicates that a new measurement is just being taken and therefore measured value is **not available**.
 * - NA = Not Available. **No value** can be derived, e.g., if a sensor is not placed correctly.
 *
 * This implies for
 * - @ref NumericMetricValue and @ref StringMetricValue : the value is not there.
 * - @ref SampleArrayValue : samples are empty.
 *
 * BICEPS ObservedValueStream is not handled (entity not modeled).
 *
 * S32_SRS_1276 [PTSR.32154 .. OSF.16380 .. MPKP.675]:
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following condition holds true:
 * if pm:MetricValue/pm:MetricQuality/\@Validity in { Vld, Vldated }, then \@Value/\@Samples is present.
 *
 * S32_SRS_1279 [PTSR.26482 .. OSF.2117 .. MPKP.214/SDC.R0011]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if for a pm:MetricValue \@Value / \@Samples exists, then \@DeterminationTime shall be set.
 *
 * Note:
 * Requirement S32_SRS_1279 links both into the MPKP as well as into the SDC Glue standard. While the latter is
 * a lot more vague, the former is formulated like the S32 Requirement.
 *
 * S32_SRS_1304 [PTSR.21903 .. OSF.717 .. BICEPS.5.4.7]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if @ref DFL::Mdib::MetricCategory "pm:AbstractMetricDescriptor/\@MetricCategory" in { Mrsmt, Set, Clc } and
 * @ref DFL::Mdib::ComponentActivation "pm:AbstractMetricState/\@ActivationState" in { Shtdn, Off, Fail},
 * then the pm:MetricValue's \@Value/\@Samples is not present.
 *
 * @ingroup Mdib
 */
class MetricStateChecker : public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
