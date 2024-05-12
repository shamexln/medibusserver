#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricStateBuilder.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace DFL
{
namespace Mdib
{
class Channel;
class StringMetric;

/**
 * @brief Type safe handle for \ref StringMetric.
 * @ingroup Mdib
 */
using StringMetricHandle = BasicHandle<StringMetric>;

/**
 * @brief A string metric represents a textual status or annotation information.
 * @ingroup Mdib
 */
class StringMetric: public Impl::MdibEntity<StringMetric, StringMetricDescriptorBuilder, StringMetricStateBuilder, Channel>
{
    DFL_MDIB_IMMUTABLE(StringMetric)

    public:
        /**
         * Constructor to populate all fields.
         */
        StringMetric(const StringMetricHandle& handle,
                     const DFL::NotNull<StringMetricDescriptorSharedPtr>& descriptor,
                     VersionCounter descriptorVersion,
                     const DFL::NotNull<StringMetricStateSharedPtr>& state,
                     VersionCounter stateVersion,
                     const BasicHandle<Channel>& parent);
};

inline StringMetric::StringMetric(const StringMetricHandle& handle,
                                  const DFL::NotNull<StringMetricDescriptorSharedPtr>& descriptor,
                                  VersionCounter descriptorVersion,
                                  const DFL::NotNull<StringMetricStateSharedPtr>& state,
                                  VersionCounter stateVersion,
                                  const BasicHandle<Channel>& parent) :
        Impl::MdibEntity<StringMetric, StringMetricDescriptorBuilder, StringMetricStateBuilder, Channel>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref StringMetricSharedPtr for entity \ref StringMetric.
 */
using StringMetricSharedPtr = SharedPtr<StringMetric>;

} /* namespace Mdib */
} /* namespace DFL */
