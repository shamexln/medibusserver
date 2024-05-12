#pragma once

#include <S31/Log/S31Only/ComponentLogger.h>
#include <S31/Log/Private/ServiceLogger.h>

#include <Framework/Format/Public/Stream.h>

namespace S31::Log::Impl
{

/**
 * @brief Write a log message to a logger.
 * @details see log macro group: S31_STREAM_*.
 * @ingroup S31Log
 */
template<class ... Args>
inline void writeStreamLogMessage(const DFL::Log::Logger& logger, const DFL::Log::Severity& level, const char* file, int line, Args&& ... args) noexcept
{
    try
    {
        if (!logger.is(level))
        {
            return;
        }
        // NOLINTNEXTLINE(misc-const-correctness)
        DFL::Format::Stream stream;
        (stream << ... << args);
        S31::Log::Impl::ComponentLogger::writeBufferMessage(logger, level, file, line, stream.cStr());
    }
    catch(...)
    {
    }
}

/**
 * @brief Write a log message to service logger.
 * @details See log macro group: S31_SERVICE_STREAM_*.
 * @ingroup S31Log
 */
// NOLINTBEGIN(bugprone-easily-swappable-parameters)
template<class ... Args>
inline void writeServiceStreamLogMessage(const DFL::Log::Severity& level, const char* file, int line, unsigned int remosCode, Args&& ... args) noexcept
// NOLINTEND(bugprone-easily-swappable-parameters)
{
    try
    {
        // NOLINTNEXTLINE(misc-const-correctness)
        DFL::Format::Stream stream;
        (stream << ... << args);
        S31::Log::Impl::ServiceLogger::writeBufferMessage(level, file, line, remosCode, stream.cStr());
    }
    catch(...)
    {
    }
}

/**
 * @brief Write a log message to a logger that is given by it's name.
 * @details To be used in header implementation (where no logger reference at file scope is available).
 * See log macro group: S31_STREAM_*_LOGGER.
 * @ingroup S31Log
 */
template<class ... Args>
inline void writeStreamLogMessageToLoggerByName(
        const std::string& loggerName, const DFL::Log::Severity& level, const char* file, int line, Args&& ... args) noexcept
{
    try
    {
        auto& logger = S31::Log::Impl::ComponentLogger::getComponentLogger(loggerName);
        if (!logger.is(level))
        {
            return;
        }
        // NOLINTNEXTLINE(misc-const-correctness)
        DFL::Format::Stream stream;
        (stream << ... << args);
        S31::Log::Impl::ComponentLogger::writeBufferMessage(logger, level, file, line, stream.cStr());
    }
    catch (...)
    {
        // Writing log message failed, looks like we cannot log anything
    }
}

}
