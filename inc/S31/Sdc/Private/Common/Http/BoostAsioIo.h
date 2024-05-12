#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StringViewIo.h>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string_type.hpp>

/**
 * @file
 * @brief Makes boost asio types streamable into @ref DFL::Format::Stream.
 */
namespace boost::asio::ip
{
/**
 * @brief Stream a \c boost::asio::ip::tcp::endpoint to \ref DFL::Format::Stream
 * @details The endpoint is formatted as "address:port"
 */
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const tcp::endpoint& endpoint)
{
    str << endpoint.address().to_string() << ':' << endpoint.port();
    return str;
}
}

namespace boost::system
{
/**
 * @brief Stream a \c boost::system::error_code to \ref DFL::Format::Stream
 * @details The error is formatted as "category:value 'message'"
 * @note This differs from std::ostream output operator which prints only "category:value"
 */
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const error_code& ec)
{
    str << ec.category().name() << ':' << ec.value() << " '" << ec.message() << '\'';
    return str;
}
}

namespace boost
{
/**
 * @brief Stream a \c boost::string_view to \ref DFL::Format::Stream
 * @details Boost beast provides alias \c boost::beast::string_view to \c boost::string_view
 */
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, string_view value)
{
    const std::string_view valueAsStd{value.data(), value.size()};
    str << valueAsStd;
    return str;
}
}
