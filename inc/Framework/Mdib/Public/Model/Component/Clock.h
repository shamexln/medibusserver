#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/ClockDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/ClockStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class Clock;
class Mds;

/**
 * @brief Type safe handle for \ref Clock.
 * @ingroup Mdib
 */
using ClockHandle = BasicHandle<Clock>;

/**
 * @brief Description of date/time capabilities of an \ref Mds.
 * @details The presence of a %Clock object does not imply any specific hardware or software support.
 * @ingroup Mdib
 */
class Clock: public Impl::MdibEntity<Clock, ClockDescriptorBuilder, ClockStateBuilder, Mds>
{
    public:
        /**
         * @brief Constructor.
         */
        Clock(const ClockHandle& handle,
              const DFL::NotNull<ClockDescriptorSharedPtr>& descriptor,
              VersionCounter descriptorVersion,
              const DFL::NotNull<ClockStateSharedPtr>& state,
              VersionCounter stateVersion,
              const BasicHandle<Mds>& parent);
};

inline Clock::Clock(const ClockHandle& handle,
                    const DFL::NotNull<ClockDescriptorSharedPtr>& descriptor,
                    VersionCounter descriptorVersion,
                    const DFL::NotNull<ClockStateSharedPtr>& state,
                    VersionCounter stateVersion,
                    const BasicHandle<Mds>& parent):
        Impl::MdibEntity<Clock, ClockDescriptorBuilder, ClockStateBuilder, Mds>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref ClockSharedPtr for entity \ref Clock.
 */
using ClockSharedPtr = SharedPtr<Clock>;


} /* namespace Mdib */
} /* namespace DFL */
