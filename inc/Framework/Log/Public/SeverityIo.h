#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <iosfwd>

/**
 * @file Log/Public/SeverityIo.h
 *
 * @brief Contains operators for streaming @ref DFL::Log::Severity into @ref DFL::Format::Stream and std::ostream.
 *
 * @ingroup Log
 */
namespace DFL
{
namespace Log
{
class Severity;
/**
 * @brief Streams a string-representation of given severity into given stream.
 *
 * @snippet Log/Test/UnitTest/TestSeverity.cpp SevToStr
 * @snippet Log/Test/UnitTest/TestSeverity.cpp OStreaming
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& out, Severity const& sev);
}
}
namespace DFL
{
namespace Log
{
class Severity;
}
namespace Format
{
class Stream;
/**
 * @brief Streams a string-representation of given severity into given stream.
 *
 * @snippet Log/Test/UnitTest/TestSeverity.cpp SevToStr
 * @snippet Log/Test/UnitTest/TestSeverity.cpp FmtStreaming
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP Stream& operator<<(Stream& str, Log::Severity const& sev);
}
}
