#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/SystemClock.h>
#include <Framework/Chrono/Public/SystemTime.h>

namespace DFL
{
namespace Chrono
{

/**
 * @brief Creates timepoints which represent the time of the current system.
 *
 * The epoch of this clock is the Unix epoch (1970-01-01T00:00:00Z).
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP SystemClock
{
public:
    /**
     * @brief Represents period of this clock.
     */
    using Duration = Impl::SystemClock::Duration;
    /**
     * @brief Represents period of this clock.
     */
    using duration = Duration;
    /**
     * @brief Type which holds the duration since the epoch of this clock.
     *
     * This unambiguously defines a type which only works with this clock.
     * Thus interfaces can precisely specify from which clock
     * a timepoint shall be provided.
     * @warning A client should not construct a timepoint directly.
     * To create a correct timepoint for a clock the clocks epoch has to
     * be known and the according arithmetic calculations have to be done
     * by hand. Creation of timepoints are either done by clocks or
     * by conversion-function which can be found in
     * @ref Framework/Chrono/Public/Convert.h
     */
    using TimePoint = Impl::SystemClock::TimePoint;
    /**
     * @brief Type which holds the duration since the epoch of this clock.
     *
     * This unambiguously defines a type which only works with this clock.
     * Thus interfaces can precisely specify from which clock
     * a timepoint shall be provided.
     * @warning A client should not construct a timepoint directly.
     * To create a correct timepoint for a clock the clocks epoch has to
     * be known and the according arithmetic calculations have to be done
     * by hand. Creation of timepoints are either done by clocks or
     * by conversion-function which can be found in
     * @ref Framework/Chrono/Public/Convert.h
     */
    using time_point = TimePoint;
    /**
     * @brief Creates a timepoint which represents the time of the current
     * system.
     *
     * This returns an UTC timepoint.
     * @return Timepoint which represents the time since epoch.
     */
    static TimePoint now();
};
}
}
