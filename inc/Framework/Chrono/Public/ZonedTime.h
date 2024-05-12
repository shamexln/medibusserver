#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/LocalTime.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/SystemInfo.h>
#include <Framework/Chrono/Public/TimeZone.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief ZonedTime represents a logical paring of a time zone and a system clock time point.
 *
 * The local time is obtained by applying the according time zone offset to the system clock time point.
 * @snippet Chrono/Sample/Sample.cpp LocalTime
 * If only a system clock time point is given the time zone equals UTC.
 *
 * These definitions are used for the code snippets to document further features of this class.
 * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp TestData
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP ZonedTime
{
public:
    /**
     * @brief Takes a system clock time point and thus holds a utc zoned time.
     *
     * Thus no offset to the system time is applied when a local time is calculated.
     *
     * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp UtcCtor
     */
    explicit ZonedTime(const SystemClock::TimePoint& sysTime);
    /**
     * @brief Takes a system clock time point and a time zone.
     *
     * The given time zone is used for converting system time into local time.
     *
     * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp TzCtor
     */
    ZonedTime(
        const SystemClock::TimePoint& sysTime,
        TimeZone tz);
    /**
     * @brief Returns the given/created time zone from constructor.
     *
     * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp TimeZone
     */
    const TimeZone& timeZone() const;
    /**
     * @brief Returns whatever @ref DFL::Chrono::TimeZone::systemInfo with held time point returns.
     *
     * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp SystemInfo
     */
    SystemInfo systemInfo() const;
    /**
     * @brief Returns the held system clock time point.
     *
     * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp TzCtor
     */
    SystemClock::TimePoint systemTime() const;
    /**
     * @brief Calculates the local time from the contained system info and system clock time point.
     *
     * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp TzCtor
     */
    LocalTime localTime() const;
private:
    SystemClock::TimePoint m_systemTime;
    TimeZone m_tz;
};

/**
 * @brief Two zoned times are equal if they represent the same time point in the same time zone.
 */
DFL_CHRONO_EXPIMP bool operator==(const ZonedTime& lhs, const ZonedTime& rhs);
/**
 * @brief Two zoned times are not equal if they do not represent the same time point or are not in the same time zone.
 */
DFL_CHRONO_EXPIMP bool operator!=(const ZonedTime& lhs, const ZonedTime& rhs);

}
}
