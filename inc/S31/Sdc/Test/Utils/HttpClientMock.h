#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/Http/HttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>

#include <mutex>

namespace S31::Sdc::Test
{

class HttpClientMock : public S31::Sdc::Impl::HttpClient
{
public:
    void sendRequest(DFL::NotNull<std::unique_ptr<Impl::HttpClientRequest>> request) override
    {
        const std::lock_guard guard{m_mutex};
        S31_STREAM_INFO_LOGGER(
                "Test", "HttpClient called for ", request->serverAddress(), request->targetPath(), "callback");
        m_requests.push_back(std::move(request));
    }

    void handleFirstRequest(S31::Sdc::Impl::HttpResult httpResult)
    {
        std::unique_lock lock{m_mutex};
        if (m_requests.empty())
        {
            S31_STREAM_ERROR_LOGGER("Test", "There is no request to handle!");
            S31_THROW_EXCEPTION(S31::InternalResourceMissing, "There is no request to handle!");
        }

        auto request = std::move(m_requests[0].get());
        m_requests.erase(m_requests.begin());
        lock.unlock();
        request->notifyCompletion(httpResult);
    }

    [[nodiscard]] bool empty() const
    {
        const std::lock_guard guard{m_mutex};
        return m_requests.empty();
    }

    [[nodiscard]] std::size_t size() const
    {
        const std::lock_guard guard{m_mutex};
        return m_requests.size();
    }

    void clear()
    {
        const std::lock_guard guard{m_mutex};
        m_requests.clear();
    }

    const Impl::HttpClientRequest& firstRequest() const
    {
        const std::lock_guard guard{m_mutex};
        if (m_requests.empty())
        {
            S31_STREAM_ERROR_LOGGER("Test", "There is no request!");
            S31_THROW_EXCEPTION(S31::InternalResourceMissing, "There is no request!");
        }
        return *m_requests[0];
    }

private:
    mutable std::mutex                                                  m_mutex;
    std::vector<DFL::NotNull<std::unique_ptr<Impl::HttpClientRequest>>> m_requests;
};
}  // namespace S31::Sdc::Test
