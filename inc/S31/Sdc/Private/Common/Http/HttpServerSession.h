#pragma once

#include <S31/Sdc/Private/Common/Http/HttpServerHandler.h>
#include <S31/Sdc/Private/Common/Http/HttpServerSessionPool.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Chrono/Public/Duration.h>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4702)  // unreachable code
#endif
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <memory>
#include <optional>

namespace S31::Sdc::Impl
{
class SslHandshakeBroker;
class HttpSessionContext;
class ConnectionPolicy;

/**
 * @brief Maintains a keep-alive HTTPS session from a connected client.
 * @details This session monitors its own keep-alive timer, and will initiate a
 * graceful shutdown if the client does not make any requests during the timeout
 * period.
 * @ingroup S31SdcCommon
 */
class HttpServerSession: public std::enable_shared_from_this<HttpServerSession>
{
    public:
        // Expose the State enum for logging purposes
        enum class State
        {
            Initial,       // Initial state after socket accept
            TlsConnect,    // TLS handshake in progress
            FirstRequest,  // Read the first request after connection
            Active,        // Read request or write response in progress
            Idle,          // Waiting up to idle timeout for new request
            Shutdown,      // TLS shutdown in progress
            Failed,        // Connection is closed due to error
            Finished       // Final state
        };

        HttpServerSession(
                boost::asio::ip::tcp::socket&&                        socket,
                std::weak_ptr<SslHandshakeBroker>                     sslHandshakeBroker,
                std::weak_ptr<HttpServerSessionPool>                  serverPool,
                DFL::NotNull<std::shared_ptr<const ConnectionPolicy>> connectionPolicy,
                std::weak_ptr<HttpServerHandler>                      serverHandler,
                boost::asio::ssl::context                             sslContext);

        ~HttpServerSession() noexcept;

        /**
         * @brief Start the session
         * @note It is required to call start to start Tls Handshake
         */
        void start();

        /**
         * @brief Immediately close the connection
         * @note It is not possible to restart the connection after stop.
         */
        void stop();

    private:
        // Schedule next action
        void startHttpRead();
        void startShutdown();

        // Event handlers
        void onStart();
        void onStop();
        void onHandshake(boost::beast::error_code ec);
        void onRead(boost::beast::error_code ec, std::size_t bytesTransferred);
        void onWrite(bool close, boost::beast::error_code ec, std::size_t bytesTransferred);
        void onShutdown(boost::beast::error_code ec);
        void onFail(boost::beast::error_code ec, char const* what);

        bool onSslVerify(bool preverified, boost::asio::ssl::verify_context& ctx);

        void setTimeout(DFL::Chrono::Seconds duration);
        void setTimeout(std::chrono::seconds duration);
        void stopTimeout();
        void onTimeout(const boost::system::error_code& ec);

        void handleReadError(boost::beast::error_code ec);

        void cancelStreamOperationOrFail();
        void logTlsConnectionFailureToSecurityLog(boost::beast::error_code ec);

        std::weak_ptr<SslHandshakeBroker>                     m_sslHandshakeBroker;
        std::weak_ptr<HttpServerSessionPool>                  m_serverPool;
        DFL::NotNull<std::shared_ptr<const ConnectionPolicy>> m_connectionPolicy;
        std::weak_ptr<HttpServerHandler>                      m_serverHandler;
        boost::asio::ssl::context                             m_sslContext;

        DFL::NotNull<std::shared_ptr<const HttpSessionContext>> m_sessionContext;
        std::optional<Utils::Error>                             m_sessionError;

        // Avoid bugs associated with boost::beast::tcp_stream
        // see: https://jira.draeger.com/browse/PCSWORK-6818
        boost::beast::ssl_stream<boost::asio::ip::tcp::socket> m_stream;
        boost::asio::steady_timer                              m_timeout;

        // For logging
        boost::asio::ip::tcp::endpoint m_clientEndpoint;

        State m_state = State::Initial;

        // Buffer must persist while reading a request.
        boost::beast::flat_buffer m_requestBuffer;
        // Construct a fresh parser for each request.
        std::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> m_requestParser;

        boost::beast::http::response<boost::beast::http::string_body> m_response;
};

DFL_ENUM_CLASS_STREAM_OPERATOR(HttpServerSession::State, (Initial)(TlsConnect)(FirstRequest)(Active)(Idle)(Shutdown)(Failed)(Finished))

}
