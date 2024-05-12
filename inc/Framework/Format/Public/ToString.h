#pragma once


#include <Framework/Format/Public/Stream.h>

namespace DFL
{
namespace Format
{
/**
 * @brief Converts given parameter to string via format stream.
 *
 * @tparam FormatStreamable Type must be streamable via format stream.
 *
 * @ingroup Format
 */
template <class FormatStreamable>
std::string toString(const FormatStreamable& streamable);

template <class FormatStreamable>
inline std::string toString(const FormatStreamable& streamable)
{
    // NOLINTNEXTLINE(misc-const-correctness)
    Stream str;
    str << streamable;
    return str.cStr();
}
}
}
