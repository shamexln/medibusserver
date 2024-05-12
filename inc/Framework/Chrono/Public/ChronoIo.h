#pragma once

#include <Framework/Chrono/Private/Convert.h>
#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/LocalTime.h>
#include <Framework/Chrono/Public/TimeOfDay.h>

#include <Framework/Format/Public/Pad.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/ToString.h>

#include <boost/chrono/chrono_io.hpp>

#include <cstdlib>
#include <iosfwd>
#include <string>

/**
 * @file
 * @brief Contains operators for streaming various chrono types
 * into std-ostream and @ref DFL::Format::Stream
 *
 * @ingroup Chrono
 */
namespace DFL
{
namespace Chrono
{
class Day;
class IanaFormat;
class Month;
class MonthDayLast;
class PosixFormat;
class TimeZone;
class Transition;
class Transitions;
class Year;
class YearMonth;
class YearMonthDay;
class YearMonthDayLast;
class ZonedTime;
struct SystemInfo;
/**
 * @brief Formats given duration with a long description.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp StdStreamingDurations
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Years& d);
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Months& d);
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Weeks& d);
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Days& d);
/** @} */
/**
 * @brief Formats given year padded with leading 0.
 *
 * @snippet Chrono/Test/UnitTest/TestYear.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Year& d);
/**
 * @brief Formats given month as 3 letter string.
 *
 * @snippet Chrono/Test/UnitTest/TestMonth.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Month& d);
/**
 * @brief Formats given day padded with leading 0.
 *
 * @snippet Chrono/Test/UnitTest/TestDay.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Day& d);
/**
 * @brief Formats given date as Y-M-D into stream.
 *
 * @snippet Chrono/Test/UnitTest/TestYearMonthDay.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const YearMonthDay& date);
/**
 * @brief Formats given date as Y-M into stream.
 *
 * @snippet Chrono/Test/UnitTest/TestYearMonth.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const YearMonth& date);
/**
 * @brief Formats given zoned time as local time point wit utc offset into stream.
 *
 * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp TestData
 * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const ZonedTime& zt);
/**
 * @brief Formats given system infos.
 *
 * @snippet Chrono/Test/UnitTest/TestSystemInfo.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const SystemInfo& si);
/**
 * @brief Formats given last of month as 3 letter month with "last" appended.
 *
 * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const MonthDayLast& mdl);
/**
 * @brief Formats given @ref DFL::Chrono::YearMonthDayLast into stream.
 *
 * @snippet Chrono/Test/UnitTest/TestYearMonthDayLast.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const YearMonthDayLast& ymdl);
/**
 * @brief Formats given @ref DFL::Chrono::LocalTime into stream.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const LocalTime& lt);
/**
 * @brief Same as @ref DFL::Chrono::TimeZone::toIanaFormat.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const TimeZone& tz);
/**
 * @brief @ref DFL::Chrono::TimeZone::toIanaFormat.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const IanaFormat& ianaFmt);
/**
 * @brief @ref DFL::Chrono::TimeZone::toPosixFormat.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const PosixFormat& posixFmt);
/**
 * @brief String representation of a transition.
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp Streaming
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Transition& transition);
/**
 * @brief String representation of a transitions.
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp StreamingTransitions
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::ostream& operator<<(std::ostream& str, const Transitions& transitions);
/**
 * @brief Formats given time as hh:mm::ss.fraction into stream.
 *
 * Depending on the precision the fraction and the ss part could be missing.
 *
 * @snippet Chrono/Test/UnitTest/TestTimeOfDay.cpp Streaming
 * @ingroup Chrono
 * @{
 */
template<class Duration>
std::ostream& operator<<(std::ostream& str, const TimeOfDay<Duration>& tod);
template<>
std::ostream& operator<<(std::ostream& str, const TimeOfDay<Seconds>& tod);
template<>
std::ostream& operator<<(std::ostream& str, const TimeOfDay<Minutes>& tod);
template<>
std::ostream& operator<<(std::ostream& str, const TimeOfDay<Hours>& tod);
/** @} */
template<class Duration>
inline std::ostream& operator<<(std::ostream& str, const TimeOfDay<Duration>& tod)
{
    str << Format::toString(tod);
    return str;
}

template<>
inline std::ostream& operator<<(std::ostream& str, const TimeOfDay<Seconds>& tod)
{
    str << Format::toString(tod);
    return str;
}

template<>
inline std::ostream& operator<<(std::ostream& str, const TimeOfDay<Minutes>& tod)
{
    str << Format::toString(tod);
    return str;
}

template<>
inline std::ostream& operator<<(std::ostream& str, const TimeOfDay<Hours>& tod)
{
    str << Format::toString(tod);
    return str;
}
}
}
namespace DFL
{
namespace Format
{
/**
 * @brief Formats given duration with a short description.
 *
 * @snippet Chrono/Test/UnitTest/TestDuration.cpp FmtStreamDurations
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Years& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Months& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Weeks& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Days& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Hours& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Minutes& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Seconds& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Milliseconds& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Microseconds& d);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Nanoseconds& d);
/** @} */
/**
 * @brief Formats given year padded with leading 0.
 *
 * @snippet Chrono/Test/UnitTest/TestYear.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Year& d);
/**
 * @brief Formats given month as 3 letter string.
 *
 * @snippet Chrono/Test/UnitTest/TestMonth.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Month& d);
/**
 * @brief Formats given day padded with leading 0.
 *
 * @snippet Chrono/Test/UnitTest/TestDay.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Day& d);
/**
 * @brief Formats given date into stream.
 * @param str Stream to put date into.
 * @param date Date to be formatted.
 * @return Stream with formatted date in it.
 * @ingroup Chrono
 * @{
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::YearMonthDay& date);
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::YearMonth& date);
/** @} */
/**
 * @brief Formats given zoned time as local time point wit utc offset into stream.
 *
 * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp TestData
 * @snippet Chrono/Test/UnitTest/TestZonedTime.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::ZonedTime& zt);
/**
 * @brief Formats given system info.
 *
 * @snippet Chrono/Test/UnitTest/TestSystemInfo.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::SystemInfo& si);
/**
 * @brief Formats given last of month as 3 letter month with "last" appended.
 *
 * @snippet Chrono/Test/UnitTest/TestMonthDayLast.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::MonthDayLast& mdl);
/**
 * @brief Formats given @ref DFL::Chrono::YearMonthDayLast into stream.
 *
 * @snippet Chrono/Test/UnitTest/TestYearMonthDayLast.cpp Streaming
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::YearMonthDayLast& ymdl);
/**
 * @brief Formats given @ref DFL::Chrono::LocalTime into stream.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::LocalTime& lt);
/**
 * @brief Same as @ref DFL::Chrono::TimeZone::toIanaFormat.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::TimeZone& tz);
/**
 * @brief @ref DFL::Chrono::TimeZone::toIanaFormat.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::IanaFormat& ianaFmt);
/**
 * @brief @ref DFL::Chrono::TimeZone::toPosixFormat.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::PosixFormat& posixFmt);
/**
 * @brief String representation of a transition.
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp Streaming
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Transition& transition);
/**
 * @brief String representation of a transitions.
 *
 * @snippet Chrono/Test/UnitTest/TestTransitions.cpp StreamingTransitions
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP Stream& operator<<(Stream& str, const Chrono::Transitions& transitions);
/**
 * @brief Formats given time as hh:mm::ss.fraction into stream.
 *
 * Depending on the precision the fraction and the ss part could be missing.
 *
 * @snippet Chrono/Test/UnitTest/TestTimeOfDay.cpp Streaming
 * @ingroup Chrono
 * @{
 */
template<class Duration>
Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Duration>& tod);
template<>
Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Chrono::Seconds>& tod);
template<>
Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Chrono::Minutes>& tod);
template<>
Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Chrono::Hours>& tod);
/** @} */
template<class Duration>
inline Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Duration>& tod)
{
    if(tod.toDuration() < Chrono::Hours(0)) str << '-';
    str << pad(std::abs(                  tod.hours()  .count()) , 2, '0') << ':'
        << pad(std::abs(                  tod.minutes().count()) , 2, '0') << ':'
        << pad(std::abs(static_cast<long>(tod.seconds().count())), 2, '0');

    const long microSec = std::abs(static_cast<long>(Chrono::duration_cast<Chrono::Microseconds>(tod.subseconds()).count()));
    if(microSec)
    {
        // remove trailing 0 from subseconds as of:
        // https://www.w3.org/TR/xmlschema-2/#dateTime-canonical-representation section 3,2.7.2
        Stream strMicroSec;
        strMicroSec << pad(microSec, 6, '0');
        str << '.' << Chrono::Impl::removeTrailingZeros(strMicroSec.cStr());
    }
    return str;
}

template<>
inline Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Chrono::Seconds>& tod)
{
    const Chrono::TimeOfDay<Chrono::Microseconds> ms(tod.toDuration());
    str << ms;
    return str;
}

template<>
inline Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Chrono::Minutes>& tod)
{
    if(tod.toDuration() < Chrono::Hours(0)) str << '-';
    str << pad(std::abs(tod.hours()  .count()) , 2, '0') << ':'
        << pad(std::abs(tod.minutes().count()) , 2, '0');
    return str;
}

template<>
inline Stream& operator<<(Stream& str, const Chrono::TimeOfDay<Chrono::Hours>& tod)
{
    const Chrono::TimeOfDay<Chrono::Minutes> ms(tod.toDuration());
    str << ms;
    return str;
}
}
}
