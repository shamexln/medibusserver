#pragma once

#include <S31/Sdc/Private/Common/Http/HttpServerResponse.h>

namespace S31::Sdc::Impl
{

/**
 * @brief 404 - Not Found client error.
 */
inline HttpServerResponse status404_NotFound()
{
    return HttpServerResponse{HttpStatusCode{404}, ConnectionPersistence::Close};
}

/**
 * @brief 414 - URI Too Long client error.
 */
inline HttpServerResponse status414_UriTooLong()
{
    return HttpServerResponse{HttpStatusCode{414}, ConnectionPersistence::Close};
}

/**
 * @brief 500 - Internal Error on server side.
 */
inline HttpServerResponse status500_InternalError()
{
    return HttpServerResponse{HttpStatusCode{500}, ConnectionPersistence::Close};
}

/**
 * @brief Extract supported response encoding (compression) from request.
 */
std::string_view responseEncoding(HttpAcceptEncodingView acceptedEncoding);

/**
 * @brief Compresses non empty body in case the encoding is gzip.
 */
std::string optionallyCompressedResponse(std::string&& responseBody, std::string_view encoding);


}
