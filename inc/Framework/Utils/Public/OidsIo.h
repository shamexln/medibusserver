#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
class Oids;
/**
 * @brief Creates readable form of given Oids.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& str, const Oids& oids);
}
namespace DFL
{
class Oids;
namespace Format
{
class Stream;
/**
 * @brief Streams buffer into format stream.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Stream& operator<<(Stream& str, const DFL::Oids& oids);
}
}
