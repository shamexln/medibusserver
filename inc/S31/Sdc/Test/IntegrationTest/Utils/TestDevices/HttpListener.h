#pragma once

#include <S31/Sdc/Test/IntegrationTest/Utils/Common/HttpTypes.h>

#include <S31/Sdc/Test/IntegrationTest/Utils/TestDevices/HttpListenerObserver.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/NotNull.h>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/beast/core/error.hpp>

#include <string>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief General response callback function definition for @ref S31::Sdc::Impl::Test::AsyncListener
 */
using RequestHandler = std::function<HttpResponse(const HttpRequest&)>;

/**
 * @brief Asynchronous listener for Http requests.
 * @details Starts an asynchronous session in case of an incoming Http request.
 *          A session keeps itself alive until it either times out or handles the request.
 *          Thus, a session might outlive the listener (and its scope).
 *          The RequestHandler needs to accommodate to this, e.g. making use of weak_ptr.
 */
class HttpListener : public S31::Utils::ObservableSubject<HttpListenerObserver>,
                     public std::enable_shared_from_this<HttpListener>
{
    public:
        /**
         * @brief ctor
         * @param ioc io_context on which the HttpListener operates
         * @param sslContext ssl context used for Tls connections
         * @param endpoint endpoint configuration for the listener
         * @param RequestHandler callback function for incoming requests
         */
        explicit HttpListener(
                boost::asio::io_context& ioc,
                boost::asio::ssl::context& sslContext,
                boost::asio::ip::tcp::endpoint endpoint,
                const RequestHandler& callback);

        /**
         * @brief Start listening.
         */
        void start();

        /**
         * @brief Stop listening.
         */
        void stop();

        /**
         * @brief get address information
         */
        boost::asio::ip::tcp::endpoint endpoint() const;

        /// Register an observer to be notified of listener events
        void registerObserver(const std::weak_ptr<HttpListenerObserver>& observer) override;
        /// Unregister an observer
        void unregisterObserver(const std::weak_ptr<HttpListenerObserver>& observer) override;

    private:
        void doAccept();
        void onAccept(
                boost::beast::error_code ec,
                boost::asio::ip::tcp::socket socket);

        boost::asio::io_context& m_ioContext;
        boost::asio::ssl::context& m_sslContext;
        boost::asio::ip::tcp::acceptor m_acceptor;
        RequestHandler m_callback;

        class HttpListenerObserverDelegate;
        DFL::NotNull<std::shared_ptr<HttpListenerObserverDelegate>> m_observerDelegate;
};


}
