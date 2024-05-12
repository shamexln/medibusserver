#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/LibImpl.h>

/**
 * @ingroup Chrono
 * @{
 *
 * @file Chrono/Public/Duration.h
 * @brief Defines different duration types with different periods and
 * cast function (duration_cast) to convert a duration with a higher resolution
 * to one with a lower resolution.
 *
 * Durations represent a timespan like 2 hours or 12 seconds and 100 milliseconds.
 * All durations are arithmetic types which behave much like an int.
 * @snippet Chrono/Sample/Sample.cpp Duration::ArithmeticOperations
 * Durations can only be implicit converted from lower period to higher periods.
 * Otherwise information would be lost. If this is acceptable a duration_cast
 * or one of the round functions from @ref Chrono/Public/Round.h must be used:
 * - @ref DFL::Chrono::floor
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp FloorDurations
 * - @ref DFL::Chrono::ceil
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp CeilDurations
 * - @c duration_cast
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp duration_cast
 * - @ref DFL::Chrono::round
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp RoundDurations
 *
 * Defining duration with custom periods is simple too.
 * A duration with a ratio of <1, 1> corresponds to seconds.
 * Thus if an application is called periodically every 250 ms.
 * Then one can simple define a tick duration,
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp TickDuration
 * thus making it unecessary to compute a tick counter from a given duration.
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp ComputeCount
 */
namespace DFL
{
namespace Chrono
{

using Impl::ratio;
using Impl::duration;

/** @brief Duration representing a resolution of nanoseconds. */
using Nanoseconds = Impl::Nanoseconds;

/** @brief Duration representing a resolution of microseconds. */
using Microseconds = Impl::Microseconds;

/** @brief Duration representing a resolution of milliseconds. */
using Milliseconds = Impl::Milliseconds;

/** @brief Duration representing a resolution of seconds. */
using Seconds = Impl::Seconds;

/** @brief Duration representing a resolution of minutes. */
using Minutes = Impl::Minutes;

/** @brief Duration representing a resolution of hours. */
using Hours = Impl::Hours;

using Impl::duration_cast;

/** @brief Duration representing a resolution of days. */
using Days = Impl::Days;

/** @brief Duration representing a resolution of weeks. */
using Weeks = Impl::Weeks;

/** @brief Duration representing a resolution of months. */
using Months = Impl::Months;

/** @brief Duration representing a resolution of years. */
using Years = Impl::Years;
}
}
/** @} */

namespace DFL
{
namespace Chrono
{
namespace Literals
{
/**
 * @brief Literal operator for creating hours.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Hours operator"" _h(unsigned long long count);

/**
 * @brief Literal operator for creating minutes.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Minutes operator"" _min(unsigned long long count);

/**
 * @brief Literal operator for creating seconds.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Seconds operator"" _s(unsigned long long count);

/**
 * @brief Literal operator for creating milliseconds.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Milliseconds operator"" _ms(unsigned long long count);

/**
 * @brief Literal operator for creating microseconds.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Microseconds operator"" _us(unsigned long long count);

/**
 * @brief Literal operator for creating nanoseconds.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Nanoseconds operator"" _ns(unsigned long long count);
}
}
}
