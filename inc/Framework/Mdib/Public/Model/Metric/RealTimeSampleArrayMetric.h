#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricSharedPtrType.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricStateBuilder.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
class Channel;
class RealTimeSampleArrayMetric;

/**
 * @brief Type safe handle for \ref RealTimeSampleArrayMetric.
 * @ingroup Mdib
 */
using RealTimeSampleArrayMetricHandle = BasicHandle<RealTimeSampleArrayMetric>;

/**
 * @brief Declares a sample array that represents a real-time continuous waveform.
 * @details Example: an electrocardiogram (ECG) real-time wave.
 * @ingroup Mdib
 */
class RealTimeSampleArrayMetric: public Impl::MdibEntity<RealTimeSampleArrayMetric, RealTimeSampleArrayMetricDescriptorBuilder, RealTimeSampleArrayMetricStateBuilder, Channel>
{
    DFL_MDIB_IMMUTABLE(RealTimeSampleArrayMetric)

    public:
        /**
         * Constructor to populate all fields.
         */
        RealTimeSampleArrayMetric(const RealTimeSampleArrayMetricHandle& handle,
                                  const DFL::NotNull<RealTimeSampleArrayMetricDescriptorSharedPtr>& descriptor,
                                  VersionCounter descriptorVersion,
                                  const DFL::NotNull<RealTimeSampleArrayMetricStateSharedPtr>& state,
                                  VersionCounter stateVersion,
                                  const BasicHandle<Channel>& parent);
};

inline RealTimeSampleArrayMetric::RealTimeSampleArrayMetric(const RealTimeSampleArrayMetricHandle& handle,
                                                            const DFL::NotNull<RealTimeSampleArrayMetricDescriptorSharedPtr>& descriptor,
                                                            VersionCounter descriptorVersion,
                                                            const DFL::NotNull<RealTimeSampleArrayMetricStateSharedPtr>& state,
                                                            VersionCounter stateVersion,
                                                            const BasicHandle<Channel>& parent) :
        Impl::MdibEntity<RealTimeSampleArrayMetric, RealTimeSampleArrayMetricDescriptorBuilder, RealTimeSampleArrayMetricStateBuilder, Channel>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

/**
 * @brief Definition of shared pointer type \ref RealTimeSampleArrayMetricSharedPtr for entity \ref RealTimeSampleArrayMetric.
 * @ingroup Mdib
 */
using RealTimeSampleArrayMetricSharedPtr = SharedPtr<RealTimeSampleArrayMetric>;

} /* namespace Mdib */
} /* namespace DFL */
