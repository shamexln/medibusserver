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
 * @brief Describes the volatile part of an \ref ActivateOperation.
 * @ingroup Mdib
 */
class ActivateOperationState: public AbstractOperationState
{
    DFL_MDIB_IMMUTABLE(ActivateOperationState)

    public:
        /**
         * @brief Applies defaults from \ref AbstractOperationState.
         */
        ActivateOperationState();

        /**
         * @brief Full constructor.
         */
        ActivateOperationState(OperatingMode operatingMode,
                               ExtensionTypes extensions = ExtensionTypes{ });
};

inline ActivateOperationState::ActivateOperationState() :
        AbstractOperationState()
{
}

inline ActivateOperationState::ActivateOperationState(OperatingMode operatingMode,
                                                      ExtensionTypes extensions) :
        AbstractOperationState(operatingMode, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref ActivateOperationStateSharedPtr for state \ref ActivateOperationState.
 * @ingroup Mdib
 */
using ActivateOperationStateSharedPtr = SharedPtr<ActivateOperationState>;

} /* namespace Mdib */
} /* namespace DFL */
