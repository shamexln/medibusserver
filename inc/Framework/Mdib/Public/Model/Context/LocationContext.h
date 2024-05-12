#pragma once

#include <Framework/Mdib/Private/ContextStateEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextStateBuilder.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace DFL
{
namespace Mdib
{
class LocationContext;
class LocationContextIndicator;

/**
 * @brief Type safe handle for \ref LocationContext.
 * @ingroup Mdib
 */
using LocationContextHandle = BasicHandle<LocationContext>;

/**
 * @brief Multi-state version of location contexts.
 * @ingroup Mdib
 */
class LocationContext: public Impl::ContextStateEntity<LocationContext, LocationContextDescriptorBuilder, LocationContextStateBuilder, LocationContextIndicator>
{
    public:
        /**
         * @brief Constructor.
         */
        LocationContext(const LocationContextHandle& stateHandle,
                        const DFL::NotNull<LocationContextStateSharedPtr>& state,
                        VersionCounter stateVersion,
                        const BasicHandle<LocationContextIndicator>& descriptorHandle);

        /**
         * @brief Constructor that accepts a descriptor and descriptor version to ease the use with templates.
         * @details \note The descriptor and descriptor version are not used by the constructor.
         */
        LocationContext(const LocationContextHandle& stateHandle,
                        const DFL::NotNull<LocationContextDescriptorSharedPtr>& descriptor,
                        VersionCounter descriptorVersion,
                        const DFL::NotNull<LocationContextStateSharedPtr>& state,
                        VersionCounter stateVersion,
                        const BasicHandle<LocationContextIndicator>& descriptorHandle);
};

inline LocationContext::LocationContext(const LocationContextHandle& stateHandle,
                                        const DFL::NotNull<LocationContextStateSharedPtr>& state,
                                        VersionCounter stateVersion,
                                        const BasicHandle<LocationContextIndicator>& descriptorHandle) :
        ContextStateEntity(stateHandle, state, stateVersion, descriptorHandle)
{
}

inline LocationContext::LocationContext(const LocationContextHandle& stateHandle,
                                        const DFL::NotNull<LocationContextDescriptorSharedPtr>& /* descriptor */,
                                        VersionCounter /* descriptorVersion */,
                                        const DFL::NotNull<LocationContextStateSharedPtr>& state,
                                        VersionCounter stateVersion,
                                        const BasicHandle<LocationContextIndicator>& descriptorHandle) :
        ContextStateEntity(stateHandle, state, stateVersion, descriptorHandle)
{
}

/**
 * @brief Definition of shared pointer type \ref LocationContextSharedPtr for entity \ref LocationContext.
 */
using LocationContextSharedPtr = SharedPtr<LocationContext>;


} /* namespace Mdib */
} /* namespace DFL */
