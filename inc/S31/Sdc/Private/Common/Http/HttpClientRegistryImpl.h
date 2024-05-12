#pragma once

#include <S31/Sdc/Private/Common/Http/HttpClientRegistry.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31
{
namespace AsioDispatch
{
class ExecutorProvider;
}

class CoreConfiguration;

namespace Sdc::Impl
{
class HttpClient;
class SslHandshakeBroker;

class S31_CORE_EXPIMP HttpClientRegistryImpl : public HttpClientRegistry
{
    public:
        HttpClientRegistryImpl(
                DFL::NotNull<std::shared_ptr<AsioDispatch::ExecutorProvider>> executorProvider,
                DFL::NotNull<std::shared_ptr<SslHandshakeBroker>>             handshakeBroker,
                DFL::NotNull<std::shared_ptr<const CoreConfiguration>>        coreConfiguration);

        /// Implementation of @ref HttpClientRegistry interface
        /// @{
        DFL::NotNull<std::shared_ptr<HttpClient>> sdcNormalPriorityClient() const override;
        DFL::NotNull<std::shared_ptr<HttpClient>> sdcLowPriorityClient() const override;
        DFL::NotNull<std::shared_ptr<HttpClient>> basicClient() const override;
        DFL::NotNull<std::shared_ptr<HttpClient>> discoveryClient() const override;
        /// @}

    private:
        DFL::NotNull<std::shared_ptr<HttpClient>> m_sdcPriorityClient;
        DFL::NotNull<std::shared_ptr<HttpClient>> m_basicClient;
        DFL::NotNull<std::shared_ptr<HttpClient>> m_discoveryClient;
};

}
}