#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Public/SecurityState.h>

#include <iosfwd>

namespace DFL
{
namespace Log
{
/**
 * @brief Streams a string-representation of given SecurityState into given
 * stream.
 *
 * @snippet Log/Test/UnitTest/TestSecurityState.cpp SecToStr
 * @snippet Log/Test/UnitTest/TestSecurityState.cpp OStreaming
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& out,
                                        SecurityState ss);
}
}

namespace DFL
{

namespace Format
{
class Stream;
/**
 * @brief Streams a string-representation of given SecurityState into given
 * stream.
 *
 * @snippet Log/Test/UnitTest/TestSecurityState.cpp SecToStr
 * @snippet Log/Test/UnitTest/TestSecurityState.cpp FmtStreaming
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP Stream& operator<<(Stream& str, Log::SecurityState ss);
}
}
