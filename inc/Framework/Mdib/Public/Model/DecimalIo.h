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
class Decimal;

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param decimal numeric value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, Decimal const& decimal);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param decimal numeric value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, Decimal const& decimal);

} /* namespace Mdib */
} /* namespace DFL */
