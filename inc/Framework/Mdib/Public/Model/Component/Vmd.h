#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/VmdDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/VmdStateBuilder.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Mdib/Public/Utils/Entities.h>

#include <variant>

namespace DFL::Mdib
{
class Vmd;
class Mds;
class Channel;

/**
 * @brief Type safe handle for \ref Vmd.
 * @ingroup Mdib
 */
using VmdHandle = BasicHandle<Vmd>;

/**
 * @brief An abstraction for a module (medical-related subsystem) of an \ref Mds.
 * @details According to IEEE 11073-10201, an MDS with one VMD is a single purpose point-of-care (PoC) medical device in contrast to an MDS
 * with multiple VMDs that has multiple purposes.
 *
 * \note Example: a multiple purpose PoC medical device: an anesthesia workstation (one MDS) with a ventilation unit (one VMD), a
 * patient monitoring unit (another VMD), and gas delivery/monitor system (another VMD). In the IEEE 11073-10201 a VMD may not
 * be a hardware module, it also can be pure software.
 * @ingroup Mdib
 */
class Vmd: public Impl::MdibEntity<Vmd, VmdDescriptorBuilder, VmdStateBuilder, Mds>
{
    public:
        /// @brief The only ordered children of VMDs are Channels.
        using ChildType = std::variant<NotNull<SharedPtr<Channel>>>;
        /// @brief Container for visitor pattern.
        using ChildEntities = Entities<Channel>;

        /**
         * @brief Constructor.
         */
        Vmd(const VmdHandle& handle,
            const DFL::NotNull<VmdDescriptorSharedPtr>& descriptor,
            VersionCounter descriptorVersion,
            const DFL::NotNull<VmdStateSharedPtr>& state,
            VersionCounter stateVersion,
            const BasicHandle<Mds>& parent);
};

inline Vmd::Vmd(const VmdHandle& handle,
                const DFL::NotNull<VmdDescriptorSharedPtr>& descriptor,
                VersionCounter descriptorVersion,
                const DFL::NotNull<VmdStateSharedPtr>& state,
                VersionCounter stateVersion,
                const BasicHandle<Mds>& parent):
        Impl::MdibEntity<Vmd, VmdDescriptorBuilder, VmdStateBuilder, Mds>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref VmdSharedPtr for entity \ref Vmd.
 */
using VmdSharedPtr = SharedPtr<Vmd>;

}
