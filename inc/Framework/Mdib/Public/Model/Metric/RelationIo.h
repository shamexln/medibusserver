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
class Relation;

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param relation to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, Relation const& relation);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param relation to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, Relation const& relation);

} /* namespace Mdib */
} /* namespace DFL */
