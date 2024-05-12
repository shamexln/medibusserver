#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/LocalTime.h>
#include <Framework/Chrono/Public/MonthDayLast.h>
#include <Framework/Chrono/Public/SystemTime.h>
#include <Framework/Chrono/Public/Year.h>

// technically a forward declaration to these types would be sufficient
// but each client who wants to use this syntax "Year(1966) / mar / last"
// would get a compile error so we include these files here
#include <Framework/Chrono/Public/LastSpec.h>
#include <Framework/Chrono/Public/YearMonth.h>

namespace DFL
{
namespace Chrono
{
class Day;
/**
 * @brief Represents a specific year, month, and the last day of the month.
 *
 * This is a field-based time point with a resolution of days,
 * except that it is restricted to pointing to the last day of a year and month.
 * One can observe each field. The day field is computed on demand.
 * Years and months oriented arithmetic is supported, but not days oriented arithmetic.
 * For the latter, there is a conversion to SystemDays which efficiently supports days oriented arithmetic.
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP YearMonthDayLast
{
public:
    /**
     * @brief Constructs a date pointing to the last day of given year and month.
     *
     * @param y Year.
     * @param mdl Last Day of month.
     */
    YearMonthDayLast(const Year& y, const MonthDayLast& mdl);
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
     * @brief Returns month day last of date.
     *
     * @return MonthDayLast.
     */
    MonthDayLast monthDayLast() const;
    /**
     * @brief Returns day of date.
     *
     * @return Day.
     */
    Chrono::Day day() const;
    /**
     * @brief Plus/Minus-assignment operations.
     *
     * @param d Duration to be added/substraced.
     * @return New last date.
     * @{
     */
    YearMonthDayLast& operator+=(const Months& d);
    YearMonthDayLast& operator-=(const Months& d);
    YearMonthDayLast& operator+=(const Years& d);
    YearMonthDayLast& operator-=(const Years& d);
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
    MonthDayLast m_monthDayLast;
};
/**
 * @brief Relational operators between two dates.
 * @param lhs Date on the left side.
 * @param rhs Date on the right side.
 * @return Result of the comparison.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP bool operator==(const YearMonthDayLast& lhs, const YearMonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator!=(const YearMonthDayLast& lhs, const YearMonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator< (const YearMonthDayLast& lhs, const YearMonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator> (const YearMonthDayLast& lhs, const YearMonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator<=(const YearMonthDayLast& lhs, const YearMonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator>=(const YearMonthDayLast& lhs, const YearMonthDayLast& rhs);
/** @} */
/**
 * @brief Arithmetic operators between date and durations.
 * @param ymdl Date.
 * @param months Duration.
 * @return Result
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP YearMonthDayLast operator+(const YearMonthDayLast& ymdl  , const Months&           months);
DFL_CHRONO_EXPIMP YearMonthDayLast operator+(const Months&           months, const YearMonthDayLast& ymdl   );
DFL_CHRONO_EXPIMP YearMonthDayLast operator-(const YearMonthDayLast& ymdl  , const Months&           months);
/** @} */
/**
 * @brief Arithmetic operators between date and durations.
 * @param ymdl Date.
 * @param years Duration.
 * @return Result
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP YearMonthDayLast operator+(const YearMonthDayLast& ymdl , const Years&            years);
DFL_CHRONO_EXPIMP YearMonthDayLast operator+(const Years&            years, const YearMonthDayLast& ymdl  );
DFL_CHRONO_EXPIMP YearMonthDayLast operator-(const YearMonthDayLast& ymdl , const Years&            years);
/** @} */
/**
 * @brief Allows for short zero overhead construction of dates.
 *
 * @code
 * Year(2015) / aug / last
 * @endcode
 * Instead of:
 * @code
 * YearMonthDayLast(Year(2015), MonthDayLast(aug))
 * @endcode
 *
 * @param ym YearMonth.
 * @return YearMonthDayLast Object.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP YearMonthDayLast operator/(const YearMonth& ym, LastSpec               );
/**
 * @brief Allows for short zero overhead construction of dates.
 *
 * @code
 * Year(2015) / aug / last
 * @endcode
 * Instead of:
 * @code
 * YearMonthDayLast(Year(2015), MonthDayLast(aug))
 * @endcode
 *
 * @param y Year.
 * @param mdl MonthDayLast.
 * @return YearMonthDayLast Object.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP YearMonthDayLast operator/(const Year&       y, const MonthDayLast& mdl);
}
}
