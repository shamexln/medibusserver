#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

#include <Framework/Format/Public/Stream.h>

#include <ostream>

namespace DFL
{
namespace Mdib
{
class Range;

/**
 * @brief Stream data to output stream.
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const Range& range);

/**
 * @brief Stream data to output stream.
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const Range& range);

} /* namespace Mdib */
} /* namespace DFL */
