#pragma once

#include <iosfwd>
#include <Framework/Utils/Private/ExpImp.h>

namespace DFL
{
class Sha1;
namespace Format
{
class Stream;
}

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, const Sha1& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Format::Stream& operator<<(Format::Stream& out, const Sha1& data);

}
