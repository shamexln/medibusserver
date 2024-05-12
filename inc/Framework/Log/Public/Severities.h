#pragma once

#include <Framework/Log/Public/SeverityTypes.h>
#include <Framework/Log/Private/ExpImp.h>

/**
 * @ingroup Log
 * @{
 *
 * @file
 * @brief Definition of different logging severities.
 *
 * Trace, success, info, warning and error are the different severities.
 * In that order these severities make an ascending sequence.
 * This is used for filtering messages.
 * @code
 * DFL_LOG_SUCCESS_WITH(logger, "This message gets logged");
 * // Trace, Success and Info shall no longer be logged
 * logger.severity(Warning);
 * DFL_LOG_SUCCESS_WITH(logger, "This message is not processed");
 * @endcode
 */
namespace DFL
{
namespace Log
{

/**
 * @brief Use this for debug purposes. By default trace messages are not logged
 * since the default severity of a logger is success.
 */
extern DFL_LOG_EXPIMP TraceType const Trace;

/**
 * @brief Indicates the successful completion of an transaction.
 */
extern DFL_LOG_EXPIMP SuccessType const Success;

/**
 * @brief Use this for providing informations about ongoing processes.
 */
extern DFL_LOG_EXPIMP InfoType const Info;

/**
 * @brief Indicate an unusual event which will be handled safely.
 */
extern DFL_LOG_EXPIMP WarningType const Warning;

/**
 * @brief Indicate an event which must be handled by the client.
 */
extern DFL_LOG_EXPIMP ErrorType const Error;

}
}
/** @} */
