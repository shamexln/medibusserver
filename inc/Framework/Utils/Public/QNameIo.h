#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <iosfwd>
#include <Framework/Utils/Public/QName.h>

namespace DFL
{

namespace Format
{
class Stream;
}

class QName;

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param qname @ref DFL::QName value to stream
 * @return the passed stream (first argument)
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, QName const& qname);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param qname @ref DFL::QName value to stream
 * @return the passed stream (first argument)
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Format::Stream& operator<<(Format::Stream& out, QName const& qname);

}
