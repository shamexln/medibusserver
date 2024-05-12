#pragma once

#include <Framework/Mdib/Private/ContextStateEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class PatientContext;
class PatientContextIndicator;

/**
 * @brief Type safe handle for \ref PatientContext.
 * @ingroup Mdib
 */
using PatientContextHandle = BasicHandle<PatientContext>;

/**
 * @brief Multi-state version of patient contexts.
 * @ingroup Mdib
 */
class PatientContext: public Impl::ContextStateEntity<PatientContext, PatientContextDescriptorBuilder, PatientContextStateBuilder, PatientContextIndicator>
{
    public:
        /**
         * @brief Constructor.
         */
        PatientContext(const PatientContextHandle& stateHandle,
                       const DFL::NotNull<PatientContextStateSharedPtr>& state,
                       VersionCounter stateVersion,
                       const BasicHandle<PatientContextIndicator>& descriptorHandle);

        /**
         * @brief Constructor that accepts a descriptor and descriptor version to ease the use with templates.
         * @details \note The descriptor and descriptor version are not used by the constructor.
         */
        PatientContext(const PatientContextHandle& stateHandle,
                       const DFL::NotNull<PatientContextDescriptorSharedPtr>& descriptor,
                       VersionCounter descriptorVersion,
                       const DFL::NotNull<PatientContextStateSharedPtr>& state,
                       VersionCounter stateVersion,
                       const BasicHandle<PatientContextIndicator>& descriptorHandle);
};

inline PatientContext::PatientContext(const PatientContextHandle& stateHandle,
                                      const DFL::NotNull<PatientContextStateSharedPtr>& state,
                                      VersionCounter stateVersion,
                                      const BasicHandle<PatientContextIndicator>& descriptorHandle) :
        ContextStateEntity(stateHandle, state, stateVersion, descriptorHandle)
{
}

inline PatientContext::PatientContext(const PatientContextHandle& stateHandle,
                                      const DFL::NotNull<PatientContextDescriptorSharedPtr>& /* descriptor */,
                                      VersionCounter /* descriptorVersion */,
                                      const DFL::NotNull<PatientContextStateSharedPtr>& state,
                                      VersionCounter stateVersion,
                                      const BasicHandle<PatientContextIndicator>& descriptorHandle) :
        ContextStateEntity(stateHandle, state, stateVersion, descriptorHandle)
{
}

/**
 * @brief Definition of shared pointer type \ref PatientContextSharedPtr for entity \ref PatientContext.
 */
using PatientContextSharedPtr = SharedPtr<PatientContext>;


} /* namespace Mdib */
} /* namespace DFL */
