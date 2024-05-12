#pragma once

#include <Framework/Mdib/Public/Model/Context/DateOfBirth.h>
#include <iosfwd>

namespace DFL
{
namespace Format
{
class Stream;
}

namespace Mdib
{

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
std::ostream& operator<<(std::ostream& out, const DateOfBirth& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
Format::Stream& operator<<(Format::Stream& out, const DateOfBirth& data);

inline std::ostream& operator <<(std::ostream& out, const DateOfBirth& data)
{
    out << data.isoString();
    return out;
}

inline Format::Stream& operator <<(Format::Stream& out, const DateOfBirth& data)
{
    out << data.isoString();
    return out;
}

}
}
