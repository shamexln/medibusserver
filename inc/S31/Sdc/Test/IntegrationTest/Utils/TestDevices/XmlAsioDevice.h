#pragma once
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/Common/HttpTypes.h>

#include <Framework/Utils/Public/Uri.h>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context.hpp>

#include <future>
#include <optional>
#include <memory>
#include <string>
#include <thread>
#include <mutex>

namespace S31::Sdc::Impl::Test
{
class HttpListener;

class XmlAsioDevice
{
    public:
        XmlAsioDevice();
        explicit XmlAsioDevice(std::string_view getMdibResponse);
        ~XmlAsioDevice();

        [[nodiscard]] std::future<void> delayGetMdibResponse();
        void resumeGetMdibResponse();

        [[nodiscard]] DFL::Net::Uri discoveryAddress() const;
        [[nodiscard]] S31::Sdc::EndpointReference epr() const;
        [[nodiscard]] const std::string& clientSubscriptionAddress() const;

    private:
        void saveClientSubscriptionAddress(const std::string& requestBody);
        void waitOptionalGetMdibDelay();
        HttpResponse processRequest(const HttpRequest& request);

        mutable std::mutex m_mutex;
        boost::asio::io_context m_ioCtx;
        boost::asio::ssl::context m_sslCtx;
        std::shared_ptr<S31::Sdc::Impl::Test::HttpListener> m_listener;
        std::string m_getMdibResponse;
        std::string m_ownAddress;
        std::string m_ownEpr;
        std::string m_clientSubscriptionAddress;
        std::thread m_runIo;
        std::optional<std::promise<void>> m_delayGetMdib;
        std::condition_variable m_getMdibResume;
};

}