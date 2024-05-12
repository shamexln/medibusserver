#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/ComponentActivation.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Dynamic part of a \ref SystemContext.
 * @ingroup Mdib
 */
class SystemContextState: public Impl::HasExtensions
{
    public:
        /**
         * @brief Sets the \ref SystemContextState::activationState() "activation state" to \ref ComponentActivation::On "on".
         */
        SystemContextState() = default;

        /**
         * @brief Full constructor.
         */
        explicit SystemContextState(ComponentActivation activationState,
                                    ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief See \ref ComponentActivation.
         */
        ComponentActivation activationState() const;

    private:
        ComponentActivation m_activationState{ComponentActivation::On};
};

inline SystemContextState::SystemContextState(ComponentActivation activationState,
                                              ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_activationState(activationState)
{
}

inline ComponentActivation SystemContextState::activationState() const
{
    return m_activationState;
}

/**
 * @brief Definition of shared pointer type \ref SystemContextStateSharedPtr for state \ref SystemContextState.
 * @ingroup Mdib
 */
using SystemContextStateSharedPtr = SharedPtr<SystemContextState>;


} /* namespace Mdib */
} /* namespace DFL */
