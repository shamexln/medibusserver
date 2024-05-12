#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Chrono/Public/Duration.h>

#include <memory>
#include <string>

namespace S31::Sdc
{
class Job;
namespace Impl
{

/**
 * @brief Container for a \ref Job that shall executed later on.
 *
 * @ingroup S31SdcCommonScheduling
 */
class S31_CORE_EXPIMP TimerTask
{
    public:
        TimerTask(std::unique_ptr<Job> task, DFL::Chrono::SteadyClock::TimePoint startTime);
        TimerTask(const TimerTask& rhs) = delete;
        TimerTask(TimerTask&& rhs) noexcept;
        ~TimerTask() = default;

        TimerTask& operator=(const TimerTask& rhs) = delete;
        TimerTask& operator=(TimerTask&& rhs) noexcept;

        bool operator<(const TimerTask& rhs) const;

        [[nodiscard]] DFL::Chrono::Milliseconds getCurrentDelay() const;
        std::unique_ptr<Job> releaseTask() noexcept;

        /// Job's name, for logging and debugging.
        [[nodiscard]] std::string name() const;
    private:
        std::unique_ptr<Job> m_task;
        DFL::Chrono::SteadyClock::TimePoint m_startTime;
};

}
}
