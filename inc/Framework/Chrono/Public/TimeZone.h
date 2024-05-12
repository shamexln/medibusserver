#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/TimeZone.h>
#include <Framework/Chrono/Private/TzStringParser.h>
#include <Framework/Chrono/Public/LocalTime.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/SystemTime.h>

#include <Framework/Utils/Public/EnumClass.h>

#include <string>
#include <utility>

namespace DFL
{
namespace Chrono
{
struct SystemInfo;
/**
 * @brief Holds constants which decide if in case of an
 * ambiguous/nonexistent conversion from local to system time
 * either the earliest or latest system time shall be chosen.
 *
 * @see @ref DFL::Chrono::TimeZone::toSystem
 *
 * @ingroup Chrono
 */
enum class Choose
{
    /// Choose earliest system time.
    Earliest,
    /// Choose latest system time.
    Latest
};
/**
 * @brief Tag type for holding a iana-format-tz-string.
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP IanaFormat
{
public:
    /**
     * @brief Ctor defaults to UTC timezone
     */
    IanaFormat();
    /**
     * @brief Ctor.
     */
    explicit IanaFormat(std::string ianaFmt);
    /**
     * @brief Returns tz-string from ctor.
     */
    std::string str() const;
private:
    std::string m_fmt;
};
/**
 * @brief Returns true if the held strings are identical otherwise false.
 * @warning No analysis is done if the time zones constructed from these
 * tz-strings are identical or not.
 * @ingroup Chrono
 * @{
 */
bool operator==(const IanaFormat& lhs, const IanaFormat& rhs);
bool operator!=(const IanaFormat& lhs, const IanaFormat& rhs);
/** @} */
inline IanaFormat::IanaFormat()
    : m_fmt("UTC0")
{
}
inline IanaFormat::IanaFormat(std::string ianaFmt)
    : m_fmt(std::move(ianaFmt))
{
}
inline std::string IanaFormat::str() const
{
    return m_fmt;
}
inline bool operator==(const IanaFormat& lhs, const IanaFormat& rhs)
{
    return lhs.str() == rhs.str();
}
inline bool operator!=(const IanaFormat& lhs, const IanaFormat& rhs)
{
    return !(lhs == rhs);
}
/**
 * @brief Tag type for holding a posix-format-tz-string.
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP PosixFormat
{
public:
    /**
     * @brief Ctor defaults to UTC timezone
     */
    PosixFormat();
    /**
     * @brief Ctor.
     */
    explicit PosixFormat(std::string posixFmt);
    /**
     * @brief Returns tz-string from ctor.
     */
    std::string str() const;
private:
    std::string m_fmt;
};
/**
 * @brief Returns true if the held strings are identical otherwise false.
 * @warning No analysis is done if the time zones constructed from these
 * tz-strings are identical or not.
 * @ingroup Chrono
 * @{
 */
bool operator==(const PosixFormat& lhs, const PosixFormat& rhs);
bool operator!=(const PosixFormat& lhs, const PosixFormat& rhs);
/** @} */

