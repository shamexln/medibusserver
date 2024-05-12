#pragma once

#include <S31/Sdc/Private/Common/Http/BasicHttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpResult.h>

#include <Framework/Utils/Public/NotNull.h>

#include <condition_variable>
#include <memory>
#include <mutex>

namespace S31
{
class CoreConfiguration;

namespace AsioDispatch
{
class DefaultAsioDispatcher;
}

namespace Sdc::Impl
{
class SslHandshakeBrokerImpl;
namespace Test
{

class StandaloneHttpClient : public HttpClient
{
public:
    StandaloneHttpClient();

    explicit StandaloneHttpClient(DFL::NotNull<std::shared_ptr<S31::CoreConfiguration>> configuration);

    void sendRequest(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters) override
    {
        m_httpClient.sendRequest(std::move(requestParameters));
    }

    HttpResult sendRequestAndWaitForResponse(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters);

private:
    DFL::NotNull<std::shared_ptr<AsioDispatch::DefaultAsioDispatcher>> m_dispatcher;
    DFL::NotNull<std::shared_ptr<SslHandshakeBrokerImpl>>              m_handshakeBroker;
    BasicHttpClient                                                    m_httpClient;

    std::mutex              m_mutex;
    std::condition_variable m_condVariable;
};

}  // namespace Test
}  // namespace Sdc::Impl
}  // namespace S31