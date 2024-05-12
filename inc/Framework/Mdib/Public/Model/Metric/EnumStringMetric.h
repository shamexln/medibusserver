#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetricStateBuilder.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
class Channel;
class EnumStringMetric;

/**
 * @brief Type safe handle for \ref EnumStringMetric.
 * @ingroup Mdib
 */
using EnumStringMetricHandle = BasicHandle<EnumStringMetric>;

/**
 * @brief A string metric represents a textual status or annotation information.
 * @ingroup Mdib
 */
class EnumStringMetric: public Impl::MdibEntity<EnumStringMetric, EnumStringMetricDescriptorBuilder, EnumStringMetricStateBuilder, Channel>
{
    DFL_MDIB_IMMUTABLE(EnumStringMetric)

    public:
        /**
         * Constructor to populate all fields.
         */
    EnumStringMetric(const EnumStringMetricHandle& handle,
                     const DFL::NotNull<EnumStringMetricDescriptorSharedPtr>& descriptor,
                     VersionCounter descriptorVersion,
                     const DFL::NotNull<EnumStringMetricStateSharedPtr>& state,
                     VersionCounter stateVersion,
                     const BasicHandle<Channel>& parent);
};

inline EnumStringMetric::EnumStringMetric(const EnumStringMetricHandle& handle,
                                          const DFL::NotNull<EnumStringMetricDescriptorSharedPtr>& descriptor,
                                          VersionCounter descriptorVersion,
                                          const DFL::NotNull<EnumStringMetricStateSharedPtr>& state,
                                          VersionCounter stateVersion,
                                          const BasicHandle<Channel>& parent) :
        Impl::MdibEntity<EnumStringMetric, EnumStringMetricDescriptorBuilder, EnumStringMetricStateBuilder, Channel>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref EnumStringMetricSharedPtr for entity \ref EnumStringMetric.
 */
using EnumStringMetricSharedPtr = SharedPtr<EnumStringMetric>;

}
}
