#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Alert/AlertActivation.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Acts as a base class for all alert states that contain dynamic/volatile alert meta information.
 * @ingroup Mdib
 */
class AbstractAlertState: public Impl::HasExtensions
{
    DFL_MDIB_IMMUTABLE(AbstractAlertState)

    public:
        /**
         * @brief The activation state indicates if the underlying alert system will activate the condition.
         * @return Activation state.
         */
        AlertActivation activationState() const;

    protected:
        /**
         * @brief Constructor that sets the \ref AbstractAlertState::activationState() "activation state" to \ref AlertActivation::On "on"
         */
        AbstractAlertState() = default;

        /**
         * @brief Full constructor.
         */
        AbstractAlertState(AlertActivation activationState,
                           ExtensionTypes&& extensions);

        ~AbstractAlertState() = default;

    private:
        AlertActivation m_activationState = AlertActivation::On;
};

inline AbstractAlertState::AbstractAlertState(AlertActivation activationState,
                                              ExtensionTypes&& extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_activationState(activationState)
{
}

inline AlertActivation AbstractAlertState::activationState() const
{
    return m_activationState;
}

} /* namespace Mdib */
} /* namespace DFL */
