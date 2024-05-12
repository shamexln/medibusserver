#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Utils/Entities.h>
#include <Framework/Mdib/Public/Utils/EntityLists.h>
#include <Framework/Mdib/Public/Model/Component/ChannelDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/ChannelStateBuilder.h>

#include <variant>

namespace DFL::Mdib
{
class Channel;
class DistributionSampleArrayMetric;
class EnumStringMetric;
class NumericMetric;
class RealTimeSampleArrayMetric;
class StringMetric;
class Vmd;

/**
 * @brief Type safe handle for \ref Channel.
 * @ingroup Mdib
 */
using ChannelHandle = BasicHandle<Channel>;

/**
 * @brief Describes a channel to group metrics for organizational purposes only.
 * @details Example: an example would be a blood pressure \ref Vmd with one channel to group together all metrics that
 * deal with the blood pressure (e.g., pressure value, pressure waveform). A second channel object could be used
 * to group together metrics that deal with heart rate.
 * @ingroup Mdib
 */
class Channel: public Impl::MdibEntity<Channel, ChannelDescriptorBuilder, ChannelStateBuilder, Vmd>
{
    public:
        /// @brief Child types of a channel match any metric.
        using ChildType = std::variant<DFL_MDIB_ENTITIES_AS_SHARED_PTRS(DFL_MDIB_ENTITY_METRICS)>;
        /// @brief Container for visitor pattern.
        using ChildEntities = Entities<DFL_MDIB_ENTITY_METRICS>;

        /**
         * @brief Constructor.
         */
        Channel(const ChannelHandle& handle,
                const DFL::NotNull<ChannelDescriptorSharedPtr>& descriptor,
                VersionCounter descriptorVersion,
                const DFL::NotNull<ChannelStateSharedPtr>& state,
                VersionCounter stateVersion,
                const BasicHandle<Vmd>& parent);
};

inline Channel::Channel(const ChannelHandle& handle,
                        const DFL::NotNull<ChannelDescriptorSharedPtr>& descriptor,
                        VersionCounter descriptorVersion,
                        const DFL::NotNull<ChannelStateSharedPtr>& state,
                        VersionCounter stateVersion,
                        const BasicHandle<Vmd>& parent):
        Impl::MdibEntity<Channel, ChannelDescriptorBuilder, ChannelStateBuilder, Vmd>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref ChannelSharedPtr for entity \ref Channel.
 */
using ChannelSharedPtr = SharedPtr<Channel>;

}
