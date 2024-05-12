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
namespace Ext
{
class AlertSignalFlashing;

/**
 * @brief Stream operator for output.
 * @param out returned output stream
 * @param value value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out,
                                         const AlertSignalFlashing& value);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param value value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out,
                                           const AlertSignalFlashing& value);

}
}
}
