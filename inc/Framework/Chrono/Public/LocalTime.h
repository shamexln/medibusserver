#pragma once

#include <Framework/Chrono/Private/LibImpl.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/TimePoint.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Tag type for representing an non-clock.
 */
struct LocalType
{};
/**
 * @brief LocalTime contains aliases for creating a TimePoint of arbitrary precision which is not based on any clock at all.
 *
 * This family of types represents a time not associated with any time zone.
 * It is handy in disambiguating calendar timestamps referring to an unspecified timezone, and those referring to UTC.
 * For example, we can say that the upcoming 2017 New Years will be commonly celebrated at LocalDays(Year(2017)/jan/1) + Seconds(0).
 * For those in a time zone with a zero offset from UTC, it will be celebrated at the concrete time of SystemDays(Year(2017/jan/1) + 0s.
 * These two timestamps have different types, though both have the exact same representation (a count of seconds),
 * because they mean two subtly different things, and are both quite useful.
 *
 * @ingroup Chrono
 * @{
 */
using LocalDays = DFL::Chrono::time_point<LocalType, Days>;
using LocalHours = DFL::Chrono::time_point<LocalType, Hours>;
using LocalMinutes = DFL::Chrono::time_point<LocalType, Minutes>;
using LocalSeconds = DFL::Chrono::time_point<LocalType, Seconds>;
using LocalMilliseconds = DFL::Chrono::time_point<LocalType, Milliseconds>;
using LocalMicroseconds = DFL::Chrono::time_point<LocalType, Microseconds>;
using LocalTime = DFL::Chrono::time_point<LocalType, SystemClock::Duration>;
/** @} */
}
}
