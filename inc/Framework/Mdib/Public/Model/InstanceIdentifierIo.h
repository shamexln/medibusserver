#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{

namespace Format
{
class Stream;
} /* namespace Format */

namespace Mdib
{
class InstanceIdentifier;

/**
 * @param out output stream
 * @param ii data to stream out
 * @return passed output stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const InstanceIdentifier& ii);

/**
 * @param out output stream
 * @param ii data to stream out
 * @return passed output stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, InstanceIdentifier const& ii);

} /* namespace Mdib */
} /* namespace DFL */
