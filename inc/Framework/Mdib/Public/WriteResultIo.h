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
class WriteResult;

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data WriteResult to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const WriteResult& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data WriteResult to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const WriteResult& data);

}
}
