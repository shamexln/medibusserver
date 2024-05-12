#pragma once

#include <S31/Sdc/Private/Common/Http/HttpResult.h>

#include <optional>
#include <mutex>
#include <condition_variable>

namespace S31::Sdc::Impl
{
/**
 * A tool to synchronously wait for an HttpResult. Intended for temporary
 * use until Blocking jobs are converted to asynchronous.
 */
class HttpResultWaiter
{
public:
    void setResult(HttpResult result)
    {
        {
            std::lock_guard const lock(m_mutex);
            m_result = std::move(result);
        }
        m_condition.notify_all();
    }

    std::optional<HttpResult> waitForResult(std::chrono::seconds timeout)
    {
        std::unique_lock lock(m_mutex);
        m_condition.wait_for(lock, timeout, [this] { return m_result.has_value(); });

        auto result = std::move(m_result);
        m_result.reset();
        return result;
    }

private:
    std::optional<HttpResult> m_result;
    std::condition_variable m_condition;
    std::mutex m_mutex;
};

}  // namespace S31::Sdc::Impl
