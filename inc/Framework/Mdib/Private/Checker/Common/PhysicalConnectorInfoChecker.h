#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks existence for required PhysicalConnectorInfo.
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1296 [PTSR.21967 .. OSF.642 .. BPKP.Draft.1436]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if a pm:MdsDescriptor contains multiple pm:VmdDescriptor elements that are of semantically equivalent pm:Type
 * and while the corresponding pm:VmdState/\@ActivationState is {On, StndBy, Fail}, each of these pm:VmdState elements
 * has a unique pm:PhysicalConnectorInfo/\@Number.
 *
 * Info: The Number is not intended for display.
 *       Example: Used for IHE PCD (HL7) containment tree ID.
 *       The VMD may represent a physical connector.
 *
 *
 * S32_SRS_1297 [PTSR.21969 .. OSF.646 .. BKPK.Draft.1437]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if a pm:VmdDescriptor contains multiple pm:ChannelDescriptor elements that are of semantically equivalent
 * pm:Type and while the corresponding pm:ChannelState/\@ActivationState is {On, StndBy, Fail}, each of the
 * corresponding pm:ChannelState elements has a unique pm:PhysicalConnectorInfo/\@Number.
 *
 * S32_SRS_1298 [PTSR.21972 .. OSF.648 .. BKPK.Draft.1438]:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * if a pm:ChannelDescriptor contains multiple pm:AbstractMetricDescriptor elements that are of the same
 * \@MetricCategory and of semantically equivalent pm:Type and pm:Unit, each of these pm:AbstractMetricDescriptor
 * elements has a unique pm:PhysicalConnectorInfo/\@Number.
 *
 * Info: e.g. if Y-cables with two sensors are supported
 *       Note: Metrics with same type and different units may have the same PhysicalConnectorInfo.
 *       BodySite is not included because you could have multiple measurements at the same BodySite.
 *
 * @ingroup Mdib
 */
class PhysicalConnectorInfoChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr> &mdib,
            const MdibTreeStore &mdibTreeStore,
            const MdibChangeSet &changes) override;
};

}
