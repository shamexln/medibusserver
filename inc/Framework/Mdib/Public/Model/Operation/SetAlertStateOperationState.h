#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationState.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines the volatile part of a \ref SetAlertStateOperation.
 * @ingroup Mdib
 */
class SetAlertStateOperationState: public AbstractOperationState
{
    DFL_MDIB_IMMUTABLE(SetAlertStateOperationState)

    public:
        /**
         * @brief Applies defaults from \ref AbstractOperationState.
         */
        SetAlertStateOperationState();

        /**
         * @brief Full constructor.
         */
        SetAlertStateOperationState(OperatingMode operatingMode,
                                    ExtensionTypes extensions = ExtensionTypes{ });
};

inline SetAlertStateOperationState::SetAlertStateOperationState() :
        AbstractOperationState()
{
}

inline SetAlertStateOperationState::SetAlertStateOperationState(OperatingMode operatingMode,
                                                                ExtensionTypes extensions) :
        AbstractOperationState(operatingMode, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref SetAlertStateOperationStateSharedPtr for state \ref SetAlertStateOperationState.
 * @ingroup Mdib
 */
using SetAlertStateOperationStateSharedPtr = SharedPtr<SetAlertStateOperationState>;

} /* namespace Mdib */
} /* namespace DFL */
