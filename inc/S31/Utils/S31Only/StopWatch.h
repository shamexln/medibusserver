#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Chrono/Public/SteadyClock.h>

#include <chrono>

namespace S31::Utils
{

/**
 * @brief Stop watch to measure time passing by.
 * @ingroup S31Utils
 */
class S31_UTILS_EXPIMP StopWatch
{
    public:
        StopWatch();

        void stop();

        DFL::Chrono::SteadyClock::Duration elapsedTime() const noexcept;
        std::chrono::microseconds elapsedStdTime() const noexcept;

        std::string elapsedTimeString() const;

    private:
        DFL::Chrono::SteadyClock::TimePoint m_startTime;
        DFL::Chrono::SteadyClock::Duration m_elapsedTime;

};

S31_UTILS_EXPIMP bool operator<(const StopWatch& watch, DFL::Chrono::SteadyClock::Duration duration);
S31_UTILS_EXPIMP bool operator<=(const StopWatch& watch, DFL::Chrono::SteadyClock::Duration duration);
S31_UTILS_EXPIMP bool operator>(const StopWatch& watch, DFL::Chrono::SteadyClock::Duration duration);
S31_UTILS_EXPIMP bool operator<(const StopWatch& watch, std::chrono::microseconds duration);
S31_UTILS_EXPIMP bool operator<=(const StopWatch& watch, std::chrono::microseconds duration);
S31_UTILS_EXPIMP bool operator>(const StopWatch& watch, std::chrono::microseconds duration);

}
