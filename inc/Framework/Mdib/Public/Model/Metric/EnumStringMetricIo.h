#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{

namespace Format
{
class Stream;
}

namespace Mdib
{
class EnumStringMetric;

/**
 * @brief Generates a human readable representation of \ref EnumStringMetric.
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const EnumStringMetric& data);

/**
 * @brief Stream operator for \ref EnumStringMetric.
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const EnumStringMetric& data);

}
}
