#pragma once

#include <chrono>

namespace S31::Utils
{
class Timer
{
public:
    virtual ~Timer() noexcept = default;

    /**
     * @brief (Re-)start the timer.
     */
    virtual void start(std::chrono::milliseconds timeout) = 0;
};
}  // namespace S31::Utils
