#pragma once

#include <S31/Test/Private/S31TestUtilsExImp.h>

#include <string>

namespace S31::Log
{

/**
 * @brief Re-route all main DFL loggers to a log file.
 * @details
 * Has to be called immediately after @ref S31::startLogging().
 * This is intended to be used with tests and samples only.
 *
 * Internally this uses a buffering logger, an existing log file is overwritten.
 *
 * @param logNamePrefix Log file name without extension.
 */
S31_TESTUTILS_EXPIMP void useLogFile(const std::string& logNamePrefix);

/**
 * @brief Like useLogFile() but the file is not cleared at start.
 */
S31_TESTUTILS_EXPIMP void useLogFileAppend(const std::string& logNamePrefix);

}

