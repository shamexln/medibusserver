#pragma once

#include <iosfwd>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Format
{
class Stream;
}

namespace Mdib
{
class ActivateArgument;

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, ActivateArgument const& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, ActivateArgument const& data);

} /* namespace Mdib */
} /* namespace DFL */
