#pragma once

#include <S31/Sdc/Test/IntegrationTest/Utils/Common/HttpTypes.h>

#include <boost/beast/version.hpp>

namespace S31::Sdc::Impl::Test::HttpErrorResponses
{
/**
 * @brief General bad request response.
 * @param reason why the request is bad
 * @param request original request that led to BadRequest response.
 * @return @ref S31::Sdc::Impl::Test::HttpResponse "Http response" with fields set according to bad request.
 */
HttpResponse badRequest(const std::string& reason, const HttpRequest& request);

/**
 * @brief General server error response.
 * @param reason for the internal server error
 * @request original request that led to internal server error
 * @return @ref S31::Sdc::Impl::Test::HttpResponse "Http response" with fields set according to internal server error.
 */
HttpResponse serverError(const std::string& reason, const HttpRequest& request);

/**
 * @brief Status code 422 unprocessable entity error response.
 * @param reason provides details about the error
 * @request original request that led to 422 error
 * @return @ref S31::Sdc::Impl::Test::HttpResponse "Http response" with fields set according to unprocessable entity error.
 */
HttpResponse unprocessableEntity(const std::string& reason, const HttpRequest& request);

}
