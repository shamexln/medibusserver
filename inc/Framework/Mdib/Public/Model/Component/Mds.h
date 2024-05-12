#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Utils/Entities.h>
#include <Framework/Mdib/Public/Model/Component/MdsDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/MdsStateBuilder.h>

#include <variant>

namespace DFL::Mdib
{
namespace Impl
{
class MdsParentPlaceholder;
}
class Mds;
class Vmd;

/**
 * @brief Type safe handle for \ref Mds.
 * @ingroup Mdib
 */
using MdsHandle = BasicHandle<Mds>;

/**
 * @brief Represents a medical device system that in turn represents a medical device such as an anesthesia workstation.
 * @ingroup Mdib
 */
class Mds: public Impl::MdibEntity<Mds, MdsDescriptorBuilder, MdsStateBuilder, Impl::MdsParentPlaceholder>
{
    public:
        /// @brief The only ordered children of MDSs are VMDs.
        using ChildType = std::variant<NotNull<SharedPtr<Vmd>>>;
        /// @brief Container for visitor pattern.
        using ChildEntities = Entities<Vmd>;

        /**
         * @brief Constructor.
         */
        Mds(const MdsHandle& handle,
            const DFL::NotNull<MdsDescriptorSharedPtr>& descriptor,
            VersionCounter descriptorVersion,
            const DFL::NotNull<MdsStateSharedPtr>& state,
            VersionCounter stateVersion);

        /**
         * @brief Full constructor with parent.
         * @details \attention This constructor is intended to be used by template functions and shall not be used otherwise!
         */
        Mds(const MdsHandle& handle,
            const DFL::NotNull<MdsDescriptorSharedPtr>& descriptor,
            VersionCounter descriptorVersion,
            const DFL::NotNull<MdsStateSharedPtr>& state,
            VersionCounter stateVersion,
            const BasicHandle<Impl::MdsParentPlaceholder>& parent);
};

inline Mds::Mds(const MdsHandle& handle,
                const DFL::NotNull<MdsDescriptorSharedPtr>& descriptor,
                VersionCounter descriptorVersion,
                const DFL::NotNull<MdsStateSharedPtr>& state,
                VersionCounter stateVersion)
    : Impl::MdibEntity<Mds,
                       MdsDescriptorBuilder,
                       MdsStateBuilder,
                       Impl::MdsParentPlaceholder>(
          handle,
          descriptor,
          descriptorVersion,
          state,
          stateVersion,
          BasicHandle<Impl::MdsParentPlaceholder>{})
{
}

inline Mds::Mds(const MdsHandle& handle,
                const DFL::NotNull<MdsDescriptorSharedPtr>& descriptor,
                VersionCounter descriptorVersion,
                const DFL::NotNull<MdsStateSharedPtr>& state,
                VersionCounter stateVersion,
                const BasicHandle<Impl::MdsParentPlaceholder>& /* parent */)
    : Impl::MdibEntity<Mds,
                       MdsDescriptorBuilder,
                       MdsStateBuilder,
                       Impl::MdsParentPlaceholder>(
          handle,
          descriptor,
          descriptorVersion,
          state,
          stateVersion,
          BasicHandle<Impl::MdsParentPlaceholder>{})
{
}

/**
 * @brief Definition of shared pointer type \ref MdsSharedPtr for entity \ref Mds.
 */
using MdsSharedPtr = SharedPtr<Mds>;

}
