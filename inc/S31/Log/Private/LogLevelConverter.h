#pragma once

#include <Framework/Log/Public/Severity.h>

#include <string>

namespace S31::Log::Impl
{

/**
 * \brief Tool to convert string based log levels to the S31::LogLevel enum.
 *
 * \ingroup S31Log
 */
class LogLevelConverter
{
    public:

        /**
         * @brief Parses log level from string.
         * @param logLevelString The log level to parse. Invalid log levels are parsed to DFL::Log::Success.
         */
        static DFL::Log::Severity convert(const std::string& logLevelString);
};

}
