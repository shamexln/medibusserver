#pragma once

#include <Framework/Chrono/Private/LibImpl.h>

/**
 * @file
 * @brief Contains rounding function for durations and time points.
 *
 * Each of the rounding functions have a specific behaviour. If
 * in doubt use @ref DFL::Chrono::floor for time points
 * and @c duration_cast for durations.
 *
 * @dot
 * digraph A
 * {
 *     graph [rankdir=LR]
 *     node [shape=plaintext]
 *     node [fontname="courier bold"]
 *     edge [fontname="courier bold"]
 *     edge [penwidth=2.0]
 *     edge [color="blueviolet"]
 *     edge [label="ceil"]
 *     -2 -> -1 -> 0 -> 1 -> 2
 *     edge [color="blue"]
 *     edge [label="duration_cast"]
 *     -2 -> -1 -> 0
 *     2 -> 1 -> 0
 *     edge [color="black"]
 *     edge [label="floor"]
 *     2 -> 1 -> 0 -> -1 -> -2
 * }
 * @enddot
 *
 * - @ref DFL::Chrono::floor always rounds durations in the direction of lower values.
 *   Meaning 0.25 becomes 0 and -0.25 becomes -1.
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp FloorDurations
 *   The same happens for time points. But with time points positive and negative
 *   have another semantic as with durations. A positive time point denotes a
 *   point in time which is after the clock's epoch and a negative one points
 *   to a point in time which is before the clock's epoch. Hence 9 hours after
 *   the system clock's epoch returns 1970/jan/1 and 9 hours before the epoch
 *   returns 1969/dec/31.
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp FloorTimePoints
 *
 * - @ref DFL::Chrono::ceil always rounds durations in the direction of higher values.
 *   Meaning 0.25 becomes 1 and -0.25 becomes 0.
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp CeilDurations
 *   The same happens for time points. Hence 9 hours after
 *   the system clock's epoch returns 1970/jan/2 and 9 hours before the epoch
 *   returns 1970/jan/1.
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp CeilTimePoints
 *
 * - @c duration_cast behaves the same way as @ref DFL::Chrono::floor
 *   for positive durations. For negative durations @c duration_cast
 *   returns the same result as @ref DFL::Chrono::ceil.
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp duration_cast
 *
 * - @ref DFL::Chrono::round always rounds durations in the direction of nearest value.
 *   Meaning 0.25 becomes 0 and 0.75 becomes 1.
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp RoundDurations
 *   The same happens for time points. Hence 9 hours after
 *   the system clock's epoch returns 1970/jan/1 and 15 hours after the epoch
 *   returns 1970/jan/2.
 *   @snippet Chrono/Test/UnitTest/TestRound.cpp RoundTimePoints
 *
 * @ingroup Chrono
 */
namespace DFL
{
namespace Chrono
{
using Impl::ceil;
using Impl::floor;
using Impl::round;
/**
 * @brief Coverts time point from a higher period to a lower one.
 *
 * This conversion always cuts off information. The different round
 * function allow to specify how the resulting time point shall be rounded.
 *
 * @tparam TimePointType Type of time point which shall be converted.
 * @tparam To Duration to which time point shall be converted.
 * @param tp Time point to be converted.
 * @return Converted time point.
 * @ingroup Chrono
 * @{
 */
template<class To, class TimePointType>
Impl::time_point<typename TimePointType::clock, To> floor(
    const TimePointType& tp);

template<class To, class TimePointType>
Impl::time_point<typename TimePointType::clock, To> round(
    const TimePointType& tp);

template<class To, class TimePointType>
Impl::time_point<typename TimePointType::clock, To> ceil(
    const TimePointType& tp);
/** @} */

template<class To, class TimePointType>
inline Impl::time_point<typename TimePointType::clock, To> floor(
    const TimePointType& tp)
{
    return Impl::time_point<typename TimePointType::clock, To>(floor<To>(tp.time_since_epoch()));
}

template<class To, class TimePointType>
inline Impl::time_point<typename TimePointType::clock, To> round(
    const TimePointType& tp)
{
    return Impl::time_point<typename TimePointType::clock, To>(round<To>(tp.time_since_epoch()));
}

template<class To, class TimePointType>
inline Impl::time_point<typename TimePointType::clock, To> ceil(
    const TimePointType& tp)
{
    return Impl::time_point<typename TimePointType::clock, To>(ceil<To>(tp.time_since_epoch()));
}
}
}
