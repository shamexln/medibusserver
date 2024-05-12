#pragma once

#include <Framework/Log/Private/ExpImp.h>

/**
 * @ingroup Log
 * @{
 */
namespace DFL
{
namespace Log
{

/**
 * @brief Base class for concrete severity type classes.
 *
 * Provides all compare and relational operators to determine the equality and
 * priority of a concrete severity.
 */
class DFL_LOG_EXPIMP Severity
{
public:
    /**
     * @brief Determines whether two severities are equal.
     * @param other Value to be compared with this.
     * @return True if severities are equal otherwise false.
     */
    bool operator==(Severity const& other) const noexcept;

    /**
     * @brief Determines whether two severities are unequal.
     * @param other Value to be compared with this.
     * @return True if severities are unequal otherwise false.
     */
    bool operator!=(Severity const& other) const noexcept;

    /**
     * @brief Determines whether this severity is less than other.
     * @param other Value to be compared with this.
     * @return True if this severity is less than other otherwise false.
     */
    bool operator<(Severity const& other) const noexcept;

    /**
     * @brief Determines whether this severity is greater than other.
     * @param other Value to be compared with this.
     * @return True if this severity is greater than other otherwise false.
     */
    bool operator>(Severity const& other) const noexcept;

    /**
     * @brief Determines whether this severity is less or equal than other.
     * @param other Value to be compared with this.
     * @return True if this severity is less or equal than other otherwise false.
     */
    bool operator<=(Severity const& other) const noexcept;

    /**
     * @brief Determines whether this severity is greater or equal than other.
     * @param other Value to be compared with this.
     * @return True if this severity is greater or equal than other otherwise false.
     */
    bool operator>=(Severity const& other) const noexcept;

    /**
     * @brief Transforms severity value to a string.
     * @return Null terminated string representation of this severity value.
     */
    char const * cStr() const;

protected:
    /**
     * @brief Internal type which represents all severities.
     */
    using Kind = enum
    {
        Trace,
        Success,
        Info,
        Warning,
        Error
    };

    /**
     * @brief Constructs a severity with specified kind.
     * @param k Kindvalue which this severity object shall represent.
     */
    explicit Severity(Kind k);

private:
    Kind m_kind;
};

}
}
/** @} */
