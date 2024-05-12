#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/Month.h>
#include <Framework/Chrono/Public/Year.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief A field based time point with a resolution of one month.
 *
 * This type combines year and month value of a date.
 * Especially the arithmetic operators take care of any year overflow if it occurs.
 * @snippet Chrono/Test/Unittest/TestYearMonth.cpp ArithmeticOperators
 * Any arbitrary year-month-dates can be created even some which do not exist.
 * Use YearMonth::ok() to check if the date is valid.
 * @snippet Chrono/Test/Unittest/TestYearMonth.cpp Construction
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP YearMonth
{
public:
    /**
     * @brief Constructs date from @ref Year, and @ref Month.
     *
     * @param year Year
     * @param month Month
     */
    YearMonth(const Year& year, const Month& month);
    /**
     * @brief Returns year of date.
     *
     * @return Year.
     */
    Year year()  const;
    /**
     * @brief Returns month of date.
     *
     * @return Month.
     */
    Month month() const;
    /**
     * @brief Checks if date is valid or not.
     *
     * @return True if valid otherwise false.
     */
    bool ok() const;
    /**
     * @brief plus/minus-assignemt operations.
     * @{
     */
    YearMonth& operator+=(const Months& months);
    YearMonth& operator-=(const Months& months);
    YearMonth& operator+=(const Years& years);
    YearMonth& operator-=(const Years& years);
    /** @} */
private:
    Year m_year;
    Month m_month;
};
/**
 * @brief Relational operators between two dates.
 * @param lhs Date on the left side.
 * @param rhs Date on the right side.
 * @return Result of the comparison.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP bool operator==(const YearMonth& lhs, const YearMonth& rhs);
DFL_CHRONO_EXPIMP bool operator!=(const YearMonth& lhs, const YearMonth& rhs);
DFL_CHRONO_EXPIMP bool operator< (const YearMonth& lhs, const YearMonth& rhs);
DFL_CHRONO_EXPIMP bool operator> (const YearMonth& lhs, const YearMonth& rhs);
DFL_CHRONO_EXPIMP bool operator<=(const YearMonth& lhs, const YearMonth& rhs);
DFL_CHRONO_EXPIMP bool operator>=(const YearMonth& lhs, const YearMonth& rhs);
/** @} */
/**
 * @brief Arithmetic operators between date and durations.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP YearMonth operator+(const YearMonth& ym,     const Months&    months);
DFL_CHRONO_EXPIMP YearMonth operator+(const Months&    months, const YearMonth& ym);
DFL_CHRONO_EXPIMP YearMonth operator-(const YearMonth& ym,     const Months&    months);
DFL_CHRONO_EXPIMP YearMonth operator+(const YearMonth& ym,    const Years&     years);
DFL_CHRONO_EXPIMP YearMonth operator+(const Years&     years, const YearMonth& ym);
DFL_CHRONO_EXPIMP YearMonth operator-(const YearMonth& ym,    const Years&     years);
DFL_CHRONO_EXPIMP Months    operator-(const YearMonth& lhs, const YearMonth& rhs);
/** @} */
/**
 * @brief Allows for short zero overhead construction of dates.
 *
 * @code
 * Year(2015) / aug
 * @endcode
 * Instead of:
 * @code
 * YearMonth(Year(2015), aug)
 * @endcode
 * @param y Year.
 * @param m Month.
 * @return Year-Month date.
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP YearMonth operator/(const Year& y, const Month& m);
}
}
