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
 * @brief Defines the volatile part of a \ref SetContextStateOperation.
 * @ingroup Mdib
 */
class SetContextStateOperationState: public AbstractOperationState
{
    DFL_MDIB_IMMUTABLE(SetContextStateOperationState)

    public:
        /**
         * @brief Applies defaults from \ref AbstractOperationState.
         */
        SetContextStateOperationState();

        /**
         * @brief Full constructor.
         */
        SetContextStateOperationState(OperatingMode operatingMode,
                                      ExtensionTypes extensions = ExtensionTypes{ });
};

inline SetContextStateOperationState::SetContextStateOperationState() :
        AbstractOperationState()
{
}

inline SetContextStateOperationState::SetContextStateOperationState(OperatingMode operatingMode,
                                                                    ExtensionTypes extensions) :
        AbstractOperationState(operatingMode, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref SetContextStateOperationStateSharedPtr for state \ref SetContextStateOperationState.
 * @ingroup Mdib
 */
using SetContextStateOperationStateSharedPtr = SharedPtr<SetContextStateOperationState>;

} /* namespace Mdib */
} /* namespace DFL */
