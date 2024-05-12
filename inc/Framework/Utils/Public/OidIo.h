#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
class Oid;
/**
 * @brief Streams the URI string.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, Oid const& data);
}
namespace DFL
{
class Oid;
namespace Format
{
class Stream;
/**
 * @brief Streams the URI string.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Stream& operator<<(Stream& out, DFL::Oid const& data);
}
}
