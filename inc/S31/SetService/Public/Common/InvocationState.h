#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::SetService
{

/**
 * @brief States that can be accepted during an operation invocation.
 * @ingroup S31SetService
 */
enum class InvocationState
{
    Waiting,                 //!< The operation has been queued and waits for execution.

    Started,                 //!< The execution of the operation has been started.

    Cancelled,               //!< The execution has been cancelled by the service provider.

    CancelledManually,       //!< The execution has been cancelled by the operator.

    Finished,                //!< The execution has been finished.

    FinishedWithModification,//!< As the requested target value could not be reached, the next best value has been chosen and used as target value.

    Failed                   //!< The execution failed.
};
DFL_ENUM_CLASS_STREAM_OPERATOR(InvocationState, (Waiting)(Started)(Cancelled)(CancelledManually)(Finished)(FinishedWithModification)(Failed))

}
