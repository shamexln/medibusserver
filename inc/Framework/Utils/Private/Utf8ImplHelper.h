#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Utf8Constants.h>

#include <string>

namespace DFL::Locale::Impl
{

class DFL_UTILS_EXPIMP Utf8ImplHelper
{
    public:
        /**
         * @brief Encodes a code point in UTF-8.
         */
        static std::string toUtf8(Utf8Constants::CodePoint codePoint);

        /**
         * @brief Checks whether the given code point is a valid Unicode code point.
         * @details Unicode only allows specific code points
         * (no surrogates and no code points outside UTF-16 encoding).
         */
        static bool validUnicodeCodePoint(Utf8Constants::CodePoint codePoint);

    private:
        static std::string toUtf8With1ByteEncoding(Utf8Constants::CodePoint codePoint);
        static std::string toUtf8With2ByteEncoding(Utf8Constants::CodePoint codePoint);
        static std::string toUtf8With3ByteEncoding(Utf8Constants::CodePoint codePoint);
        static std::string toUtf8With4ByteEncoding(Utf8Constants::CodePoint codePoint);
};

}
