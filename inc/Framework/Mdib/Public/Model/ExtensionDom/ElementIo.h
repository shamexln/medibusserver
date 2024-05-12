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
class Element;

/**
 * @brief Stream operator for output.
 * @param out returned output stream
 * @param element @ref DFL::Mdib::Dom::Element value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const Element& element);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param element @ref DFL::Mdib::Dom::Element value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const Element& element);

}
}
}