inline PosixFormat::PosixFormat()
    : m_fmt("UTC0")
{
}
inline PosixFormat::PosixFormat(std::string posixFmt)
    : m_fmt(std::move(posixFmt))
{
}
inline std::string PosixFormat::str() const
{
    return m_fmt;
}
inline bool operator==(const PosixFormat& lhs, const PosixFormat& rhs)
{
    return lhs.str() == rhs.str();
}
inline bool operator!=(const PosixFormat& lhs, const PosixFormat& rhs)
{
    return !(lhs == rhs);
}
/**
 * @brief A time zone represents all the utc offset transitions for a specific geographic area.
 *
 * Construction is done by providing a time-zone-string which either has the iana or the posix
 * format (http://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html). The only difference
 * between these two formats is that the sign of the utc offsets is inverted. Thus it is impossible
 * to detect the right format by inspecting the given string. The constructor from time zone has
 * has been overloaded and the client has to explicitly specify the format of the tz-string.
 * These two tz-strings construct identical time zones:
 * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp SameTimeZone
 *
 * In case of an invalid string an exception is thrown. If this is not desired take a look at
 * @ref DFL::Chrono::Convert::toTimeZone which returns none in case of an invalid string.
 *
 * The tz-string can include the extension to POSIX.1, where the range of the hour fields in the DST rules
 * are extended from 0..23 to -167..167, e.g. used in Israel since at least 2016.
 *
 * The format supported in this parser has the following deviations from the reference format:
 *  - Strings starting with ':', where a file is referenced, are not supported.
 *  - The time zone names can have 3..10 characters (standard gives no upper limit).
 *  - The special case of a string "WART-4WARST,J1/0,J365/25", which switches between standard time
 *    and summer at the same date and time (e.g. Western Argentina Summer Time in prior years),
 *    should be interpreted as summer time / day light saving is effective the whole year.
 *    This is not supported, instead use a simpler string "WARST-3" which has the same effect.
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP TimeZone
{
    friend SystemInfo Impl::calcSystemInfo(SystemSeconds tp, const TimeZone& zone);
public:
    /**
     * @brief Constructs a default time zone representing UTC time
     */
    TimeZone();
    /**
     * @brief Constructs time zone from given iana-format-tz-string.
     *
     * @throws std::runtime_error if tz-string is not valid.
     * @see @ref DFL::Chrono::Convert::toTimeZone for a non-throwing version.
     */
    explicit TimeZone(const IanaFormat& tzStr);
    /**
     * @brief Constructs time zone from given posix-format-tz-string.
     *
     * @throws std::runtime_error if tz-string is not valid.
     * @see @ref DFL::Chrono::Convert::toTimeZone for a non-throwing version.
     */
    explicit TimeZone(const PosixFormat& tzStr);
    /**
     * @brief True if time zone has dst rules, otherwise false.
     *
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp HasDstRule
     */
    bool hasDstRule() const;
    /**
     * @brief Returns a @ref DFL::Chrono::SystemInfo @c s for which @c tp is in the range [s.begin, s.end).
     *
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp SystemInfo
     */
    SystemInfo systemInfo(SystemClock::TimePoint tp) const;
    /**
     * @brief Returns the local time associated with given time point in this time zone.
     *
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp SystemTimeToLocalTime
     */
    LocalTime toLocal(SystemClock::TimePoint tp) const;
    /**
     * @brief Returns the system time associated with given local time point in this time zone.
     *
     * The problem with this conversion is, that it is not always unique.
     * Depending on the zone and its std/dst-rules it is possible to give this function
     * a local time which either never existed or is ambiguous because it existed twice.
     * For this reason the caller has to specify how this function shall handle these cases.
     * For example this time zone:
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp LocalTimeTimeZone
     * Here you can see that there is a gap of one hour between the end of std-time
     * and the beginning of dst-time. The following behaviour is implemented
     * if a conversion of a local time during that hour is requested:
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp LocalTimeNonexistent
     * On the other hand there is an overlap of one hour between end of dst-time
     * and the beginning of std-time. The following behaviour is implemented
     * if a conversion of a local time during that hour is requested:
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp LocalTimeAmbigous
     * In all other cases the conversion is unique:
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp LocalTimeUnique
     */
    SystemClock::TimePoint toSystem(LocalTime lt, Choose choose) const;
    /**
     * @brief Turns internal std/dst switching rules into a corresponding tz-string.
     *
     * The returned format is semantically identical to the one the time zone
     * has been constructed with but it is possible that is not identical
     * on the character by character level.
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp AssertTzToTzString
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp ToString
     * @{
     */
    IanaFormat  toIanaFormat () const;
    PosixFormat toPosixFormat() const;
    /** @} */
    /**
     * @brief True if zones are identical otherwise false.
     *
     * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp SameTimeZone
     */
    bool equals(const TimeZone& other) const;
private:
    Impl::TzStringParser m_tz;
};
/**
 * @brief True if zones are identical otherwise false.
 *
 * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp SameTimeZone
 *
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP bool operator==(const TimeZone& lhs, const TimeZone& rhs);
DFL_CHRONO_EXPIMP bool operator!=(const TimeZone& lhs, const TimeZone& rhs);
/** @} */
/**
 * @brief Returns the current time zone.
 *
 * If a current time zone has never been set a time zone representing
 * the UTC time is returned. The current time zone can be changed by
 * calling @ref DFL::Chrono::Registry::TimeZone::current().
 *
 * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp DefaultIsUtc
 * @snippet Chrono/Test/UnitTest/TestTimeZone.cpp ChangeCurrentZone
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP const TimeZone& currentZone();
}
}
