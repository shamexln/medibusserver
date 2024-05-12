#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/SystemContextDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/SystemContextStateBuilder.h>
#include <Framework/Mdib/Public/Model/Handle.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace DFL
{
namespace Mdib
{
class Mds;
class SystemContext;

/**
 * @brief Type safe handle for \ref SystemContext.
 * @ingroup Mdib
 */
using SystemContextHandle = BasicHandle<SystemContext>;

/**
 * @brief The context of an \ref Mds that lists the possible relationship of a medical device into its usage environment by means
 * of contexts.
 * @ingroup Mdib
 */
class SystemContext: public Impl::MdibEntity<SystemContext, SystemContextDescriptorBuilder, SystemContextStateBuilder, Mds>
{
    DFL_MDIB_IMMUTABLE(SystemContext)

    public:
        /**
         * @brief Constructor.
         */
        SystemContext(const SystemContextHandle& handle,
                      const DFL::NotNull<SystemContextDescriptorSharedPtr>& descriptor,
                      VersionCounter descriptorVersion,
                      const DFL::NotNull<SystemContextStateSharedPtr>& state,
                      VersionCounter stateVersion,
                      const BasicHandle<Mds>& parent);
};

inline SystemContext::SystemContext(const SystemContextHandle& handle,
                                    const DFL::NotNull<SystemContextDescriptorSharedPtr>& descriptor,
                                    VersionCounter descriptorVersion,
                                    const DFL::NotNull<SystemContextStateSharedPtr>& state,
                                    VersionCounter stateVersion,
                                    const BasicHandle<Mds>& parent) :
        Impl::MdibEntity<SystemContext, SystemContextDescriptorBuilder, SystemContextStateBuilder, Mds>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref SystemContextSharedPtr for entity \ref SystemContext.
 */
using SystemContextSharedPtr = SharedPtr<SystemContext>;


} /* namespace Mdib */
} /* namespace DFL */
