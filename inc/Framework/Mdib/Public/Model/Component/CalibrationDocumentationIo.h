#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <iosfwd>
#include <ostream>

namespace DFL
{
namespace Format
{
class Stream;
}

namespace Mdib
{
class CalibrationDocumentation;

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param calibDoc to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, CalibrationDocumentation const& calibDoc);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param calibDoc to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, CalibrationDocumentation const& calibDoc);

} /* namespace Mdib */
} /* namespace DFL */
