#pragma once

#include <Framework/Format/Private/ExpImp.h>

#include <string_view>

namespace DFL::Format
{
class Stream;

/**
 * @brief Makes std::string_view streamable into a @ref DFL::Format::Stream.
 *
 * @ingroup Format
 */
DFL_FORMAT_EXPIMP ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, std::string_view sv);
}
