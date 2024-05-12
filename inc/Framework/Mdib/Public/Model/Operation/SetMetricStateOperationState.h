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
 * @brief Defines the volatile part of a \ref SetMetricStateOperation.
 * @ingroup Mdib
 */
class SetMetricStateOperationState: public AbstractOperationState
{
    DFL_MDIB_IMMUTABLE(SetMetricStateOperationState)

    public:
        /**
         * @brief Applies defaults from \ref AbstractOperationState.
         */
        SetMetricStateOperationState();

        /**
         * @brief Full constructor.
         */
        SetMetricStateOperationState(OperatingMode operatingMode,
                                     ExtensionTypes extensions = ExtensionTypes{ });
};

inline SetMetricStateOperationState::SetMetricStateOperationState() :
        AbstractOperationState()

{
}

inline SetMetricStateOperationState::SetMetricStateOperationState(OperatingMode operatingMode,
                                                                  ExtensionTypes extensions) :
        AbstractOperationState(operatingMode, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref SetMetricStateOperationStateSharedPtr for state \ref SetMetricStateOperationState.
 * @ingroup Mdib
 */
using SetMetricStateOperationStateSharedPtr = SharedPtr<SetMetricStateOperationState>;

} /* namespace Mdib */
} /* namespace DFL */
