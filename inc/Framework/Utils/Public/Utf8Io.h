#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <Framework/Format/Public/Stream.h>

#include <ostream>

namespace DFL
{
namespace Locale
{
class Utf8;

/**
 * @brief Streams the UTF-8 string.
 * @param out Sink for data
 * @param data Input UTF-8 to stream.
 * @return Passed stream.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, const Utf8& data);

} /* namespace Locale */

namespace Format
{

/**
 * @brief Streams the UTF-8 string.
 * @param out Sink for data
 * @param data Input UTF-8 to stream.
 * @return Passed stream.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Stream& operator<<(Stream& out, const Locale::Utf8& data);

} /* namespace Format */
} /* namespace DFL */
