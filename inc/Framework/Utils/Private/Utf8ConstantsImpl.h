#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Utf8Constants.h>

namespace DFL
{
namespace Locale
{
namespace Impl
{

class DFL_UTILS_EXPIMP Utf8ConstantsImpl
{
    public:

        /**
         * @name Valid code point range
         * @brief Unicode has a code point range from \c 0x0000 to \c 0x10FFFF.
         * @details The allowed range is the maximum range that is encodable in UTF-16.
         * In UTF-8 it would be possible to encode larger code points,
         * but these are not valid Unicode code points.
         */
        ///@{
        static const Utf8Constants::CodePoint MinValidCodePoint = 0x0000;
        static const Utf8Constants::CodePoint MaxValidCodePoint = 0x10FFFF;
        ///@}


        /**
         * @name Invalid code points for errors
         * @brief Used code point to report invalid byte sequences.
         * @details Parsing errors lead to error code points for the invalid byte sequence.
         */
        ///@{


        /**
         * Code point in case of end of input stream.
         */
        static const Utf8Constants::CodePoint ErrorCodePointEndOfSequence = 0xffffffffU;

        /**
         * Code point in case of overlong encoding in input stream.
         */
        static const Utf8Constants::CodePoint ErrorCodePointOverlongEncoding = 0xfffffffeU;

        /**
         * Code point for unexpected continuation byte in input stream.
         */
        static const Utf8Constants::CodePoint ErrorCodePointUnexpectedContinuationByte = 0xfffffffdU;

        /**
         * Code point in case of missing continuation byte for a multi byte encoding.
         */
        static const Utf8Constants::CodePoint ErrorCodePointMissingContinuationByte = 0xfffffffcU;
        ///@}


        /**
         * @name Unicode surrogates
         * @brief Unicode surrogates are invalid code points.
         * @details Unicode surrogates are reserved for UTF-16 encoding.
         * They are not valid code point and shall never appears in valid UTF-8
         * byte sequences.
         */
        ///@{
        static const Utf8Constants::CodePoint FirstSurrogateCodePoint = 0xD800;
        static const Utf8Constants::CodePoint LastSurrogateCodePoint = 0xDFFF;
        ///@}

        /**
         * @name Code point ranges.
         * @details
         * Depending on the code point different encoding (1, 2, 3, or 4 byte encodings)
         * are used.
         */
        ///@{
        static const Utf8Constants::CodePoint FirstCodePointFor1ByteEncoding = 0x0000;
        static const Utf8Constants::CodePoint LastCodePointFor1ByteEncoding = 0x007F;
        static const Utf8Constants::CodePoint FirstCodePointFor2ByteEncoding = 0x0080;
        static const Utf8Constants::CodePoint LastCodePointFor2ByteEncoding = 0x07FF;
        static const Utf8Constants::CodePoint FirstCodePointFor3ByteEncoding = 0x0800;
        static const Utf8Constants::CodePoint LastCodePointFor3ByteEncoding = 0xFFFF;
        static const Utf8Constants::CodePoint FirstCodePointFor4ByteEncoding = 0x10000;
        static const Utf8Constants::CodePoint LastCodePointFor4ByteEncoding = 0x10FFFF;
        ///@}
};

} /* namespace Impl */
} /* namespace Locale */
} /* namespace DFL */
