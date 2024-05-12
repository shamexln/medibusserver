#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/AsioSslConfiguration.h>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/http.hpp>

#include <memory>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief Client to perform custom HTTP Requests.
 */
class HttpTestClient
{
    public:

        /**
         * @brief Creates a Http Client.
         * @details Uses \ref DFL::Crypto::Test::createTestrootCaSignedLeafCertificate() to create a certificate chain
         * and loads the certificate, private key and root CAs into the ssl context.
         *
         * @param certCommonName is the name set in the generated certificate.
         * @param supportedRoles type of the roles to be included in the certificate.
         * @param sslVersions list of supported ssl/tls Versions
         * @param expiration certificate validity (expiration)
         * @param issuer issuing authority
         */
        explicit HttpTestClient(const std::string& certCommonName = "ITHttpTestClient",
                                S31::Utils::Test::CertHelper::ExtendedKeyUsage supportedRoles = S31::Utils::Test::CertHelper::ExtendedKeyUsage::WithAllRoles,
                                const SupportedSslVersions& sslVersion = {SslVersion::TlsV1_3, SslVersion::TlsV1_2},
                                Expiration expiration = Expiration::Valid,
                                IssuingCertificateAuthority issuer = IssuingCertificateAuthority::DraegerDeviceTestRoot);

        /**
         * @brief Make a Http Request.
         * @param url Absolute URL to send the request to
         * @param method defines which request method to use. Defaults to a HTTP GET Request.
         * @param body Body of the request. Defaults to an empty string.
         * @return The body of the response.
         * @throws \ref std::runtime_error
         */
        std::string httpSuccessfulRequest(const std::string& url,
                                          boost::beast::http::verb method = boost::beast::http::verb::get,
                                          const std::string& body = "");

        /**
         * @brief Sends Http Request with the given request body returns the response read.
         * @param url URL to send the request to
         * @param method Http request method, defaults to 'get'.
         * @param body Body of the request. Defaults to an empty string.
         * @return The body of the response.
         * @throws \ref std::runtime_error
         */
        boost::beast::http::response<boost::beast::http::string_body> httpRequest(
                const std::string& url,
                boost::beast::http::verb method = boost::beast::http::verb::get,
                const std::string& body = "");

        /**
         * @brief Sends given Http Request and returns the response read.
         * @param url URL to send the request to
         * @param method Http request method.
         * @param req Http request.
         * @return The body of the response.
         * @throws \ref std::runtime_error
         */
        boost::beast::http::response<boost::beast::http::string_body> httpRequest(
                const std::string& url,
                boost::beast::http::verb method,
                const boost::beast::http::request<boost::beast::http::string_body>& req);

        /**
         * @brief Try a handshake
         * @details This can be used when merely the handshaking procedure shall be tested.
         * @throws @ref std::runtime_error in case the handshake fails.
         */
        void tryHandshake(const std::string& url);

        /**
         * @brief Set an SslVerify function
         * @details This can be used to inject some behavior during a handshake
         */
        template<class Func>
        void sslVerifyFunction(Func&& fn);

        /**
         * @brief Make request object.
         *
         * @return boost::beast::http::request<boost::beast::http::string_body>
         */
        boost::beast::http::request<boost::beast::http::string_body>
        prepareRequest(const std::string& url, boost::beast::http::verb method, std::string body);

    private:
        std::string m_host;
        std::string m_port;

        boost::asio::ssl::context m_sslContext;

        boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> resolveHost(boost::asio::io_context& ioc);

        void setConnectionTarget(const std::string& url);

        void connect(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& stream,
                     const boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>& results);

        boost::beast::http::response<boost::beast::http::string_body> makeRequest(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& stream,
                                                                                  const boost::beast::http::request<boost::beast::http::string_body>& request,
                                                                                  boost::beast::http::verb method);

        static void disconnect(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& stream);
};

template<class Func>
inline void HttpTestClient::sslVerifyFunction(Func&& fn)
{
    m_sslContext.set_verify_callback(std::forward<Func>(fn));
}
}
