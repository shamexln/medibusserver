#pragma once

#include <Framework/Mdib/Private/ContextDescriptorEntity.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextStateBuilder.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
class PatientContextIndicator;
class SystemContext;

/**
 * @brief Type safe handle for \ref PatientContextIndicator.
 * @ingroup Mdib
 */
using PatientContextIndicatorHandle = BasicHandle<PatientContextIndicator>;

/**
 * @brief The patient context indicates that a medical device is able to process information about the patient that it is associated with.
 * @ingroup Mdib
 */
class PatientContextIndicator: public Impl::ContextDescriptorEntity<PatientContextIndicator, PatientContextDescriptorBuilder, PatientContextStateBuilder, SystemContext>
{
    DFL_MDIB_IMMUTABLE(PatientContextIndicator)

    public:
        /**
         * @brief Constructor.
         */
        PatientContextIndicator(const PatientContextIndicatorHandle& handle,
                                const DFL::NotNull<PatientContextDescriptorSharedPtr>& descriptor,
                                VersionCounter descriptorVersion,
                                const BasicHandle<SystemContext>& parent);

        /**
         * @brief Constructor that accepts a state and state version to ease the use with templates.
         * @details \note The state and state version are not used by the constructor.
         */
        PatientContextIndicator(const PatientContextIndicatorHandle& handle,
                                const DFL::NotNull<PatientContextDescriptorSharedPtr>& descriptor,
                                VersionCounter descriptorVersion,
                                const DFL::NotNull<PatientContextStateSharedPtr>& state,
                                VersionCounter stateVersion,
                                const BasicHandle<SystemContext>& parent);

};

inline PatientContextIndicator::PatientContextIndicator(const PatientContextIndicatorHandle& handle,
                                                        const DFL::NotNull<PatientContextDescriptorSharedPtr>& descriptor,
                                                        VersionCounter descriptorVersion,
                                                        const BasicHandle<SystemContext>& parent) :
        Impl::ContextDescriptorEntity<PatientContextIndicator, PatientContextDescriptorBuilder, PatientContextStateBuilder, SystemContext>(handle, descriptor, descriptorVersion, parent)
{
}

inline PatientContextIndicator::PatientContextIndicator(const PatientContextIndicatorHandle& handle,
                                                        const DFL::NotNull<PatientContextDescriptorSharedPtr>& descriptor,
                                                        VersionCounter descriptorVersion,
                                                        const DFL::NotNull<PatientContextStateSharedPtr>& /* state */,
                                                        VersionCounter /* stateVersion */,
                                                        const BasicHandle<SystemContext>& parent) :
        Impl::ContextDescriptorEntity<PatientContextIndicator, PatientContextDescriptorBuilder, PatientContextStateBuilder, SystemContext>(handle, descriptor, descriptorVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref PatientContextIndicatorSharedPtr for entity \ref PatientContextIndicator.
 */
using PatientContextIndicatorSharedPtr = SharedPtr<PatientContextIndicator>;

}
}
