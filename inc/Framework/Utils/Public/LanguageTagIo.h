#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <Framework/Format/Public/Stream.h>

#include <ostream>
#include <string>

namespace DFL
{
namespace Locale
{

class LanguageTag;

/**
 * @brief Generates a human readable representation.
 * @details Format is not specified. It is typically used for debug log messages.
 * @param out Sink for data
 * @param data Input data structure to convert to string
 * @return human readable representation of data.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, LanguageTag const& data);

/**
 * @brief Stream operator for \ref LanguageTag.
 * @param out Sink for data
 * @param data Data to stream
 * @return the referenced sink (first argument)
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, LanguageTag const& data);

} /* namespace Locale */
} /* namespace DFL */
