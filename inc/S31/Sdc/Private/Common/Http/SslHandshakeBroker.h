#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/system/error_code.hpp>

#include <functional>
#include <chrono>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface for Ssl handshake broker
 * @details An Ssl handshake broker has responsibility for limiting the amount of concurrent SSL handshakes, and for
 * dispatching handshake operations to an appropriate boost asio executor.
 * @ingroup S31SdcCommon
 */
class SslHandshakeBroker
{
public:
    virtual ~SslHandshakeBroker() = default;

    virtual void
    add(boost::beast::ssl_stream<boost::asio::ip::tcp::socket>& stream,
        boost::asio::ssl::stream_base::handshake_type           type,
        std::chrono::seconds                                    timeout,
        std::function<void(boost::system::error_code)>          completion) = 0;
};

}
