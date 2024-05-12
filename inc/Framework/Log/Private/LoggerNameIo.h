#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
namespace Log
{
namespace Impl
{
class LoggerName;
}
}
namespace Format
{
class Stream;
/**
 * @brief Makes a /-separted view of contained hierachy.
 *
 * @snippet Log/Test/UnitTest/TestLoggerName.cpp FmtStream
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP Stream& operator<<(Stream& str, const Log::Impl::LoggerName& name);
}
}
namespace DFL
{
namespace Log
{
namespace Impl
{
class LoggerName;
/**
 * @brief Makes a /-separted view of contained hierachy.
 *
 * @snippet Log/Test/UnitTest/TestLoggerName.cpp OStream
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& str, const LoggerName& name);
}
}
}
