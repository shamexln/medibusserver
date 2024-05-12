#pragma once

#include <Framework/Chrono/Private/Registry.h>
#include <Framework/Chrono/Public/Duration.h>

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
 * SteadyClock::now() will be frozen.
 * The returned time point can be manipulated by the methods setClock and
 * advanceClock.
 * After destructing the instance, SteadyClock::now() will work as usual again.
 *
 * @ingroup Chrono
 */
class FrozenSteadyMockClock
{
public:
    /**
     * @brief Precision of mocked clock.
     */
    using Duration = Microseconds;
    /**
     * @brief Constructs a FrozenSteadyMockClock.
     *
     * The time point returned by SteadyClock::now() will be frozen.
     */
    FrozenSteadyMockClock();
    /**
     * @brief Sets the time point returned by SteadyClock::now() to the given
     * duration.
     * @param d Duration that will be returned by SteadyClock::now()
     */
    void setClock(const Duration& d);
    /**
     * @brief Advances the time point returned by SteadyClock::now() by the
     * given duration.
     * @param d Duration used to advance the time point returned by
     * SteadyClock::now()
     */
    void advanceClock(const Duration& d);

private:
    Duration m_duration{duration_cast<Duration>(
        Impl::Registry::SteadyClock::timeSinceEpoch()())};
    StateSaver<Impl::Registry::SteadyClock::TimeSinceEpoch> m_stateSaver{
        Impl::Registry::SteadyClock::timeSinceEpoch()};
};

inline FrozenSteadyMockClock::FrozenSteadyMockClock()
{
    Impl::Registry::SteadyClock::timeSinceEpoch() = [&]() {
        return m_duration;
    };
}

inline void FrozenSteadyMockClock::setClock(const Duration& d)
{
    m_duration = d;
}

inline void FrozenSteadyMockClock::advanceClock(const Duration& d)
{
    m_duration += d;
}
}
}
}
