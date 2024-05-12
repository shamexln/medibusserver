#pragma once

#include <Framework/Utils/Public/Uri.h>

#include <vector>

namespace DFL
{
namespace Net
{

/**
 * @brief   Helper functions for dealing with \ref DFL::Net::Uri objects.
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP UriHelper
{
    public:

        /**@brief The minimal reserved character set for any URI independent of the underlying scheme.
         */
        static const char* uriReservedCharacterSet;

        /**@brief Reserved character set for URLs.
         */
        static const char* urlReservedCharacterSet;

        /**@brief Percent encodes a given string using the reserved character set provided.
         * @details Apply this to parts of an URI only. Otherwise, delimiters may be encoded (usually, they are part of the reserved character set).
         *          The minimal reserved character set for URIs is defined by \ref DFL::Net::UriHelper::uriReservedCharacterSet and will be used as the default.
         *          Here are examples of URIs and their percent-encoded form:
         *          @snippet Utils/Test/UnitTest/TestUriHelper.cpp UriEncode
         *          Other schemes may define more characters to be reserved, e.g. \ref DFL::Net::UriHelper::urlReservedCharacterSet .
         *          Here are examples of URLs and their percent-encoded form:
         *          @snippet Utils/Test/UnitTest/TestUriHelper.cpp UrlEncode
         *          Note that encoding the same string twice results in unexpected behavior.
         * @return Percent-encoded string according to reserved character set.
         */
        static Uri::string_type percentEncode(const Uri::string_type& raw, const char* reserved = uriReservedCharacterSet);

        /**@brief Decodes a given percent-encoded string.
         * @details Never decode a string twice since %25 will decode to %. Decoding twice will lead to whatever comes after % to be interpreted as percent encoded.
         *          As opposed to encoding, there is no scheme-specific decoding method.
         *          This is because the percent character, by design, is always part of the reserved character set for percent-encoded strings.
         *          Therefore, the decoding procedure is the same independent of encoding.
         *          Here are examples of percent-encoded strings and their decoded form:
         * @snippet Utils/Test/UnitTest/TestUriHelper.cpp UriDecode
         * @return Decoded String.
         */
        static Uri::string_type decode(const Uri::string_type& percentEncoded);

        /**@brief Decodes a vector of percent-encoded strings.
         * @details Never decode a vector twice since %25 will decode to %. Decoding twice will lead to whatever comes after % to be interpreted as percent encoded.
         *          Here are examples of segments and their decoded form:
         * @snippet Utils/Test/UnitTest/TestUriHelper.cpp DecodeSegments
         * @return Vector of decoded strings.
         */
        static std::vector<Uri::string_type> decode(const std::vector<Uri::string_type>& segments);
};

}
}
