#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <iosfwd>

/**
 * @file Log/Public/LoggerIo.h
 *
 * @brief Contains operators for streaming @ref DFL::Log::Logger into
 * std::ostream and @ref DFL::Format::Stream.
 *
 * @ingroup Log
 */
namespace DFL
{
namespace Log
{
class Logger;
}
namespace Format
{
class Stream;
/**
 * @brief Streams a string-representation of given logger into given stream.
 *
 * @snippet Log/Test/UnitTest/TestLogger.cpp Streaming
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP Stream& operator<<(Stream& str, const Log::Logger& l);
}
}
namespace DFL
{
namespace Log
{
class Logger;
/**
 * @brief Streams a string-representation of given logger into given stream.
 *
 * @snippet Log/Test/UnitTest/TestLogger.cpp Streaming
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& str, const Logger& l);
}
}
