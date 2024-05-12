/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricState.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Calls the visitor for each member.
 *
 * @param vis visitor
 * @param distributionSampleArrayMetricState @ref DFL::Mdib::DistributionSampleArrayMetricState value to visit
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const DistributionSampleArrayMetricState& distributionSampleArrayMetricState)
{
    vis(distributionSampleArrayMetricState.activationState());
    vis(distributionSampleArrayMetricState.activeDeterminationPeriod());
    vis(distributionSampleArrayMetricState.lifeTimePeriod());
    vis(distributionSampleArrayMetricState.bodySites());
    vis(distributionSampleArrayMetricState.physicalConnector());
    vis(distributionSampleArrayMetricState.metricValue());
    vis(distributionSampleArrayMetricState.physiologicalRanges());
    vis(distributionSampleArrayMetricState.extensions());
}
}
}
}
