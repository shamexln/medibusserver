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
namespace Dom
{
class Node;

/**
 * @brief Stream operator for output.
 * @param out returned output stream
 * @param node @ref DFL::Mdib::Dom::Node value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const Node& node);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param node @ref DFL::Mdib::Dom::Node value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const Node& node);

}
}
}
