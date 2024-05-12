#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemTime.h>

#include <string>

namespace DFL
{
namespace Chrono
{
/**
 * @brief This structure contains data typically used internally for
 * conversions from system time to local time.
 *
 * @ingroup Chrono
 */
struct DFL_CHRONO_EXPIMP SystemInfo
{
    /**
     * @brief The value of each member is valid but unspecified.
     */
    SystemInfo() = default;
    /**
     * @brief Sets the member to the given values.
     */
    SystemInfo(const SystemSeconds& begin_,
               const SystemSeconds& end_,
               const Seconds& offset_,
               const Minutes& save_,
               std::string abbrev_);
    /**
     * @brief The begin and end fields indicate that for the associated time
     * zone and time point, the offset and abbrev are in effect in the range
     * [begin, end).
     *
     * @note
     * In case of a timezone without dst-rule begin and end are set to
     * @c SystemSeconds::min()/max(). If an assignment to a @ref
     * DFL::Chrono::SystemClock::TimePoint is done an overflow will occur e.g.
     * @code
     * ZonedTime zt(SystemSeconds::max());
     * assert(zt.systemTime() != SystemSeconds::max());
     * @endcode
     * @{
     */
    SystemSeconds begin{Seconds{0}};
    SystemSeconds end{Seconds{0}};
    /** @} */
    /**
     * @brief The offset field indicates the UTC offset in effect for the
     * associated time zone and time point.
     *
     * The relationship between local time and sys time is: offset = localTime -
     * systemTime
     */
    Seconds offset{0};
    /**
     * @brief The save field is "extra" information not normally needed
     * for conversion between local_time and sys_time. If save != 0min,
     * this sys_info is said to be on "daylight saving" time, and offset - save
     * suggests what this time_zone might use if it were off daylight saving.
     * However this information should not be taken as authoritative.
     * The only sure way to get such information is to query the time zone
     * with a time point that returns an system info where save == 0min.
     * There is no guarantee what time point might return such an system info
     * except that it is guaranteed not to be in the range [begin, end)
     * (if save != 0min for this system info).
     */
    Minutes save{0};
    /**
     * @brief Short name of the time zone currently in effect o [begin, end).
     */
    std::string abbrev{};
};
/**
 * @brief Two system infos are equal if they hold the same data.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP bool operator==(const SystemInfo& lhs, const SystemInfo& rhs);
/**
 * @brief Two system infos are not equal if they do not hold the same data.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP bool operator!=(const SystemInfo& lhs, const SystemInfo& rhs);
}
}
