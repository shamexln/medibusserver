#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::SetService
{

/**
 * @brief Errors that occur on the client side before any report from the device has been received.
 * @ingroup S31SetService
 */
enum class ClientError
{
    NoError = 0,                        ///< There is no client error
    OperationHandleNotFound,            ///< The requested operation could not be found in the remote MDIB.
    InaccessibleCommunicationEndpoint,  ///< Communication endpoint not accessible.
    OperatingModeNotEnabled,            ///< The requested operation was not enabled.
    MissingDependency,                  ///< A required weak reference was not available during request processing.
    DataConversionFailed,               ///< Request payload data could not be mapped.
    PayloadMissing,                     ///< Request does not have a proposed state
    EventServiceNotSubscribed,          ///< Not subscribed to event service of requested data type
    SafetyClassificationMissing,        ///< Operation is not associated with any SafetyClassification
    InvalidLength,                      ///< Requested string length is more than allowed MaxLength
    NotInAllowedValues,                 ///< Requested value not one of AllowedValues
    InvalidInstanceIdentifierRoot       ///< InstanceIdentifier root is not valid
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ClientError, (NoError)
                               (OperationHandleNotFound)(InaccessibleCommunicationEndpoint)(OperatingModeNotEnabled)
                               (MissingDependency)(DataConversionFailed)(PayloadMissing)(EventServiceNotSubscribed)
                               (SafetyClassificationMissing)(InvalidLength)(NotInAllowedValues)(InvalidInstanceIdentifierRoot))

}
