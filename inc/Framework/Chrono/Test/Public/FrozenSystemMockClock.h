#pragma once

#include <Framework/Chrono/Private/Registry.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemClock.h>

#include <Framework/Utils/Public/StateSaver.h>

namespace DFL
{
namespace Chrono
{
namespace Test
{
/**
 * @brief Mocks SystemClock::now() by returning a frozen SystemClock::TimePoint.
 *
 * By creating an instance of this class, the time point returned by
 * SystemClock::now() will be frozen.
 * The returned time point can be manipulated by the methods setClock and
 * advanceClock.
 * After destructing the instance, SystemClock::now() will work as usual again.
 *
 * @ingroup Chrono
 */
class FrozenSystemMockClock
{
public:
    /**
     * @brief Precision of mocked clock.
     */
    using Duration = Microseconds;
    /**
     * @brief Constructs a FrozenSystemMockClock.
     *
     * The time point returned by SystemClock::now() will be frozen.
     */
    FrozenSystemMockClock();
    /**
     * @brief Sets the time point returned by SystemClock::now() to the given
     * time point.
     * @param tp Time point that will be returned by SystemClock::now()
     */
    void setClock(const SystemClock::TimePoint& tp);
    /**
     * @brief Advances the time point returned by SystemClock::now() by the
     * given duration.
     * @param d Duration used to advance the time point returned by
     * SystemClock::now()
     */
    void advanceClock(const Duration& d);

private:
    Duration m_duration{duration_cast<Duration>(
        Impl::Registry::SystemClock::timeSinceEpoch()())};
    StateSaver<Impl::Registry::SystemClock::TimeSinceEpoch> m_stateSaver{
        Impl::Registry::SystemClock::timeSinceEpoch()};
};

inline FrozenSystemMockClock::FrozenSystemMockClock()
{
    Impl::Registry::SystemClock::timeSinceEpoch() = [&]() {
        return m_duration;
    };
}

inline void FrozenSystemMockClock::setClock(const SystemClock::TimePoint& tp)
{
    m_duration = duration_cast<Duration>(tp.time_since_epoch());
}

inline void FrozenSystemMockClock::advanceClock(const Duration& d)
{
    m_duration += d;
}
}
}
}
