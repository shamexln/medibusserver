#pragma once

#include <Framework/Chrono/Private/Registry.h>
#include <Framework/Chrono/Public/SystemClock.h>

#include <Framework/Utils/Public/StateSaver.h>

namespace DFL
{
namespace Chrono
{
namespace Test
{
/**
 * @brief Mocks SystemClock::now() by returning a manipulated time point.
 *
 * By creating an instance of this class, the time point returned by
 * SystemClock::now() can be manipulated by the method advanceClock.
 * In contrast to FrozenSystemMockClock, the time point returned by
 * SystemClock::now() is not frozen, but keeps increasing. After destructing
 * the instance, SystemClock::now() will work as usual again.
 *
 * @ingroup Chrono
 */
class RunningSystemMockClock
{
public:
    /**
     * @brief Constructs a RunningSystemMockClock.
     *
     * The time point returned by SystemClock::now() can be manipulated by
     * calling advanceClock.
     */
    RunningSystemMockClock();
    /**
     * @brief Advances the time point returned by SystemClock::now() by the
     * given duration.
     * @param ms Duration used to advance the time point returned by
     * SystemClock::now()
     */
    void advanceClock(const Microseconds& ms);

private:
    Microseconds m_offset{0};
    StateSaver<Impl::Registry::SystemClock::TimeSinceEpoch> m_stateSaver{
        Impl::Registry::SystemClock::timeSinceEpoch()};
};

inline RunningSystemMockClock::RunningSystemMockClock()
{
    Impl::Registry::SystemClock::timeSinceEpoch() = [&]() {
        return m_stateSaver.saved()() + m_offset;
    };
}

inline void RunningSystemMockClock::advanceClock(const Microseconds& ms)
{
    m_offset += ms;
}
}
}
}
