#pragma once

#include <Framework/Mdib/Private/ContextDescriptorEntity.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextStateBuilder.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
class LocationContextIndicator;
class SystemContext;

/**
 * @brief Type safe handle for \ref LocationContextIndicator.
 * @ingroup Mdib
 */
using LocationContextIndicatorHandle = BasicHandle<LocationContextIndicator>;

/**
 * @brief Indicates that a medical device can provide information about the location(s) that it is associated with.
 * @ingroup Mdib
 */
class LocationContextIndicator: public Impl::ContextDescriptorEntity<LocationContextIndicator, LocationContextDescriptorBuilder, LocationContextStateBuilder, SystemContext>
{
    DFL_MDIB_IMMUTABLE(LocationContextIndicator)

    public:
        /**
         * @brief Constructor.
         */
        LocationContextIndicator(const LocationContextIndicatorHandle& handle,
                                 const DFL::NotNull<LocationContextDescriptorSharedPtr>& descriptor,
                                 VersionCounter descriptorVersion,
                                 const BasicHandle<SystemContext>& parent);

        /**
         * @brief Constructor that accepts a state and state version to ease the use with templates.
         * @details \note The state and state version are not used by the constructor.
         */
        LocationContextIndicator(const LocationContextIndicatorHandle& handle,
                                 const DFL::NotNull<LocationContextDescriptorSharedPtr>& descriptor,
                                 VersionCounter descriptorVersion,
                                 const DFL::NotNull<LocationContextStateSharedPtr>& state,
                                 VersionCounter stateVersion,
                                 const BasicHandle<SystemContext>& parent);
};

inline LocationContextIndicator::LocationContextIndicator(const LocationContextIndicatorHandle& handle,
                                                          const DFL::NotNull<LocationContextDescriptorSharedPtr>& descriptor,
                                                          VersionCounter descriptorVersion,
                                                          const BasicHandle<SystemContext>& parent) :
        Impl::ContextDescriptorEntity<LocationContextIndicator, LocationContextDescriptorBuilder, LocationContextStateBuilder, SystemContext>(
            handle,
            descriptor,
            descriptorVersion,
            parent)
{
}

inline LocationContextIndicator::LocationContextIndicator(const LocationContextIndicatorHandle& handle,
                                                          const DFL::NotNull<LocationContextDescriptorSharedPtr>& descriptor,
                                                          VersionCounter descriptorVersion,
                                                          const DFL::NotNull<LocationContextStateSharedPtr>& /* state */,
                                                          VersionCounter /* stateVersion */,
                                                          const BasicHandle<SystemContext>& parent) :
        Impl::ContextDescriptorEntity<LocationContextIndicator, LocationContextDescriptorBuilder, LocationContextStateBuilder, SystemContext>(
            handle,
            descriptor,
            descriptorVersion,
            parent)
{
}

/**
 * @brief Definition of shared pointer type \ref LocationContextIndicatorSharedPtr for entity \ref LocationContextIndicator.
 */
using LocationContextIndicatorSharedPtr = SharedPtr<LocationContextIndicator>;

} /* namespace Mdib */
} /* namespace DFL */
