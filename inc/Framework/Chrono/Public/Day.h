#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Reperesents a date-day.
 *
 * The range of valid values is from 1 inclusive to 31 inclusive.
 * But it can hold invalid values which are outside of this range.
 * This class is typesafe wrapper around an integral type.
 * Arithmetic and relational operators are defined to make it behave
 * like an integral type.
 *
 * @see @ref Day::ok()
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP Day
{
public:
    /**
     * @brief Defaultconstructs a date.
     *
     * Like with int the held value is unspecified.
     */
    Day() = default;
    /**
     * @brief Constructs a date day from given value.
     *
     * If the day value was valid or not can be checked with
     * @ref Day::ok() afterwards.
     * @param d Day value.
     * @see @ref Day::ok()
     */
    explicit constexpr Day(unsigned d) noexcept;
    /**
     * @brief pre/post-increment and decrement operations.
     * @{
     */
    Day& operator++() noexcept;
    Day operator++(int) noexcept;
    Day& operator--() noexcept;
    Day operator--(int) noexcept;
    /** @} */
    /**
     * @brief plus/minus-assignemt operations.
     * @{
     */
    Day& operator+=(const Days& d) noexcept;
    Day& operator-=(const Days& d) noexcept;
    /** @} */
    /**
     * @brief Returns the native day value.
     */
    constexpr explicit operator unsigned() const noexcept;
    /**
     * @brief Returns the native day value.
     */
    constexpr unsigned value() const noexcept;
    /**
     * @brief Checks if day-value is valid.
     * @return True if value is from 1 inclusive to 31 inclusive.
     */
    constexpr bool ok() const noexcept;

private:
    unsigned char m_day;
};
/**
 * @brief Relational operations.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP constexpr bool operator==(const Day& lhs,
                                            const Day& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr bool operator!=(const Day& lhs,
                                            const Day& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr bool operator<(const Day& lhs,
                                           const Day& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr bool operator>(const Day& lhs,
                                           const Day& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr bool operator<=(const Day& lhs,
                                            const Day& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr bool operator>=(const Day& lhs,
                                            const Day& rhs) noexcept;
/** @} */
/**
 * @brief Arithmetic operations.
 *
 * If the calculated day is valid can be checked with @ref Day::ok().
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP constexpr Day operator+(const Day& lhs,
                                          const Days& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr Day operator+(const Days& lhs,
                                          const Day& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr Day operator-(const Day& lhs,
                                          const Days& rhs) noexcept;
DFL_CHRONO_EXPIMP constexpr Days operator-(const Day& lhs,
                                           const Day& rhs) noexcept;
/** @} */

constexpr inline Day::Day(unsigned d) noexcept
    : m_day(static_cast<unsigned char>(d))
{
}

constexpr inline Day::operator unsigned() const noexcept
{
    return m_day;
}

constexpr inline unsigned Day::value() const noexcept
{
    return m_day;
}

constexpr inline bool Day::ok() const noexcept
{
    return 1 <= m_day && m_day <= 31;
}

constexpr inline bool operator==(const Day& lhs, const Day& rhs) noexcept
{
    return lhs.value() == rhs.value();
}

constexpr inline bool operator!=(const Day& lhs, const Day& rhs) noexcept
{
    return !(lhs == rhs);
}

constexpr inline bool operator<(const Day& lhs, const Day& rhs) noexcept
{
    return lhs.value() < rhs.value();
}

constexpr inline bool operator>(const Day& lhs, const Day& rhs) noexcept
{
    return rhs < lhs;
}

constexpr inline bool operator<=(const Day& lhs, const Day& rhs) noexcept
{
    return !(rhs < lhs);
}

constexpr inline bool operator>=(const Day& lhs, const Day& rhs) noexcept
{
    return !(lhs < rhs);
}

constexpr inline Days operator-(const Day& lhs, const Day& rhs) noexcept
{
    return Days(static_cast<Days::rep>(lhs.value() - rhs.value()));
}

constexpr inline Day operator+(const Day& lhs, const Days& rhs) noexcept
{
    return Day(lhs.value() + static_cast<unsigned>(rhs.count()));
}

constexpr inline Day operator+(const Days& lhs, const Day& rhs) noexcept
{
    return rhs + lhs;
}

constexpr inline Day operator-(const Day& lhs, const Days& rhs) noexcept
{
    return lhs + -rhs;
}

namespace Literals
{
/**
 * @brief Literal operator for creating day.
 *
 * @snippet Chrono/Test/UnitTest/TestYearMonthDay.cpp Literals
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Day operator"" _d(unsigned long long count);
}
}
}
