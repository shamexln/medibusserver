#pragma once

#include <S31/Sdc/Private/Common/Http/HttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRegistry.h>

#include <S31/Test/S31Only/Exception.h>

namespace S31::Sdc::Impl::Test
{
class HttpClientRegistryMock : public S31::Sdc::Impl::HttpClientRegistry
{
public:
    explicit HttpClientRegistryMock(std::shared_ptr<HttpClient> injectClient = nullptr)
    : m_injectedClient(std::move(injectClient))
    {
    }

    DFL::NotNull<std::shared_ptr<HttpClient>> sdcNormalPriorityClient() const override
    {
        if (m_injectedClient)
        {
            return DFL::asNotNull(m_injectedClient);
        }
        THROW_EXCEPTION_NOT_IMPLEMENTED();
    }

    DFL::NotNull<std::shared_ptr<HttpClient>> sdcLowPriorityClient() const override
    {
        if (m_injectedClient)
        {
            return DFL::asNotNull(m_injectedClient);
        }
        THROW_EXCEPTION_NOT_IMPLEMENTED();
    }

    DFL::NotNull<std::shared_ptr<HttpClient>> basicClient() const override
    {
        if (m_injectedClient)
        {
            return DFL::asNotNull(m_injectedClient);
        }
        THROW_EXCEPTION_NOT_IMPLEMENTED();
    }

    DFL::NotNull<std::shared_ptr<HttpClient>> discoveryClient() const override
    {
        if (m_injectedClient)
        {
            return DFL::asNotNull(m_injectedClient);
        }
        THROW_EXCEPTION_NOT_IMPLEMENTED();
    }

private:
    std::shared_ptr<HttpClient> m_injectedClient;
};

}
