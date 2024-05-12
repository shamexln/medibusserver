#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Utf8Constants.h>

#include <string_view>

namespace DFL::Locale::Impl
{
/**
 * @brief Iterates over a non-owning UTF-8 encoded string and provides the code point.
 */
class DFL_UTILS_EXPIMP NonOwningUtf8Iterator
{
    public:
        explicit NonOwningUtf8Iterator(std::string_view utf8);

        NonOwningUtf8Iterator& operator++();
        bool endOfStream() const;

        /**
         * @brief Gets next code point from UTF-8 string.
         * @details In case of invalid byte sequences, a corresponding error code point is returned.
         */
        Utf8Constants::CodePoint getCodePoint() const;

    private:
        void parseCodePoint();

        /**
         * @brief Return EOF or next byte from input stream.
         * @return EOF or next byte from input stream.
         */
        Utf8Constants::CodePoint getNextChar();

        /**
         * @brief Get next byte if it is a UTF-8 continuation byte.
         * @return EOF or continuation byte.
         */
        Utf8Constants::CodePoint getNextContinuationByte();

        static bool isStartOf1ByteEncoding(Utf8Constants::CodePoint byte);
        static bool isStartOf2ByteEncoding(Utf8Constants::CodePoint byte);
        static bool isStartOf3ByteEncoding(Utf8Constants::CodePoint byte);
        static bool isStartOf4ByteEncoding(Utf8Constants::CodePoint byte);
        static bool isContinuationByte(Utf8Constants::CodePoint byte);

        std::string_view m_utf8it;
        Utf8Constants::CodePoint m_codePoint;
};
}
