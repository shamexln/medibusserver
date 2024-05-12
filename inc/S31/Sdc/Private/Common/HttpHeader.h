#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Base/S31Only/NtStringView.h>
#include <S31/Sdc/Private/Common/Http/HttpTypes.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Impl::HttpHeader
{
namespace Field
{
/**
 * @brief HTTP header field constant for accept encoding.
 * @ingroup S31SdcCommon
 */
inline const char* AcceptEncoding()
{
    return "Accept-Encoding";
}

/**
 * @brief HTTP header field constant for content encoding.
 * @ingroup S31SdcCommon
 */
inline const char* ContentEncoding()
{
    return "Content-Encoding";
}

/**
 * @brief Creates a header field with comma separated values.
 * @details Here are examples of header fields + values and the field created when using this function.
 * @snippet S31/Sdc/Test/UnitTest/Private/Common/TestHttpHeader.cpp HeaderFields
 * @ingroup S31SdcCommon
 */
std::string create(const char* fieldName, std::initializer_list<std::string> fieldValues);
}

namespace ContentCoding
{
/**
 * @brief Constant for lz4 compression (without "x-" prefix).
 * @ingroup S31SdcCommon
 */
constexpr NtStringView Lz4{"lz4"};

/**
 * @brief Constant for lz4 compression with "x-" prefix.
 * @ingroup S31SdcCommon
 */
constexpr NtStringView Xlz4{"x-lz4"};

/**
 * @brief Constant for gzip compression.
 * @ingroup S31SdcCommon
 */
constexpr NtStringView GZip{"gzip"};

/**
 * @brief Checks for a valid lz4 coding (lz4, x-lz4).
 * @ingroup S31SdcCommon
 */
bool isLz4(const char* coding);

}

namespace ContentType
{
/**
 * @brief Create a content-type string for soap messages
 * @details Produces the content type application/soap+xml with an optional
 * soap action appended.
 */
S31_CORE_EXPIMP HttpContentType applicationSoapXml(std::string_view action = {});
}  // namespace ContentType
}
