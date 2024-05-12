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
 * @brief Defines the volatile part of a \ref SetComponentStateOperation.
 * @ingroup Mdib
 */
class SetComponentStateOperationState: public AbstractOperationState
{
    DFL_MDIB_IMMUTABLE(SetComponentStateOperationState)

    public:
        /**
         * @brief Applies defaults from \ref AbstractOperationState.
         */
        SetComponentStateOperationState();

        /**
         * @brief Full constructor.
         */
        SetComponentStateOperationState(OperatingMode operatingMode,
                                        ExtensionTypes extensions = ExtensionTypes{ });
};

inline SetComponentStateOperationState::SetComponentStateOperationState() :
        AbstractOperationState()
{
}

inline SetComponentStateOperationState::SetComponentStateOperationState(OperatingMode operatingMode,
                                                                        ExtensionTypes extensions) :
        AbstractOperationState(operatingMode, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref SetComponentStateOperationStateSharedPtr for state \ref SetComponentStateOperationState.
 * @ingroup Mdib
 */
using SetComponentStateOperationStateSharedPtr = SharedPtr<SetComponentStateOperationState>;

} /* namespace Mdib */
} /* namespace DFL */
