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

class LocationContext;

/**
 * @brief Generates a human readable representation of \ref LocationContext.
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, LocationContext const& data);

/**
 * @brief Stream operator for \ref LocationContext.
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, LocationContext const& data);

}
}
