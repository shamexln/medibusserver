#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Month.h>

namespace DFL
{
namespace Chrono
{
class LastSpec;
/**
 * @brief This represents the last day of a month.
 *
 * An instance can be constructed from a @ref DFL::Chrono::Month
 * or using the aug/last syntax.
 * @snippet Chrono/Test/Unittest/TestMonthDayLast.cpp Construction
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP MonthDayLast
{
public:
    /**
     * @brief Constructs an instance from given @ref DFL::Chrono::Month.
     *
     * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp Construction
     * @param m @ref DFL::Chrono::Month to represent the last day from.
     */
    explicit MonthDayLast(const Month& m);
    /**
     * @brief Returns @ref DFL::Chrono::Month given to ctor.
     *
     * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp Construction
     * @return @ref DFL::Chrono::Month given to ctor.
     */
    Month month() const;
    /**
     * @brief Is ok if @ref DFL::Chrono::Month is ok.
     *
     * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp Construction
     * @return True if @ref DFL::Chrono::Month is ok otherwise false.
     */
    bool ok() const;
private:
    Month m_month;
};
/**
 * @brief Set of comparison operators.
 *
 * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp EqOperations
 * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp RelationalOperations
 *
 * @param lhs Left value to be compared.
 * @param rhs Right value to be compared.
 * @return True if the according comparison holds otherwise false.
 *
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP bool operator==(const MonthDayLast& lhs, const MonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator!=(const MonthDayLast& lhs, const MonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator< (const MonthDayLast& lhs, const MonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator> (const MonthDayLast& lhs, const MonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator<=(const MonthDayLast& lhs, const MonthDayLast& rhs);
DFL_CHRONO_EXPIMP bool operator>=(const MonthDayLast& lhs, const MonthDayLast& rhs);
/** @} */
/**
 * @brief Constructs an instance of @ref DFL::Chrono::MonthDayLast
 *
 * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp Construction
 *
 * @param m @ref DFL::Chrono::Month to represent the last day from.
 * @return @ref DFL::Chrono::MonthDayLast instance from given month.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP MonthDayLast operator/(const Month& m, LastSpec);
}
}
