#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/AsioDispatch/Public/ExecutorProvider.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <memory>

namespace S31::Sdc::Impl
{
class ConnectionPolicy;
class HttpSessionContext;
class HttpServerHandler;
class SslHandshakeBroker;
struct ListeningPortTag {};

/**
 * @brief Strong type for Http server listening port.
 * @ingroup S31SdcCommon
 */
using ListeningPort = DFL::StrongTypedef<std::uint16_t, ListeningPortTag>;

/**
 * @brief Https Server
 * @details This Https server handles keep-alive connections from multiple client endpoints. All the connections share
 * a common connection policy (with e.g. common SSL certificates and certificate verification procedures), and
 * scheduling priority.
 * The server may be configured with a fixed TCP port number to listen on, or allow the operating system to
 * dynamically assign a port.
 * Http requests (i.e. Get, Post) are dispatched to an object implementing the @ref S31::Sdc::Impl::HttpServerHandler
 * interface. This handler is shared with each new connection session to handle requests from the corresponding client.
 * @note Any shared data referenced by the handler must be protected, since it may be called concurrently for different
 * sessions. However, the handler must not block (e.g. to wait for some event) as this will block other (unrelated) work
 * execution.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP HttpServer
{
    DFL_NOT_COPYABLE(HttpServer)

public:
    /**
     * @brief Constructor
     * @param executorProvider Provides access to a prioritized execution context for
     *      all connections handled by this server.
     * @param handshakeBroker Ssl handshakes are delegated to a specialized broker
     *      service which provides e.g. limited concurrent handshakes, and different
     *      thread priority. See @ref S31::Sdc::Impl::SslHandshakeBroker
     * @param connectionPolicy Connection policy provides customization shared by
     *      all the connections managed by this server. For example ssl certificates
     *      are provided. See @ref S31::Sdc::Impl::ConnectionPolicy
     * @param serverHandler Provides application specific handling of incoming Http requests. See
     *      @ref S31::Sdc::Impl::HttpServerHandler
     * @param priority Sets the @ref S31::AsioDispatch::SchedulingPriority used for all accepted connections in this server.
     *      Listening socket scheduling is automatically assigned a lower priority (priority - 1). Note that higher
     *      numeric values indicate higher priority.
     * @param listenPort Sets the TCP port number on which the server will listen for new connections. A value of 0
     *      indicates that the operating system will dynamically assign a port.
     * @throws S31::InternalResourceMissing if the server is unable to open and bind its listening socket.
     */
    HttpServer(
            DFL::NotNull<std::shared_ptr<AsioDispatch::ExecutorProvider>> executorProvider,
            DFL::NotNull<std::shared_ptr<SslHandshakeBroker>>             handshakeBroker,
            DFL::NotNull<std::shared_ptr<const ConnectionPolicy>>         connectionPolicy,
            DFL::NotNull<std::shared_ptr<HttpServerHandler>>              serverHandler,
            AsioDispatch::SchedulingPriority                              priority,
            ListeningPort                                                 listenPort);

    ~HttpServer() noexcept;

    /**
     * @brief Start the server
     * @details Starts listening for new connections
     */
    void start();

    /**
     * @brief Stop the server
     * @details Stops listening for new connections, and immediately closes all existing connections.
     * This method is intended for use at system shutdown time, and will close (unbind) the listening
     * socket. It is not possible to restart the server after stop.
     */
    void stop();

    /**
     * @brief The TCP port the server is listening on for new connections.
     * @details This port may be dynamically assigned by the OS.  If 0 (zero) is returned
     * it indicates that the server has failed to bind or has been stopped (it is not listening
     * for connections).
     */
    std::uint16_t httpIPv4Port() const;

private:
    // Ensure lifetime of executor provider/dispatcher, and provide executors for
    // newly accepted sessions.
    DFL::NotNull<std::shared_ptr<AsioDispatch::ExecutorProvider>> m_executorProvider;

    DFL::NotNull<std::shared_ptr<HttpServerHandler>> m_serverHandler;

    class HttpServerImpl;
    DFL::NotNull<std::shared_ptr<HttpServerImpl>> m_impl;
};

}
