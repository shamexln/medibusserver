#pragma once

#include <Framework/Chrono/Public/SteadyClock.h>

namespace DFL
{
namespace Mdib
{
namespace UnitTest
{

/*!
 * Implements a simple stop watch for timing purpose.
 */
class StopWatch
{
public:
    void start();
    void stop();
    DFL::Chrono::Milliseconds elapsedMilliseconds();

private:
    bool m_started{false};
    DFL::Chrono::SteadyClock::TimePoint m_startTime{};
    DFL::Chrono::SteadyClock::TimePoint m_stopTime{};
};

} /* namespace UnitTest */
} /* namespace Mdib */
} /* namespace DFL */
