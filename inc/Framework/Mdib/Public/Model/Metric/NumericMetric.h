#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricStateBuilder.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
class Channel;
class NumericMetric;

/**
 * @brief Type safe handle for \ref NumericMetric.
 * @ingroup Mdib
 */
using NumericMetricHandle = BasicHandle<NumericMetric>;

/**
 * @brief Specification of a metric descriptor type that represents a single numerical measurement and status information.
 * @details Example: a heart rate measurement.
 * @ingroup Mdib
 */
class NumericMetric: public Impl::MdibEntity<NumericMetric, NumericMetricDescriptorBuilder, NumericMetricStateBuilder, Channel>
{
    DFL_MDIB_IMMUTABLE(NumericMetric)

    public:
        /**
         * Constructor to populate all fields.
         */
        NumericMetric(const NumericMetricHandle& handle,
                      const DFL::NotNull<NumericMetricDescriptorSharedPtr>& descriptor,
                      VersionCounter descriptorVersion,
                      const DFL::NotNull<NumericMetricStateSharedPtr>& state,
                      VersionCounter stateVersion,
                      const BasicHandle<Channel>& parent);
};

inline NumericMetric::NumericMetric(const NumericMetricHandle& handle,
                                    const DFL::NotNull<NumericMetricDescriptorSharedPtr>& descriptor,
                                    VersionCounter descriptorVersion,
                                    const DFL::NotNull<NumericMetricStateSharedPtr>& state,
                                    VersionCounter stateVersion,
                                    const BasicHandle<Channel>& parent) :
        Impl::MdibEntity<NumericMetric, NumericMetricDescriptorBuilder, NumericMetricStateBuilder, Channel>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref NumericMetricSharedPtr for entity \ref NumericMetric.
 */
using NumericMetricSharedPtr = SharedPtr<NumericMetric>;


} /* namespace Mdib */
} /* namespace DFL */
