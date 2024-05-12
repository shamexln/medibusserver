#pragma once

#include <S31/Sdc/Test/IntegrationTest/Utils/AsioSslConfiguration.h>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <string>
#include <thread>
#include <vector>

namespace S31::Sdc::Impl::Test
{

enum class HttpTestDeviceFunction
{
    Handshake,
    ReadData,
    WriteData // @todo if needed
};

/**
 * @brief Device to listen for TCP connections and perform handshake.
 */
class HttpTestDevice
{
    public:
        enum class SessionResult
        {
            NotRun,
            PassedWithoutError,
            HandshakeError,
            ReadError,
        };

        /**
         * @brief Creates ssl context with the provided certificate name and starts listening for incoming connection request
         *  at the provided address and port.
         */
        HttpTestDevice(const std::string& certCommonName,
                       const std::string& ipAddressStr,
                       S31::Utils::Test::CertHelper::ExtendedKeyUsage supportedRoles = S31::Utils::Test::CertHelper::ExtendedKeyUsage::WithAllRoles,
                       const SupportedSslVersions& sslVersions = {SslVersion::TlsV1_3, SslVersion::TlsV1_2},
                       Expiration expiration = Expiration::Valid,
                       IssuingCertificateAuthority issuer = IssuingCertificateAuthority::DraegerDeviceTestRoot,
                       HttpTestDeviceFunction mode = HttpTestDeviceFunction::Handshake);

        /**
         * @brief Creates ssl context with the provided certificate name, starts listening for incoming connection request
         *  at the provided address and port. Based on the mode, device can either read/write data
         *  Caller needs to set/allocate the buffer
         */
        HttpTestDevice(const std::string& certCommonName,
                       const std::string& ipAddressStr,
                       S31::Utils::Test::CertHelper::ExtendedKeyUsage supportedRoles,
                       const SupportedSslVersions& sslVersions,
                       HttpTestDeviceFunction mode,
                       const std::shared_ptr<std::vector<char>>& dataBuffer);

        /**
         * @brief Run the io_context object's event processing loop on its own thread.
         */
        std::thread runOnThread();

        /**
         * @brief Stops accepting new connections to allow a graceful shutdown to capture handshake errors
         */
        void stopAccepting();

        /**
         * @brief Stops the io_context object's event processing loop
         */
        void stop();

        /**
         * @brief Returns the assigned port
         */
        unsigned short assignedPort() const;

        /**
         * @brief Returns the assigned address
         */
        std::string assignedAddress() const;

        /**
         * @brief Returns an https Url with assigned address and port
         */
        std::string url() const;

        /**
         * @brief Returns result of the last session.
         * @details Empty if the last session Success
         */
        SessionResult lastSessionResult() const;

        /**
         * @brief Returns text of the last exception observed
         * @details Empty if the last session Success
         */
        const std::string& lastSessionErrorMessage() const;

        /**
         * @brief Stops the io_context object's event processing loop and destroys all the pointers.
         */
        ~HttpTestDevice();

        /**
         * @brief Set the result from the last session.
         * @details For internal use
         */
        void sessionCompleted(SessionResult result, const std::string& message);

        /**
         * @brief Configure the device to drop some number of handshakes
         * @details Supports testing of connection retry logic
         * @note Should be called to configure before running the device on its own thread.
         */
        void dropNextHandshakes(int handshakesToDrop);

    private:
        void accept();

        boost::asio::io_context m_ioc;
        boost::asio::ssl::context m_ctx;
        boost::asio::ip::tcp::acceptor m_acceptor;
        HttpTestDeviceFunction m_role;
        std::shared_ptr<std::vector<char>> m_buffer;
        SessionResult m_lastSessionResult{SessionResult::NotRun};
        std::string m_lastSessionErrorMessage;
        int m_dropHandshakes{0};
        bool m_stopAccepting{false};

};

}
