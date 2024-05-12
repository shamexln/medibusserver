#pragma once

#include <Framework/Chrono/Public/SystemClock.h>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief Provide a validity period for creating a certificate.
 *
 * @ingroup Crypto
 */
class ValidityPeriod
{
public:
    /**
     * @brief Set the starting timepoint of the period.
     */
    ValidityPeriod& validFrom(::DFL::Chrono::SystemClock::TimePoint);

    /**
     * @brief Set the lifetime duration of the period.
     */
    ValidityPeriod& validFor(::DFL::Chrono::SystemClock::Duration);

    /**
     * @brief Get the validFrom system timepoint.
     */
    ::DFL::Chrono::SystemClock::TimePoint validFrom() const;

    /**
     * @brief Get the validUntil system timepoint.
     */
    ::DFL::Chrono::SystemClock::TimePoint validUntil() const;

private:
    ::DFL::Chrono::SystemClock::TimePoint m_validFrom{};
    ::DFL::Chrono::SystemClock::Duration m_validFor{};
};

inline ValidityPeriod& ValidityPeriod::validFrom(::DFL::Chrono::SystemClock::TimePoint starttime)
{
    m_validFrom = starttime;
    return *this;
}

inline ValidityPeriod& ValidityPeriod::validFor(::DFL::Chrono::SystemClock::Duration lifetime)
{
    m_validFor = lifetime;
    return *this;
}

inline ::DFL::Chrono::SystemClock::TimePoint ValidityPeriod::validFrom() const
{
    return m_validFrom;
}

inline ::DFL::Chrono::SystemClock::TimePoint ValidityPeriod::validUntil() const
{
    return m_validFrom + m_validFor;
}
}
}
}
