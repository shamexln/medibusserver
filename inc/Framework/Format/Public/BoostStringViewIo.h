#pragma once

#include <Framework/Format/Private/ExpImp.h>

#include <boost/utility/string_view.hpp>

namespace DFL
{
namespace Format
{
class Stream;
}
}
namespace boost
{
/**
 * @brief Makes boost::string_view streamable into a @ref DFL::Format::Stream.
 *
 * @ingroup Format
 */
DFL_FORMAT_EXPIMP ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str,
                                                    string_view sv);
}
