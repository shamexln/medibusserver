#pragma once

#include <Framework/Format/Private/ExpImp.h>
#include <Framework/Format/Public/Stream.h>

#include <system_error>

namespace DFL
{
namespace Format
{
/**
 * @brief Same as streaming std::error_code to std::ostream but message() being
 * appended.
 *
 * @snippet Format/Test/UnitTest/TestStdErrorCodeIo.cpp StreamErrorCode
 *
 * @ingroup Format
 */
DFL_FORMAT_EXPIMP Stream& operator<<(Stream& str, const std::error_code& ec);
}
}
