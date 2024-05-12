#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/SteadyClock.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Creates statically monotonic increasing timepoints.
 *
 * The epoch of this clock is the time passed since boot.
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP SteadyClock
{
public:
    /**
     * @brief Period of this clock.
     */
    using Duration = Impl::SteadyClock::Duration;
    /**
     * @brief Period of this clock. Lower case because
     * boost::asio::basic_waitable_timer needs this type.
     */
    using duration = Duration;
    /**
     * @brief Type which holds the duration since the epoch of this clock.
     *
     * This unambigously defines a type which only works with this clock.
     * Thus interfaces can precisely specify from which clock
     * a timepoint shall be provided.
     * @warning A client should not construct a timepoint directly.
     * To create a correct timepoint for a clock the clocks epoch has to
     * be known and the according arithmetic calculations have to be done
     * by hand. Creation of timepoints are either done by clocks or
     * by conversion-function which can be found in
     * @ref Framework/Chrono/Public/Convert.h
     */
    using TimePoint = Impl::SteadyClock::TimePoint;
    /**
     * @brief Type time_point is defined because
     * boost::asio::basic_waitable_timer needs this type.
     */
    using time_point = TimePoint;
    /**
     * @brief Creates static monotonic increasing timepoints.
     *
     * This time point does @e not relate to the local or UTC time.
     *
     * @return Timepoint which represents the time since epoch.
     */
    static TimePoint now();
};
}
}
