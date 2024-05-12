#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/BatteryDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/BatteryStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class Battery;
class Mds;

/**
 * @brief Type safe handle for \ref Battery.
 * @ingroup Mdib
 */
using BatteryHandle = BasicHandle<Battery>;

/**
 * @brief Battery capabilities of an \ref Mds.
 * @ingroup Mdib
 */
class Battery: public Impl::MdibEntity<Battery, BatteryDescriptorBuilder, BatteryStateBuilder, Mds>
{
    public:
        /**
         * @brief Constructor.
         */
        Battery(const BatteryHandle& handle,
                const DFL::NotNull<BatteryDescriptorSharedPtr>& descriptor,
                VersionCounter descriptorVersion,
                const DFL::NotNull<BatteryStateSharedPtr>& state,
                VersionCounter stateVersion,
                const BasicHandle<Mds>& parent);
};

inline Battery::Battery(const BatteryHandle& handle,
                        const DFL::NotNull<BatteryDescriptorSharedPtr>& descriptor,
                        VersionCounter descriptorVersion,
                        const DFL::NotNull<BatteryStateSharedPtr>& state,
                        VersionCounter stateVersion,
                        const BasicHandle<Mds>& parent) :
        Impl::MdibEntity<Battery, BatteryDescriptorBuilder, BatteryStateBuilder, Mds>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref BatterySharedPtr for entity \ref Battery.
 */
using BatterySharedPtr = SharedPtr<Battery>;


} /* namespace Mdib */
} /* namespace DFL */
