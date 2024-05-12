#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <string>

namespace DFL
{
namespace Locale
{

/**
 * @brief Constants used in Utf8 handling.
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Utf8Constants
{
    public:
        /**
         * @brief Type for code points for UTF-8 encoding.
         * @details The code point in UTF-8 represents the unicode code point.
         * It is encoded with multibyte encoding (1 to 4 byte).
         * Code points have up to 21 bit, but not all values are allowed.
         */
        using CodePoint = unsigned int;

        /**
         * @brief UTF-8 encoding of replacement character (U+FFFD).
         * @details The replacement character is special.
         * It is used in UTF-8 decoding for invalid byte sequences.
         * Hint: Do not use this character in identifier.
         * http://www.fileformat.info/info/unicode/char/fffd/
         */
        static const std::string ReplacementCharacterString;
};

} /* namespace Locale */
} /* namespace DFL */
