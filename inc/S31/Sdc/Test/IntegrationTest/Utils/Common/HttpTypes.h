#pragma once

#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

namespace S31::Sdc::Impl::Test
{
/**
 * @brief Alias for standard Http Request Type using Boost Beast
 */
using HttpRequest = boost::beast::http::request<boost::beast::http::string_body>;

/**
 * @brief Alias for standard Http Response Type using Boost Beast
 */
using HttpResponse = boost::beast::http::response<boost::beast::http::string_body>;

}
