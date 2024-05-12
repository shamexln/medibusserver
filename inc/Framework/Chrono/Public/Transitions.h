#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemTime.h>

#include <Framework/Utils/Public/ConstContainer.h>

#include <string>
#include <vector>

namespace DFL
{
namespace Chrono
{
struct SystemInfo;
/**
 * @brief Represent a transition either from std- to dst-time or vice versa.
 *
 * The held utc offset, dst-flag and the abbreviated name are in effect for time
 * points greater or equal to the held time point. But the transition itself
 * does not know when the next transition starts. If you want to know all
 * transitions according to a given time zone then checkout @ref
 * DFL::Chrono::Transitions.
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP Transition
{
public:
    /**
     * @brief Transition without offset, name or dst.
     *
     * @snippet Chrono/Test/UnitTest/TestTransitions.cpp DefCtor
     */
    Transition() = default;
    /**
     * @brief Transition configured with given parameters.
     *
     * @snippet Chrono/Test/UnitTest/TestTransitions.cpp ParamCtor
     */
    Transition(SystemSeconds tp,
               Seconds effectiveOffset,
               std::string abbreviation,
               bool isDaylightSaving);
    /**
     * @brief Only needed internally for creating transitions from time zone.
     */
    explicit Transition(const SystemInfo& info);
    /**
     * @brief Returns start of transition (inclusive).
     */
    SystemSeconds timePoint() const;
    /**
     * @brief Returns UTC offset + going eastwards - going westwards.
     */
    Seconds offset() const;
    /**
     * @brief Returns abbreviated name e.g. "CEST"
     */
    std::string abbrev() const;
    /**
     * @brief True if dst is in effect otherwise false.
     */
    bool isDst() const;
    /**
     * @brief True if all members are equal otherwise false.
     */
    bool equals(const Transition& other) const noexcept;

private:
    SystemSeconds m_tp{Seconds{0}};
    Seconds m_offset{0};
    std::string m_abbrev{};
    bool m_isDst{false};
};
/**
 * @brief True if transitions are identical otherwise false.
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp CopyAndEqOps
 *
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP bool operator==(const Transition& lhs, const Transition& rhs);
DFL_CHRONO_EXPIMP bool operator!=(const Transition& lhs, const Transition& rhs);
/** @} */
}
}
namespace DFL
{
namespace Chrono
{
class TimeZone;
class Year;
/**
 * @brief Models a container holding transitions from std to dst
 * and vice versa for a specific time zone in a specific year-range.
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp TestData
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp TransWithDst
 *
 * Instances of this class are typically constructed by a factory function
 * e.g. @ref DFL::Chrono::calcTransitions.
 *
 * Access to elements of this container are gained via an iterator interface.
 * Thus making even complex tasks like getting a string representation
 * of all transitions in a specific year in local time trivial:
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp IterInterface
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP Transitions
    : public Utils::ConstContainer<std::vector<Transition>>
{
public:
    using Utils::ConstContainer<std::vector<Transition>>::ConstContainer;
};
/**
 * @brief Same as calling calcTransitions(tz, start, Years(0)).
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp TransWithDstForOneYear
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Transitions calcTransitions(const TimeZone& tz, Year start);
/**
 * @brief Contains all std/dst and dst/std transitions starting at given year
 * for the next n given years.
 *
 * Constructing from a time zone without dst rule leads to the following
 * configuration:
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp TransWithoutDst
 * If given time zone has a dst rule then the calculated transitions
 * are accessible via an iterator interface.
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp TransWithDst
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Transitions calcTransitions(const TimeZone& tz,
                                              Year start,
                                              Years nextNYears);
}
}
