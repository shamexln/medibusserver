#pragma once

#include <S31/Utils/S31Only/Timer.h>

#include <Framework/Utils/Public/NotNull.h>

#include <functional>
#include <memory>

namespace S31::Sdc::Impl
{
class IScheduling;
class TimerImpl;

/**
 * @brief Timer implementation based on scheduling concept within S31.
 * @details
 * The abstract Timer interface is implemented based on the scheduling concept in S31 to avoid having additional
 * (native) threads for notification.
 */
class Timer : public Utils::Timer
{
public:
    Timer(std::weak_ptr<IScheduling> scheduling, std::function<void()> timeoutFunc);

    void start(std::chrono::milliseconds timeout) override;

private:
    DFL::NotNull<std::shared_ptr<TimerImpl>> m_impl;
};
}  // namespace S31::Sdc::Impl
