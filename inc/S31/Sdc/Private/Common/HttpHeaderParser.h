#pragma once

#include <S31/Sdc/Private/Common/EncodingType.h>

#include <map>
#include <string>
#include <string_view>

namespace S31::Sdc::Impl::HttpHeaderParser
{

/**
 * @brief Extracts the preferred compression type from given Accept-Encoding string.
 *
 * @details Preferences in descending order are [lz4, x-lz4, gzip, None]
 * @param acceptEncodings header field (e.g. obtained from a HttpHeader)
 * @return preferred compression type.
 * @ingroup S31SdcCommon
 */
EncodingType getPreferredCompression(std::string_view acceptEncodings);


/**
 * @brief Map type for encoding and weight.
 * @details \c std::less<> is used to allow searching with string views without creating an \c std::string instance.
 */
using EncodingWeights = std::map<std::string, std::string, std::less<>>;

/**
 * @brief Parses the accept encoding field and returns all possible compressions with their weight.
 *        See <a href="https://tools.ietf.org/html/rfc2616#page-102">RFC2616</a> for reference.
 * @param acceptEncodings: The accept encoding field from the http header
 * @return map of compressions with their weight
 * @ingroup S31SdcCommon
 */
EncodingWeights getCompression(std::string_view acceptEncodings);

/**
 * @brief Returns a Http Content-Encoding header for a given compression type.
 * @param type compression type for which to create the Http header field.
 * @return Http Content Encoding header field for the compression type.
 * @ingroup S31SdcCommon
 */
const char* getHttpContentEncodingHeader(EncodingType type);

}
