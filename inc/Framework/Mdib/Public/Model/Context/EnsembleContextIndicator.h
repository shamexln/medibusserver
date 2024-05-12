#pragma once

#include <Framework/Mdib/Private/ContextDescriptorEntity.h>
#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextStateBuilder.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
class EnsembleContextIndicator;
class SystemContext;

/**
 * @brief Type safe handle for \ref EnsembleContextIndicator.
 * @ingroup Mdib
 */
using EnsembleContextIndicatorHandle = BasicHandle<EnsembleContextIndicator>;

/**
 * @brief Indicates that a medical device can provide information about the ensemble(s) that it is associated with.
 * @details An ensemble represents an arbitrary group of medical devices. The semantics depend on the ensemble itself.
 * @ingroup Mdib
 */
class EnsembleContextIndicator: public Impl::ContextDescriptorEntity<EnsembleContextIndicator, EnsembleContextDescriptorBuilder, EnsembleContextStateBuilder, SystemContext>
{
    DFL_MDIB_IMMUTABLE(EnsembleContextIndicator)

    public:
        /**
         * @brief Constructor.
         */
        EnsembleContextIndicator(const EnsembleContextIndicatorHandle& handle,
                                 const DFL::NotNull<EnsembleContextDescriptorSharedPtr>& descriptor,
                                 VersionCounter descriptorVersion,
                                 const BasicHandle<SystemContext>& parent);

        /**
         * @brief Constructor that accepts a state and state version to ease the use with templates.
         * @details \note The state and state version are not used by the constructor.
         */
        EnsembleContextIndicator(const EnsembleContextIndicatorHandle& handle,
                                 const DFL::NotNull<EnsembleContextDescriptorSharedPtr>& descriptor,
                                 VersionCounter descriptorVersion,
                                 const DFL::NotNull<EnsembleContextStateSharedPtr>& state,
                                 VersionCounter stateVersion,
                                 const BasicHandle<SystemContext>& parent);
};

inline EnsembleContextIndicator::EnsembleContextIndicator(const EnsembleContextIndicatorHandle& handle,
                                                          const DFL::NotNull<EnsembleContextDescriptorSharedPtr>& descriptor,
                                                          VersionCounter descriptorVersion,
                                                          const BasicHandle<SystemContext>& parent) :
        Impl::ContextDescriptorEntity<EnsembleContextIndicator, EnsembleContextDescriptorBuilder, EnsembleContextStateBuilder, SystemContext>(
            handle,
            descriptor,
            descriptorVersion,
            parent)
{
}

inline EnsembleContextIndicator::EnsembleContextIndicator(const EnsembleContextIndicatorHandle& handle,
                                                          const DFL::NotNull<EnsembleContextDescriptorSharedPtr>& descriptor,
                                                          VersionCounter descriptorVersion,
                                                          const DFL::NotNull<EnsembleContextStateSharedPtr>& /* state */,
                                                          VersionCounter /* stateVersion */,
                                                          const BasicHandle<SystemContext>& parent) :
        Impl::ContextDescriptorEntity<EnsembleContextIndicator, EnsembleContextDescriptorBuilder, EnsembleContextStateBuilder, SystemContext>(
            handle,
            descriptor,
            descriptorVersion,
            parent)
{
}

/**
 * @brief Definition of shared pointer type \ref EnsembleContextIndicatorSharedPtr for entity \ref EnsembleContextIndicator.
 */
using EnsembleContextIndicatorSharedPtr = SharedPtr<EnsembleContextIndicator>;

} /* namespace Mdib */
} /* namespace DFL */
