#pragma once

#include <Framework/Mdib/Private/ContextStateEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class EnsembleContext;
class EnsembleContextIndicator;

/**
 * @brief Type safe handle for \ref EnsembleContext.
 * @ingroup Mdib
 */
using EnsembleContextHandle = BasicHandle<EnsembleContext>;

/**
 * @brief Multi-state version of ensemble contexts.
 * @ingroup Mdib
 */
class EnsembleContext: public Impl::ContextStateEntity<EnsembleContext, EnsembleContextDescriptorBuilder, EnsembleContextStateBuilder, EnsembleContextIndicator>
{
    public:
        /**
         * @brief Constructor.
         */
        EnsembleContext(const EnsembleContextHandle& stateHandle,
                        const DFL::NotNull<EnsembleContextStateSharedPtr>& state,
                        VersionCounter stateVersion,
                        const BasicHandle<EnsembleContextIndicator>& descriptorHandle);

        /**
         * @brief Constructor that accepts a descriptor and descriptor version to ease the use with templates.
         * @details \note The descriptor and descriptor version are not used by the constructor.
         */
        EnsembleContext(const EnsembleContextHandle& stateHandle,
                        const DFL::NotNull<EnsembleContextDescriptorSharedPtr>& descriptor,
                        VersionCounter descriptorVersion,
                        const DFL::NotNull<EnsembleContextStateSharedPtr>& state,
                        VersionCounter stateVersion,
                        const BasicHandle<EnsembleContextIndicator>& descriptorHandle);
};

inline EnsembleContext::EnsembleContext(const EnsembleContextHandle& stateHandle,
                                        const DFL::NotNull<EnsembleContextStateSharedPtr>& state,
                                        VersionCounter stateVersion,
                                        const BasicHandle<EnsembleContextIndicator>& descriptorHandle) :
        ContextStateEntity(stateHandle, state, stateVersion, descriptorHandle)
{
}

inline EnsembleContext::EnsembleContext(const EnsembleContextHandle& stateHandle,
                                        const DFL::NotNull<EnsembleContextDescriptorSharedPtr>& /* descriptor */,
                                        VersionCounter /* descriptorVersion */,
                                        const DFL::NotNull<EnsembleContextStateSharedPtr>& state,
                                        VersionCounter stateVersion,
                                        const BasicHandle<EnsembleContextIndicator>& descriptorHandle) :
        ContextStateEntity(stateHandle, state, stateVersion, descriptorHandle)
{
}

/**
 * @brief Definition of shared pointer type \ref EnsembleContextSharedPtr for entity \ref EnsembleContext.
 */
using EnsembleContextSharedPtr = SharedPtr<EnsembleContext>;

} /* namespace Mdib */
} /* namespace DFL */
