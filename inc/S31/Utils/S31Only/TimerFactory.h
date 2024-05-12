#pragma once

#include <Framework/Utils/Public/NotNull.h>

#include <functional>
#include <memory>

namespace S31::Utils
{
class Timer;

/**
 * @brief Factory interface to create timer instances.
 * @ingroup S31Utils
 */
class TimerFactory
{
public:
    virtual ~TimerFactory() noexcept = default;

    /**
     * @brief Call this function to get a new timer.
     */
    virtual DFL::NotNull<std::unique_ptr<Timer>>
    createTimer(std::function<void()> timeoutFunc) = 0;

};
}  // namespace S31::Utils
