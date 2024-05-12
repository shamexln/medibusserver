#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Year.h>
#include <Framework/Chrono/Public/Month.h>
#include <Framework/Chrono/Public/Day.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemTime.h>
#include <Framework/Chrono/Public/LocalTime.h>
#include <Framework/Chrono/Private/LibImpl.h>

// technically a forward declaration to these types would be sufficient
// but each client who wants to use this syntax "Year(1966) / mar / 12"
// would get a compile error so we include these files here
#include <Framework/Chrono/Public/YearMonth.h>
#include <Framework/Chrono/Public/YearMonthDayLast.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief A field based time point with a resolution of one day.
 *
 * This is the same as a system clock time point except that the resolution of this type is days.
 * A date can either be constructed from a year/month/day triple or from a system clock time point.
 * This field based type is implicit convertible to the serial based type @ref SystemDays.
 * Any arbitrary dates can be created even some which do not exist. Use @ref YearMonthDay::ok
 * to check if the date is valid.
 * @snippet Chrono/Test/Unittest/TestYearMonthDay.cpp Construction
 * @snippet Chrono/Test/Unittest/TestYearMonthDay.cpp LastYearMonthDay
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP YearMonthDay
{
public:
    /**
     * @brief Default constructs a year-month-day.
     *
     * The date that such an instance represents is undefined.
     */
    YearMonthDay();
    /**
     * @brief Constructs date from @ref Year, @ref Month and @ref Day.
     *
     * @snippet Chrono/Test/Unittest/TestYearMonthDay.cpp Construction
     *
     * @param y Year
     * @param m Month
     * @param d Day
     */
    YearMonthDay(const Year& y, const Month& m, const Day& d);
    /**
     * @brief Constructs date representing the last day in a year-month combination.
     *
     * @snippet Chrono/Test/Unittest/TestYearMonthDay.cpp LastYearMonthDay
     *
     * @param ymdl Last day of year-month combination.
     */
    YearMonthDay(const YearMonthDayLast& ymdl);
    /**
     * @brief Constructs date from days since epoch.
     *
     * @param days Days since epoch.
     */
    YearMonthDay(const SystemDays& days);
    /**
     * @brief Constructs date from local days.
     *
     * @param days Local days.
     */
    YearMonthDay(const LocalDays& days);
    /**
     * @brief Checks if date is valid or not.
     *
     * @return True if valid otherwise false.
     */
    bool ok() const;
    /**
     * @brief Returns year of date.
     *
     * @return Year.
     */
    Year year() const;
    /**
     * @brief Returns month of date.
     *
     * @return Month.
     */
    Month month() const;
    /**
     * @brief Returns day of date.
     *
     * @return Day.
     */
    Day day() const;
    /**
     * @brief Plus/Minus-assignment operations.
     *
     * @param d Duration to be added/substraced.
     * @return .New date.
     * @{
     */
    YearMonthDay& operator+=(const Months& d);
    YearMonthDay& operator-=(const Months& d);
    YearMonthDay& operator+=(const Years& d);
    YearMonthDay& operator-=(const Years& d);
    /** @} */
    /**
     * @brief Implicitly converts date to days since epoch.
     */
    operator SystemDays() const;
    /**
     * @brief Converts date to days since epoch.
     */
    SystemDays systemDays() const;
    /**
     * @brief Converts date to local days.
     */
    LocalDays localDays() const;
private:
    Year m_year;
    Month m_month;
    Day m_day;
};
/**
 * @brief Relational operators between two dates.
 * @param lhs Date on the left side.
 * @param rhs Date on the right side.
 * @return Result of the comparison.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP bool operator==(const YearMonthDay& lhs, const YearMonthDay& rhs);
DFL_CHRONO_EXPIMP bool operator!=(const YearMonthDay& lhs, const YearMonthDay& rhs);
DFL_CHRONO_EXPIMP bool operator< (const YearMonthDay& lhs, const YearMonthDay& rhs);
DFL_CHRONO_EXPIMP bool operator> (const YearMonthDay& lhs, const YearMonthDay& rhs);
DFL_CHRONO_EXPIMP bool operator<=(const YearMonthDay& lhs, const YearMonthDay& rhs);
DFL_CHRONO_EXPIMP bool operator>=(const YearMonthDay& lhs, const YearMonthDay& rhs);
/** @} */
/**
 * @brief Arithmetic operators between date and durations.
 * @param ymd Date.
 * @param months Duration.
 * @return Result
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP YearMonthDay operator+(const YearMonthDay& ymd, const Months&       months);
DFL_CHRONO_EXPIMP YearMonthDay operator+(const Months& months,    const YearMonthDay& ymd);
DFL_CHRONO_EXPIMP YearMonthDay operator-(const YearMonthDay& ymd, const Months&       months);
/** @} */
/**
 * @brief Arithmetic operators between date and durations.
 * @param ymd Date.
 * @param years Duration.
 * @return Result
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP YearMonthDay operator+(const YearMonthDay& ymd, const Years&        years);
DFL_CHRONO_EXPIMP YearMonthDay operator+(const Years& years,      const YearMonthDay& ymd);
DFL_CHRONO_EXPIMP YearMonthDay operator-(const YearMonthDay& ymd, const Years&        years);
/** @} */
/**
 * @brief Allows for short zero overhead construction of dates.
 *
 * @code
 * Year(2015) / aug / 21
 * @endcode
 * Instead of:
 * @code
 * YearMonthDay(Year(2015), aug, Day(21))
 * @endcode
 * @param ym Year-Month combination.
 * @param d Day of date.
 * @return YearMonthDay Object.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP YearMonthDay operator/(const YearMonth& ym, const Day& d);
DFL_CHRONO_EXPIMP YearMonthDay operator/(const YearMonth& ym, int d);
/** @} */
}
}
