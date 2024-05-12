#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/StopwatchState.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Chrono/Public/SystemClock.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Tag type for starting a stopwatch on creation.
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP AutoStartType
{
};
/**
 * @brief Stopwatch created with this value will start automatically.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP extern const AutoStartType autoStart;
/**
 * @brief Calculates the elapsed duration between start and stop.
 *
 * This type implements the common behaviour shared between all stopwatch types.
 * It can be customized on a clocktype for specifying the time source.
 * For convenience aliases like @ref DFL::Chrono::Stopwatch are provided.
 *
 * The common behaviour is as follows:
 *
 * To start the stopwatch you can either call @ref start
 * on a default constructed stopwatch ...
 *
 * @snippet Chrono/Test/UnitTest/TestStopwatch.cpp CtorNotRunning
 *
 * ... or use @ref autoStart on construction for starting it immediately.
 *
 * @snippet Chrono/Test/UnitTest/TestStopwatch.cpp CtorRunning
 *
 * Calling @ref elapsed on a running stopwatch returns a snapshot of
 * the elapsed time.
 *
 * @snippet Chrono/Test/UnitTest/TestStopwatch.cpp ElapsedOnRunning
 *
 * After calling @ref stop the elapsed time does not change anymore.
 *
 * @snippet Chrono/Test/UnitTest/TestStopwatch.cpp ElapsedOnNotRunning
 *
 * @ref reset can be used to set the elapsed time to zero.
 *
 * @snippet Chrono/Test/UnitTest/TestStopwatch.cpp ResetOnNotRunning
 *
 * The measurement can be continued by calling @ref start on a stopped
 * stopwatch again.
 *
 * @snippet Chrono/Test/UnitTest/TestStopwatch.cpp ElapsedContinued
 *
 * @ref isRunning can be used to retrieve the current state.
 *
 * Furthermore the following behaviour is implemented:
 * - Calling @ref start on a running stopwatch does nothing.
 * - Calling @ref stop on a stopped stopwatch does nothing.
 * - Calling @ref reset on a running stopwatch is the same as calling:
 *   - @ref stop
 *   - @ref reset
 *   - @ref start
 *
 * @tparam ClockType Specifies the source for measuring how much time elapsed.
 * It has to model the
 * [named requirement Clock](https://en.cppreference.com/w/cpp/named_req/Clock).
 *
 * @tparam DurationType Specifies the precision of this stopwatch and defaults
 * to duration type of given clock.
 *
 * @ingroup Chrono
 */
template <class ClockType, class DurationType = typename ClockType::duration>
class BasicStopwatch : private Impl::StopwatchState
{
public:
    /**
     * @brief Clock used by this stopwatch.
     */
    using clock = ClockType;
    /**
     * @brief Precision of this stopwatch.
     */
    using duration = DurationType;
    /**
     * @brief Stopped stopwatch.
     *
     * @post @ref isRunning returns false.
     */
    BasicStopwatch() = default;
    /**
     * @brief Stopwatch is started immediately.
     *
     * @post @ref isRunning returns true.
     */
    explicit BasicStopwatch(AutoStartType);
    /**
     * @brief Starts the stopwatch and does nothing if it is already running.
     *
     * @post @ref isRunning returns true.
     */
    void start();
    /**
     * @brief Stops the stopwatch and does nothing if it is not running.
     *
     * @post @ref isRunning returns false.
     */
    void stop();
    /**
     * @brief Resets elapsed time to zero regardless of whether or not the
     * stopwatch is running.
     */
    void reset();
    /**
     * @brief Returns the elapsed time.
     *
     * Can be called if stopwatch is running to get a snapshot of the
     * elapsed time.
     */
    duration elapsed() const noexcept;
    /**
     * @brief Returns true if stopwatch is running otherwise false.
     */
    bool isRunning() const noexcept;

private:
    duration durSinceStart() const noexcept;

    using time_point = typename clock::time_point;

    time_point m_start{};
    duration m_elapsed{};
};

template <class ClockType, class DurationType>
inline BasicStopwatch<ClockType, DurationType>::BasicStopwatch(AutoStartType)
{
    start();
}

template <class ClockType, class DurationType>
inline void BasicStopwatch<ClockType, DurationType>::start()
{
    if (running()) return;

    m_start = clock::now();
    onStart();
}

template <class ClockType, class DurationType>
inline void BasicStopwatch<ClockType, DurationType>::stop()
{
    if (!running()) return;

    m_elapsed += durSinceStart();
    onStop();
}

template <class ClockType, class DurationType>
inline void BasicStopwatch<ClockType, DurationType>::reset()
{
    if (running())
    {
        stop();
        start();
    }
    m_elapsed = duration{};
}

template <class ClockType, class DurationType>
inline typename BasicStopwatch<ClockType, DurationType>::duration
BasicStopwatch<ClockType, DurationType>::elapsed() const noexcept
{
    if (running())
    {
        return durSinceStart() + m_elapsed;
    }
    return m_elapsed;
}

template <class ClockType, class DurationType>
inline bool BasicStopwatch<ClockType, DurationType>::isRunning() const noexcept
{
    return running();
}

template <class ClockType, class DurationType>
inline typename BasicStopwatch<ClockType, DurationType>::duration
BasicStopwatch<ClockType, DurationType>::durSinceStart() const noexcept
{
    return duration_cast<duration>(clock::now() - m_start);
}
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using @ref DFL::Chrono::SteadyClock
 * as a source.
 *
 * @ingroup Chrono
 */
template <class Duration>
using StopwatchD = BasicStopwatch<SteadyClock, Duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using @ref DFL::Chrono::SteadyClock
 * as a source.
 *
 * @ingroup Chrono
 */
using Stopwatch = StopwatchD<SteadyClock::duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using @ref DFL::Chrono::SystemClock
 * as a source.
 *
 * @ingroup Chrono
 */
template <class Duration>
using SystemStopwatchD = BasicStopwatch<SystemClock, Duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using @ref DFL::Chrono::SystemClock
 * as a source.
 *
 * @ingroup Chrono
 */
using SystemStopwatch = SystemStopwatchD<SystemClock::duration>;
}
}
