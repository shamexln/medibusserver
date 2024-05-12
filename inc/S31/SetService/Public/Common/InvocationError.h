#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::SetService
{

/**
 * @brief Errors that occur during operation call.
 * @ingroup S31SetService
 */
enum class InvocationError
{
    /**
     * @brief An unspecified error has occurred, no more information about the error is available.
     */
    Unspecified,

    /**
     * @brief Unknown operation, the HANDLE to the operation object is not known.
     */
    Unknown,

    /**
     * @brief The HANDLE to the operation object does not match the invocation request MESSAGE.
     * @details Example: A SetString message is received, in which the SetString/OperationHandleRef
     * points to / references a SetValue message.
     * (Message type does not match the type from the operation descriptor.)
     */
    Invalid,

    /**
     * @brief Another type of error has occurred, more information on the error may be available.
     */
    Other
};
DFL_ENUM_CLASS_STREAM_OPERATOR(InvocationError, (Unspecified)(Unknown)(Invalid)(Other))

}
