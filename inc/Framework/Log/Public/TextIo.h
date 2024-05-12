#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
namespace Format
{
class Stream;
}

namespace Log
{

class Text;

/**
 * @brief Streams text object to ostream.
 * @param out Stream to put text object in.
 * @param txt Text object to be put into stream
 * @return The given stream object.
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& out, Text const& txt);

/**
 * @brief Streams text object to text stream.
 * @param out Stream to put text object in.
 * @param txt Text object to be put into stream
 * @return The given stream object.
 * @ingroup Log
 */
DFL_LOG_EXPIMP Format::Stream& operator<<(Format::Stream& out, Text const& txt);

}
}
