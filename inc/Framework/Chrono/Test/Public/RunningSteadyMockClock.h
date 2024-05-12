#pragma once

#include <Framework/Chrono/Private/Registry.h>
#include <Framework/Chrono/Public/SteadyClock.h>

#include <Framework/Utils/Public/StateSaver.h>

namespace DFL
{
namespace Chrono
{
namespace Test
{
/**
 * @brief Mocks SteadyClock::now() by returning a manipulated time point.
 *
 * By creating an instance of this class, the time point returned by
 * SteadyClock::now() can be manipulated by the method advanceClock.
 * In contrast to FrozenSteadyMockClock, the time point returned by
 * SteadyClock::now() is not frozen, but keeps increasing. After destructing
 * the instance, SteadyClock::now() will work as usual again.
 *
 * @ingroup Chrono
 */
class RunningSteadyMockClock
{
public:
    /**
     * @brief Constructs a RunningSteadyMockClock.
     *
     * The time point returned by SteadyClock::now() can be manipulated by
     * calling advanceClock.
     */
    RunningSteadyMockClock();
    /**
     * @brief Advances the time point returned by SteadyClock::now() by the
     * given duration.
     * @param ms Duration used to advance the time point returned by
     * SteadyClock::now()
     */
    void advanceClock(const Microseconds& ms);

private:
    Microseconds m_offset{0};
    StateSaver<Impl::Registry::SteadyClock::TimeSinceEpoch> m_stateSaver{
        Impl::Registry::SteadyClock::timeSinceEpoch()};
};

inline RunningSteadyMockClock::RunningSteadyMockClock()
{
    Impl::Registry::SteadyClock::timeSinceEpoch() = [&]() {
        return m_stateSaver.saved()() + m_offset;
    };
}

inline void RunningSteadyMockClock::advanceClock(const Microseconds& ms)
{
    m_offset += ms;
}
}
}
}
