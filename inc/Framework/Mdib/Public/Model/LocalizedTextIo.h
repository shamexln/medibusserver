#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Format/Public/Stream.h>
#include <ostream>

namespace DFL
{
namespace Mdib
{
class LocalizedText;

/**
 * @brief Generates a human readable representation.
 * @details Format is not specified. It is typically used for debug log messages.
 * @param out Sink for data
 * @param data Input data structure to convert to string
 * @return human readable representation of data.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, LocalizedText const& data);

/**
 * @brief Stream operator for \ref LocalizedText.
 * @param out Sink for data
 * @param data Data to stream
 * @return the referenced sink (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, LocalizedText const& data);

} /* namespace Mdib */
} /* namespace DFL */
