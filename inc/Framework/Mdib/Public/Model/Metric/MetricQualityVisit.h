#pragma once

#include <Framework/Mdib/Public/Model/Metric/MetricQuality.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Calls the visitor for each member.
 *
 * @param vis visitor
 * @param metricQuality @ref DFL::Mdib::MetricQuality value to visit
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const MetricQuality& metricQuality)
{
    vis(metricQuality.validity());
    vis(metricQuality.mode());
    vis(metricQuality.qualityIndicator());
    vis(metricQuality.extensions());
}
}
}
