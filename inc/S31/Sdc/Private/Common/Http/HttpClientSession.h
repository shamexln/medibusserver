#pragma once

#include <S31/AsioDispatch/Public/Executor.h>
#include <S31/Sdc/Private/Common/Http/HttpResult.h>
#include <S31/Sdc/Private/Common/Http/HttpResultCallback.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>
#include <S31/Sdc/Private/Common/Http/HttpSessionContext.h>
#include <S31/Sdc/Private/Common/Http/ConnectionPolicy.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Uri.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <boost/asio/strand.hpp>
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
#include <string>
#include <string_view>
#include <variant>

namespace S31::Sdc::Impl
{
class HttpClientRequest;
class SslHandshakeBroker;
class HttpClientIdleKeepAlivePool;

/**
 * @brief Establishes a keep-alive HTTPS session to a server.
 * @details In case the requests fails with socket error
 * (timeout for keep-alive) the TCP connection is reestablished.
 * @ingroup S31SdcCommon
 */
class HttpClientSession: public std::enable_shared_from_this<HttpClientSession>
{
    public:
        // Expose the type for unit testing purposes here
        using ResolverType = boost::asio::ip::tcp::resolver;

        // Expose the State enum for logging purposes
        enum class State
        {
            Initial,     // Initial state, socket not yet opened
            Connecting,  // TCP connect and TLS Handshake are in progress
            Connected,   // TLS Handshake successful, waiting for request to run
            Requesting,  // Request in progress (writing request and reading response)
            Shutdown,    // TLS shutdown in progress
            Failed,      // Connection is closed due to error
            Finished     // Final state
        };

        HttpClientSession(
                const AsioDispatch::Executor&                         executor,
                std::weak_ptr<SslHandshakeBroker>                     sslHandshakeBroker,
                std::weak_ptr<HttpClientIdleKeepAlivePool>            idleKeepAlive,
                DFL::NotNull<std::shared_ptr<const ConnectionPolicy>> connectionPolicy,
                boost::asio::ssl::context                             sslContext);

        ~HttpClientSession();

        /**
         * @brief Start an asynchronous client operation
         */
        void start(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters);

        /**
         * @brief Start an asynchronous shutdown of the connection
         */
        void shutdown();

    private:
        void startRequest(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters);
        void startShutdown();

        void connect();
        void initiateHttpRequest();

        template<class Request>
        void writeHttpRequest(const Request& request);

        void onResolve(boost::beast::error_code ec, const boost::asio::ip::tcp::resolver::results_type& results);
        void onConnect(boost::beast::error_code ec);
        void onHandshake(boost::beast::error_code ec);
        void onWrite(boost::beast::error_code ec, std::size_t bytesTransferred);
        void onRead(boost::beast::error_code ec, std::size_t bytesTransferred);
        void onShutdown(boost::beast::error_code ec);
        void onFail(boost::beast::error_code ec, char const* what);
        bool onSslVerify(bool preverified, boost::asio::ssl::verify_context& ctx);

        void setTimeout(std::chrono::seconds duration);
        void stopTimeout();
        void checkTimeout(const boost::system::error_code& ec);

        void logTlsConnectionFailureToSecurityLog(boost::beast::error_code ec);

        struct KeepConnectionAliveTag {};
        using KeepConnectionAlive = DFL::StrongTypedef<bool, KeepConnectionAliveTag>;
        void completeCurrentRequest(HttpResult&& result, KeepConnectionAlive keepAlive);

        boost::asio::strand<boost::asio::executor>              m_strand;
        std::weak_ptr<SslHandshakeBroker>                       m_sslHandshakeBroker;
        std::weak_ptr<HttpClientIdleKeepAlivePool>              m_idleKeepAlivePool;
        DFL::NotNull<std::shared_ptr<const ConnectionPolicy>>   m_connectionPolicy;
        DFL::NotNull<std::shared_ptr<const HttpSessionContext>> m_sessionContext;
        std::optional<Utils::Error>                             m_sessionError;

        boost::asio::ssl::context m_sslContext;
        // Avoid bugs associated with boost::beast::tcp_stream
        // see: https://jira.draeger.com/browse/PCSWORK-6818
        boost::beast::ssl_stream<boost::asio::ip::tcp::socket> m_stream;
        boost::asio::steady_timer                              m_timeout;
        boost::asio::ip::tcp::resolver                         m_resolver;
        QualityOfService                                       m_qualityOfService;

        std::string m_serverAddress;
        State       m_state = State::Initial;

        // Current request is nullable so it can be reset between requests (i.e. when session is idle).
        std::unique_ptr<HttpClientRequest> m_currentRequest;

        // span_body request used to transmit a provided request body without copying.
        // string_body request will be used if the body is dynamically generated.
        using RequestStorage = std::variant<
                boost::beast::http::request<boost::beast::http::span_body<const char>>,
                boost::beast::http::request<boost::beast::http::string_body>>;

        RequestStorage m_request;

        // Buffer must persist while reading a response.
        boost::beast::flat_buffer m_responseBuffer;

        // Construct a fresh parser for each response.
        std::optional<boost::beast::http::response_parser<boost::beast::http::string_body>> m_responseParser;
};

DFL_ENUM_CLASS_STREAM_OPERATOR(HttpClientSession::State, (Initial)(Connecting)(Connected)(Requesting)(Shutdown)(Failed)(Finished))

}
