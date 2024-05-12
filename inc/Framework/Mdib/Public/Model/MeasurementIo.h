#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <ostream>
#include <iosfwd>

namespace DFL
{

namespace Format
{
class Stream;
}

namespace Mdib
{
class Measurement;

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param measurement The measurement to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const Measurement& measurement);

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param measurement the measurement to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const Measurement& measurement);

} /* namespace Mdib */
} /* namespace DFL */
