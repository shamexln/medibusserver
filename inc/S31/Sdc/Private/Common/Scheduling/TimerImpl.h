#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <mutex>

namespace S31::Sdc::Impl
{
class IScheduling;

class TimerImpl : public std::enable_shared_from_this<TimerImpl>
{
public:
    TimerImpl(
            std::weak_ptr<IScheduling> scheduling,
            std::function<void()>      timeoutFunc);

    ~TimerImpl() noexcept;
    void start(std::chrono::milliseconds timeout);

    void notifyEvent(std::uint32_t eventId);

private:
    void addNotifyMainLoopTaskNoLock(std::chrono::milliseconds timeout);

    std::weak_ptr<IScheduling> m_scheduling;
    std::function<void()>      m_timeoutFunc;
    std::mutex                 m_mutex;
    std::uint32_t              m_eventId{};
};
}  // namespace S31::Sdc::Impl
