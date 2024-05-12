#pragma once

#include <S31/AsioDispatch/Public/ExecutorProvider.h>
#include <S31/Sdc/Private/Common/Http/ConnectionPolicy.h>
#include <S31/Sdc/Private/Common/Http/HttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
class SslHandshakeBroker;

/**
 * @brief Https Client
 * @details This Https client handles keep-alive connections to multiple different http endpoints.
 * All the connections share a common connection policy (with e.g. common SSL certificates and certificate
 * verification procedures), and scheduling priority.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP BasicHttpClient : public HttpClient
{
    DFL_NOT_COPYABLE(BasicHttpClient)

public:
    /**
     * @brief Constructor
     * @param executorProvider Provides access to a prioritized execution context for
     *      all connections handled by this client.
     * @param handshakeBroker Ssl handshakes are delegated to a specialized broker
     *      service which may provide e.g. limited concurrent handshakes, and different
     *      thread priority. See @ref S31::Sdc::Impl::SslHandshakeBroker
     * @param connectionPolicy Connection policy provides customization shared by
     *      all the connections managed by this client.  For example ssl certificates
     *      are provided. See @ref S31::Sdc::Impl::ConnectionPolicy
     * @param priority Sets the @ref AsioDispatch::SchedulingPriority used for all connections
     *      from this client. Note that higher numeric values indicate higher priority.
     */
    BasicHttpClient(
            DFL::NotNull<std::shared_ptr<AsioDispatch::ExecutorProvider>> executorProvider,
            DFL::NotNull<std::shared_ptr<SslHandshakeBroker>>             handshakeBroker,
            DFL::NotNull<std::shared_ptr<const ConnectionPolicy>>         connectionPolicy,
            AsioDispatch::SchedulingPriority                              priority);

    /**
     * @brief Initiate a new request with @ref HttpClientRequest parameters.
     */
    void sendRequest(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters) override;

private:
    // Ensure lifetime of executor provider/dispatcher, and provide executors for
    // new sessions.
    DFL::NotNull<std::shared_ptr<AsioDispatch::ExecutorProvider>> m_executorProvider;

    class BasicHttpClientImpl;
    DFL::NotNull<std::shared_ptr<BasicHttpClientImpl>> m_impl;
};

}
