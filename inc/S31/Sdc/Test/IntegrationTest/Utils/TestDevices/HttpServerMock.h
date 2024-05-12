#pragma once

#include <S31/Sdc/Private/Common/Http/HttpServerResponse.h>
#include <S31/Sdc/Private/Common/Http/HttpServer.h>

#include <chrono>
#include <cstdint>
#include <functional>
#include <string_view>

namespace S31
{
class CoreConfiguration;

namespace AsioDispatch
{
class DefaultAsioDispatcher;
}

namespace Sdc::Impl
{
class SslHandshakeBroker;

namespace Test
{
class MockServerHandler;

/**
 * @brief A https server setup with SDC test certificate to receive messages.
 * @details
 * The default constructed server accepts all messages with HTTP status 202.
 * In case the behaviour shall be overwritten, a custom post handler could be provided in the ctor.
 */
class HttpServerMock
{
public:
    using PostFunction = std::function<HttpServerResponse(std::string_view body)>;

    HttpServerMock();
    explicit HttpServerMock(PostFunction postFunction);

    void start();

    std::uint16_t httpIPv4Port() const;

    int postCallCount() const;

    std::string targetPath(std::size_t index) const;
    std::string body(std::size_t index) const;
    std::string contentEncoding(std::size_t index) const;
    std::string contentType(std::size_t index) const;

    void reset();

    void waitForCalls(int numberOfPostCalls, std::chrono::seconds timeout);

private:
    DFL::NotNull<std::shared_ptr<CoreConfiguration>>                   m_configuration;
    DFL::NotNull<std::shared_ptr<AsioDispatch::DefaultAsioDispatcher>> m_executorProvider;
    DFL::NotNull<std::shared_ptr<SslHandshakeBroker>>                  m_handshakeBroker;
    DFL::NotNull<std::shared_ptr<MockServerHandler>>                   m_serverHandler;
    S31::Sdc::Impl::HttpServer                                         m_httpServer;
};

}  // namespace Test
}  // namespace Sdc::Impl
}  // namespace S31
