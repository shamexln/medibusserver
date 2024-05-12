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
class CodedValueTranslation;

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, CodedValueTranslation const& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, CodedValueTranslation const& data);

} /* namespace Mdib */
} /* namespace DFL */
