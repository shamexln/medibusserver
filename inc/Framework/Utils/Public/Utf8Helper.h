#pragma once

#include <Framework/Utils/Private/ExpImp.h>

namespace DFL
{
namespace Locale
{
class Utf8;

/**
 * @brief Checks if an UTF-8 string contains the unicode replacement character (U+FFFD).
 * @details If a unicode string contains the replacement character, it indicates,
 * that the string is invalid. A strategy for UTF-8 decoder is
 * to replace invalid byte sequences with the replacement character (U+FFFD).
 *
 * @param string UTF-8 string to check for replacement character.
 * @return \c true in case the string contains the unicode replacement character.
 *
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP containsReplacementCharacter(const Utf8& string);

} /* namespace Locale */
} /* namespace DFL */
