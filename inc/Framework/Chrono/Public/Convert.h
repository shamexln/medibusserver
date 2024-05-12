#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/LocalDateTime.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/TimeZone.h>
#include <Framework/Chrono/Public/UtcDateTime.h>
#include <Framework/Chrono/Public/ZonedTime.h>
#include <Framework/Config/Public/Attributes.h>
#include <boost/optional/optional.hpp>
#include <string>

/**
 * @file
 * @brief Contains various conversions from chrono types into other chrono types
 * and string conversions into standardised formats (ISO8601) or from those formats.
 *
 * @ingroup Chrono
 */
namespace DFL
{
namespace Chrono
{
class Year;
class Month;
class Day;
namespace Convert
{
/**
 * @brief DEPRECATED: Converts the given Chrono::SystemClock::Timepoint to local date time.
 * @param timePoint Chrono::SystemClock::TimePoint to be converted.
 * @return Timepont converted as local date time object.
 * @deprecated Please use @ref DFL::Chrono::ZonedTime instead.
 * @ingroup Chrono
 */
DFL_ATTRIBUTE_DEPRECATED("use DFL::Chrono::ZonedTime instead")
DFL_CHRONO_EXPIMP LocalDateTime toLocalDateTime(const SystemClock::TimePoint& timePoint);
/**
 * @brief DEPRECATED: Converts the given Chrono::SystemClock::Timepoint to utc date time.
 * @param timePoint Chrono::SystemClock::TimePoint to be converted.
 * @return Timepoint converted as utc date time object.
 * @deprecated Please use @ref DFL::Chrono::YearMonthDay instead.
 * @ingroup Chrono
 */
DFL_ATTRIBUTE_DEPRECATED("use DFL::Chrono::YearMonthDay instead")
DFL_CHRONO_EXPIMP UtcDateTime toUtcDateTime(const SystemClock::TimePoint& timePoint);
/**
 * @brief Converts given duration to an ISO8601 conform string.
 *
 * Here are some examples of how these strings look like:
 * @snippet Chrono/Test/UnitTest/TestChronoConvert.cpp Iso8601Duration
 * @param d Duration to be converted.
 * @return String conforming to ISO8601.
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::string toIso8601(const Nanoseconds& d);
/**
 * @brief Converts given ISO8601 string representation of a time point to a systemclock time point.
 *
 * The string representation has to be conform to the following grammar as defined in
 * (<a href="https://www.w3.org/TR/xmlschema-2/#duration">3.2.7 dateTime</a>):
 * '-'? yyyy '-' mm '-' dd 'T' hh ':' mm ':' ss ('.' s+)? (zzzzzz)?
 * String representing negative time points returns "none" since it is unclear how year 0 is handled.
 * Here are examples of valid time point strings:
 * @snippet Chrono/Test/UnitTest/TestChronoConvert.cpp ValidTimePointStrings
 * Here are examples of invalid time point strings:
 * @snippet Chrono/Test/UnitTest/TestChronoConvert.cpp InvalidTimePointStrings
 *
 * @param timePointAsString Text to be converted.
 * @return An optional systemclock time point which is "none" in case of an invalid string.
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP boost::optional<SystemClock::TimePoint> toTimePoint(const std::string& timePointAsString);
/**
 * @brief Converts given ISO8601 string representation of a time point to a zoned time point.
 *
 * Returns @c none in case of an invalid string.
 *
 * @snippet Chrono/Test/UnitTest/TestChronoConvert.cpp FromIso8601
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP boost::optional<ZonedTime> toZonedTime(const std::string& timePointAsString);
/**
 * @brief Converts given @ref Chrono::SystemClock::TimePoint to an ISO8601 string.
 *
 * The string representation is conform to the following grammar as defined in
 * (<a href="https://www.w3.org/TR/xmlschema-2/#duration">3.2.7 dateTime</a>):
 * '-'? yyyy '-' mm '-' dd 'T' hh ':' mm ':' ss ('.' s+)? (zzzzzz)?
 * Since a @ref Chrono::SystemClock::TimePoint is UTC based a Z is appended
 * to indicate the timezone offset.
 *
 * @par Example:
 * @snippet Chrono/Test/UnitTest/TestChronoConvert.cpp Iso8601SystemClockTimePoint
 *
 * @param timePoint Time to be converted.
 * @return An ISO8601 conform string.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::string toIso8601(const SystemClock::TimePoint& timePoint);
/**
 * @brief Converts given @ref Chrono::ZonedTime to an ISO8601 string.
 *
 * The string representation is conform to the following grammar as defined in
 * (<a href="https://www.w3.org/TR/xmlschema-2/#duration">3.2.7 dateTime</a>):
 * '-'? yyyy '-' mm '-' dd 'T' hh ':' mm ':' ss ('.' s+)? ( Z | (('+' | '-') hh ':' mm))
 *
 * @par Example:
 * @snippet Chrono/Test/UnitTest/TestChronoConvert.cpp Iso8601ZonedTimes
 *
 * @param zonedTime ZonedTime to be converted.
 * @return An ISO8601 conform string.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP std::string toIso8601(const ZonedTime& zonedTime);
/**
 * @brief Converts a year month day triplet to a systemclock time point.
 *
 * @param year Year.
 * @param month Month.
 * @param day Day.
 * @return An optional systemclock time point which is "none" in case of an invalid year month day triplet.
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP boost::optional<SystemClock::TimePoint> toTimePoint(const Year& year, const Month& month, const Day& day);
/**
 * @brief Either returns a valid time zone or none in case of an invalid tz string.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP boost::optional<TimeZone> toTimeZone(const IanaFormat& tzStr);
/**
 * @brief Either returns a valid time zone or none in case of an invalid tz string.
 *
 * @ingroup Chrono
 */
DFL_CHRONO_EXPIMP boost::optional<TimeZone> toTimeZone(const PosixFormat& tzStr);
}
}
}
