#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Reperesents a date-year.
 *
 * This class is typesafe wrapper around an integral type.
 * The range of valid values is equal to the range of the wrapped integral type.
 * Arithmetic and relational operators are defined to make it behave
 * like an integral type.
 *
 * @see @ref ok()
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP Year
{
public:
    /**
     * @brief Default constructs a year.
     *
     * Same as with int the value held is undefined.
     */
    Year() = default;
    /**
     * @brief Constructs a date year from given value.
     *
     * If the given value exceeds the range of the integral type
     * the value is truncated.
     * @param y Year value.
     */
    explicit Year(int y);
    /**
     * @brief pre/post-increment and decrement operations.
     * @{
     */
    Year& operator++();
    Year  operator++(int);
    Year& operator--();
    Year  operator--(int);
    /** @} */
    /**
     * @brief plus/minus-assignemt operations.
     * @{
     */
    Year& operator+=(const Years& rhs);
    Year& operator-=(const Years& rhs);
    /** @} */
    /**
     * @brief Returns if the year is a leap year or not.
     * @return True on leap year otherwise false.
     */
    bool isLeap() const;
    /**
     * @brief Returns the native year value.
     * @return Native year value.
     */
    int value() const;
    /**
     * @brief Checks if year-value is valid.
     * @return Always true. If a given value does not fit into the integral type
     * it is truncated.
     */
    bool ok() const;
private:
    short m_year{};
};
/**
 * @brief Arithmetic and relational operations.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP  bool operator==(const Year& lhs, const Year& rhs);
DFL_CHRONO_EXPIMP  bool operator!=(const Year& lhs, const Year& rhs);
DFL_CHRONO_EXPIMP  bool operator< (const Year& lhs, const Year& rhs);
DFL_CHRONO_EXPIMP  bool operator> (const Year& lhs, const Year& rhs);
DFL_CHRONO_EXPIMP  bool operator<=(const Year& lhs, const Year& rhs);
DFL_CHRONO_EXPIMP  bool operator>=(const Year& lhs, const Year& rhs);

DFL_CHRONO_EXPIMP  Year  operator+(const Year&  lhs, const Years& rhs);
DFL_CHRONO_EXPIMP  Year  operator+(const Years& lhs, const Year&  rhs);
DFL_CHRONO_EXPIMP  Year  operator-(const Year&  lhs, const Years& rhs);
DFL_CHRONO_EXPIMP  Years operator-(const Year&  lhs, const Year&  rhs);
/** @} */
}
}

namespace DFL
{
namespace Chrono
{
namespace Literals
{
/**
 * @brief Literal operator for creating year.
 *
 * @snippet Chrono/Test/UnitTest/TestYearMonthDay.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Year operator"" _y(unsigned long long count);
}
}
}
