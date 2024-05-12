#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Reperesents a date-month.
 *
 * The range of valid values is from 1 inclusive to 12 inclusive.
 * This class is typesafe wrapper around an integral type.
 * Arithmetic and relational operators are defined to make it behave
 * like an integral type.
 *
 * @see @ref Month::ok()
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP Month
{
public:
    /**
     * @brief Default constructs a month.
     *
     * Same as with int the value held is undefined.
     */
    Month() = default;
    /**
     * @brief Constructs a date month from given value.
     *
     * If the month value was valid or not can be checked with
     * @ref Month::ok() afterwards.
     * @param m Month value.
     * @see @ref Month::ok()
     */
    explicit Month(unsigned m);
    /**
     * @brief pre/post-increment and decrement operations.
     * @{
     */
    Month& operator++();
    Month  operator++(int);
    Month& operator--();
    Month  operator--(int);
    /** @} */
    /**
     * @brief plus/minus-assignemt operations.
     * @{
     */
    Month& operator+=(const Months& m);
    Month& operator-=(const Months& m);
    /** @} */
    /**
     * @brief Returns the native month value.
     * @return Native month value.
     */
    unsigned value() const;
    /**
     * @brief Checks if month-value is valid.
     * @return True if value is from 1 inclusive to 12 inclusive.
     */
    bool ok() const;
private:
    unsigned char m_month{};
};

/**
 * @brief Relational operations.
 * @param lhs
 * @param rhs
 * @return
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP bool operator==(const Month& lhs, const Month& rhs);
DFL_CHRONO_EXPIMP bool operator!=(const Month& lhs, const Month& rhs);
DFL_CHRONO_EXPIMP bool operator< (const Month& lhs, const Month& rhs);
DFL_CHRONO_EXPIMP bool operator> (const Month& lhs, const Month& rhs);
DFL_CHRONO_EXPIMP bool operator<=(const Month& lhs, const Month& rhs);
DFL_CHRONO_EXPIMP bool operator>=(const Month& lhs, const Month& rhs);
/** @} */
/**
 * @brief Arithmetic operations.
 *
 * If the calculated month is valid can be checked with @ref Month::ok().
 * @param lhs
 * @param rhs
 * @return
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP Month  operator+(const Month&  lhs, const Months& rhs);
DFL_CHRONO_EXPIMP Month  operator+(const Months& lhs, const Month&  rhs);
DFL_CHRONO_EXPIMP Month  operator-(const Month&  lhs, const Months& rhs);
DFL_CHRONO_EXPIMP Months operator-(const Month&  lhs, const Month&  rhs);
/** @} */
/**
 * @brief Constants for descriptive usage of month values.
 * @ingroup Chrono
 * @{
 */
const Month jan(1);
const Month feb(2);
const Month mar(3);
const Month apr(4);
const Month may(5);
const Month jun(6);
const Month jul(7);
const Month aug(8);
const Month sep(9);
const Month oct(10);
const Month nov(11);
const Month dec(12);
/** @} */
}
}
