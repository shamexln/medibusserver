#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricStateBuilder.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
class Channel;
class DistributionSampleArrayMetric;

/**
 * @brief Type safe handle for \ref DistributionSampleArrayMetric.
 * @ingroup Mdib
 */
using DistributionSampleArrayMetricHandle = BasicHandle<DistributionSampleArrayMetric>;

/**
 * @brief Declares a sample array that represents linear value distributions in the form of arrays containing scaled sample values.
 * @details In contrast to real-time sample arrays, distribution sample arrays provide observed spatial values, not time points.
 *
 * \note An example for a distribution sample array metric might be a fourier-transformed electroencephalogram to derive frequency distribution.
 * @ingroup Mdib
 */
class DistributionSampleArrayMetric: public Impl::MdibEntity<DistributionSampleArrayMetric, DistributionSampleArrayMetricDescriptorBuilder, DistributionSampleArrayMetricStateBuilder, Channel>
{
    DFL_MDIB_IMMUTABLE(DistributionSampleArrayMetric)

    public:
        /**
         * Constructor to populate all fields.
         */
        DistributionSampleArrayMetric(const DistributionSampleArrayMetricHandle& handle,
                                      const DFL::NotNull<DistributionSampleArrayMetricDescriptorSharedPtr>& descriptor,
                                      VersionCounter descriptorVersion,
                                      const DFL::NotNull<DistributionSampleArrayMetricStateSharedPtr>& state,
                                      VersionCounter stateVersion,
                                      const BasicHandle<Channel>& parent);
};

inline DistributionSampleArrayMetric::DistributionSampleArrayMetric(const DistributionSampleArrayMetricHandle& handle,
                                                                    const DFL::NotNull<DistributionSampleArrayMetricDescriptorSharedPtr>& descriptor,
                                                                    VersionCounter descriptorVersion,
                                                                    const DFL::NotNull<DistributionSampleArrayMetricStateSharedPtr>& state,
                                                                    VersionCounter stateVersion,
                                                                    const BasicHandle<Channel>& parent) :
        Impl::MdibEntity<DistributionSampleArrayMetric, DistributionSampleArrayMetricDescriptorBuilder, DistributionSampleArrayMetricStateBuilder, Channel>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

/**
 * @brief Definition of shared pointer type \ref DistributionSampleArrayMetricSharedPtr for entity \ref DistributionSampleArrayMetric.
 */
using DistributionSampleArrayMetricSharedPtr = SharedPtr<DistributionSampleArrayMetric>;


} /* namespace Mdib */
} /* namespace DFL */
