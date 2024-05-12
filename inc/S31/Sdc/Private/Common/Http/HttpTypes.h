#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/EnumClass.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{
struct HttpStatusCodeTag {};
struct HttpPathTag {};
struct HttpPathViewTag {};
struct HttpAcceptEncodingTag {};
struct HttpAcceptEncodingViewTag {};
struct HttpContentTypeTag {};
struct HttpContentEncodingTag {};
struct HttpContentTypeViewTag {};
struct HttpContentEncodingViewTag {};

/**
 * @brief Enumerate options for an Http request method
 * @ingroup S31SdcCommon
 */
enum class HttpMethod
{
    Get,
    Post
};
DFL_ENUM_CLASS_STREAM_OPERATOR(HttpMethod, (Get)(Post))

/**
 * @brief Enumerate options for Http connection persistence
 * @ingroup S31SdcCommon
 */
enum class ConnectionPersistence
{
    Close, ///! Close a connection following completion of a request.
    KeepAlive, ///! Keep idle connection alive for reuse.
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ConnectionPersistence, (Close)(KeepAlive))

/**
 * @brief Status code element of an Http response.
 * @ingroup S31SdcCommon
 */
using HttpStatusCode = DFL::StrongTypedef<unsigned int, HttpStatusCodeTag, DFL::Skill::Streamable>;

/**
 * @brief Wrapper for Http request target path.
 * @details Absolute path component of the request-target from an Http request.
 * @ingroup S31SdcCommon
 */
using HttpPath = DFL::StrongTypedef<std::string, HttpPathTag, DFL::Skill::Streamable>;

/**
 * @brief View of @ref HttpPath
 * @ingroup S31SdcCommon
 */
using HttpPathView = DFL::StrongTypedef<std::string_view, HttpPathViewTag, DFL::Skill::Streamable>;

/**
 * @brief Wrapper for Http Accept-Encoding header in an Http request.
 * @details The Accept-Encoding request-header field restricts the content-codings that are acceptable in the response.
 * @ingroup S31SdcCommon
 */
using HttpAcceptEncoding = DFL::StrongTypedef<std::string, HttpAcceptEncodingTag>;

/**
 * @brief View of @ref HttpAcceptEncoding
 * @ingroup S31SdcCommon
 */
using HttpAcceptEncodingView = DFL::StrongTypedef<std::string_view, HttpAcceptEncodingViewTag>;

/**
 * @brief Wrapper for Http Content-Type header.
 * @details The Content-Type header field indicates the media type of the message body sent to the recipient.
 * @ingroup S31SdcCommon
 */
using HttpContentType = DFL::StrongTypedef<std::string, HttpContentTypeTag>;

/**
 * @brief Wrapper for Http Content-Encoding header.
 * @details The Content-Encoding header field is used as a modifier to the media-type. When present, its value indicates
 * what additional content codings have been applied to the message body, and thus what decoding mechanisms must be
 * applied in order to obtain the media-type referenced by the Content-Type header field.
 * @ingroup S31SdcCommon
 */
using HttpContentEncoding = DFL::StrongTypedef<std::string, HttpContentEncodingTag>;

/**
 * @brief View of @ref HttpContentType
 * @ingroup S31SdcCommon
 */
using HttpContentTypeView = DFL::StrongTypedef<std::string_view, HttpContentTypeViewTag>;

/**
 * @brief View of @ref HttpContentEncoding
 * @ingroup S31SdcCommon
 */
using HttpContentEncodingView = DFL::StrongTypedef<std::string_view, HttpContentEncodingViewTag>;
}
