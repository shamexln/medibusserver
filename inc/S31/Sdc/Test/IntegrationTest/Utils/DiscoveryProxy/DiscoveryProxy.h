#pragma once

#include <S31/Sdc/Test/IntegrationTest/Utils/TestDevices/HttpListener.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/DiscoveryProxy/DeviceInformation.h>

namespace S31::Sdc::Impl::Test
{
class DiscoveryBroker;

/**
 * @brief This class implements a Discovery Proxy for a Ws-Discovery managed mode.
 * @details It listens for Ws-Discovery Hello, Bye, Probe and Resolve messages sent over Https
 *          and reacts accordingly, internally maintaining a list of devices discovered in this manner.
 *          Refer to <a href="http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html">WS-Discovery specification</a>
 *          for more information.
 */
class DiscoveryProxy
{
    public:
        /**
         * @brief ctor.
         * @param io_ctx io context for the Http listener.
         * @param ssl_ctx ssl context used for Tls connections.
         * @param endpoint used by the discovery proxy.
         * @details The io context is not run by the proxy itself. It has
         *          to be triggered externally by calling it's
         *          \ref boost::asio::io_context::run "run" method.
         */
        explicit DiscoveryProxy(boost::asio::io_context& io_ctx,
                                boost::asio::ssl::context& ssl_ctx,
                                boost::asio::ip::tcp::endpoint endpoint);

        /**
         * @brief ctor with initial devices list.
         * @param io_ctx io context for the http listener.
         * @param ssl_ctx ssl context used for tls connections.
         * @param endpoint used by the discovery proxy.
         * @param devices the proxy shall initially hold.
         */
        explicit DiscoveryProxy(boost::asio::io_context& io_ctx,
                                boost::asio::ssl::context& ssl_ctx,
                                boost::asio::ip::tcp::endpoint endpoint,
                                DiscoveryInformationMap devices);


        /**
          * @brief Start accepting incoming connections.
          */
        void start();

        /**
         * @brief Stop listening.
         */
        void stop();

        /**
         * @brief Access internal device list.
         * @details Note that when the proxy goes out of scope, this reference will start dangling.
         */
         const DiscoveryInformationMap& devices() const;

         /**
          * @brief address information of discovery proxy
          */
         boost::asio::ip::tcp::endpoint endpoint() const;

        /**
         * @copydoc S31::Sdc::Impl::Test::DiscoveryBroker::waitForDeviceListUpdate
         */
        bool waitForDeviceListUpdate(const std::chrono::milliseconds& maxWaitTime);

        /**
        * @copydoc S31::Sdc::Impl::Test::DiscoveryBroker::startWaitingForUpdates
        */
        void startWaitingForUpdates();

    private:
        std::shared_ptr<DiscoveryBroker> m_discoveryBroker;
        std::shared_ptr<HttpListener> m_server;
};

}
