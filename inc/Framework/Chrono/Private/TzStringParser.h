#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemTime.h>

#include <cstdint>
#include <string>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
/**
 * @brief Parser utility for Time Zone and Daylight Saving configuration strings ("TZ string").
 *
 * The configuration string format is very similar to the string used by the Linux/Unix
 * command tzset, and to the TZ-variable in the GNU libc library.
 *
 * Reference of format in the GLIB documentation (2017-01-10):
 *      http://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
 * This includes an extension to POSIX.1, where the range of the hour fields in the DST rules
 * are extended from 0..23 to -167..167, e.g. used in Israel since at least 2016.
 *
 * The format supported in this parser has the following deviations from the reference format:
 *  - Strings starting with ':', where a file is referenced, are not supported.
 *  - The sign of the time zone is inverted: + means east/earlier from Greenwich/0 degrees, - means west/later.
 *  - The time zone names can have 3..10 characters (standard gives no upper limit).
 *  - The special case of a string "WART-4WARST,J1/0,J365/25", which switches between standard time
 *    and summer at the same date and time (e.g. Western Argentina Summer Time in prior years),
 *    should be interpreted as summer time / day light saving is effective the whole year.
 *    This is not supported, instead use a simpler string "WARST-3" which has the same effect.
 */
class DFL_CHRONO_EXPIMP TzStringParser
{
public :
    TzStringParser();
    /**
     * == operator
     * @param[in] rhs: other instance of the class
     * @return true if internal parser results (not the input strings) are equal
     */
    bool operator==(const TzStringParser& rhs) const;
    /**
     * != operator
     * @param[in] rhs: other instance of the class
     * @return true if internal parser results (not the input strings) are not equal
     */
    bool operator!=(const TzStringParser& rhs) const;

    /**
     * Parse the given time zone string, and update the result members internally.
     * Results are available with getter methods of this class.
     *
     * The format of the TZ string is according to the GLIB documentation (2017-01-10):
     *      http://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
     *
     * This includes an extension to POSIX.1, where the range of the hour fields in the DST rules
     * are extended from 0..23 to -167..167, e.g. used in Israel since at least 2016.
     *
     * Some restrictions are documented in the class comment, see above.
     *
     * The only difference between Iana and the POSIX format is the sign in the time offset
     * fields of the standard and (optional) daylight-saving time zone:
     * The sign of the time zone is inverted: + means east/earlier from Greenwich/0 degrees, - means west/later.
     *
     * @param[in] tzString: time zone string to parse, in Iana style
     * @return true on success, false on any error, like format or range violations
     */
    bool parseIanaTzString(const std::string& tzString);

    /**
     * Parse the given time zone string, and update the result members internally.
     * Results are available with getter methods of this class.
     *
     * The format of the TZ string is according to the GLIB documentation (2017-01-10):
     *      http://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
     *
     * This includes an extension to POSIX.1, where the range of the hour fields in the DST rules
     * are extended from 0..23 to -167..167, e.g. used in Israel since at least 2016.
     *
     * Some restrictions are documented in the class comment, see above.
     *
     * This function parses strings of POSIX style. See method parseIanaTzString for
     * the difference between Iana and the POSIX format.
     *
     * @param[in] tzString: time zone string to parse, in POSIX style
     * @return true on success, false on any error, like format or range violations
     */
    bool parsePosixTzString(const std::string& tzString);

    /**
     * @brief Swaps this with other.
     */
    void swap(TzStringParser& other);

    /**
     * Creates a Iana time zone string from the currently active parameters.
     * May be used to convert from POSIX to Iana style:
     *   Input a POSIX string with method parsePosixTzString, and retrieve a string with this method.
     *   @note No roundtrip: This does'nt always produce an exact copy of the TZ string input of parse...().
     * @return the created TZ String in Iana style
     */
    std::string createIanaTzString() const;

    /**
     * Creates a POSIX time zone string from the currently active parameters.
     * May be used to convert from Iana to POSIX style.
     *   Input a Iana string with method parseIanaTzString, and retrieve a string with this method.
     *   @note No roundtrip: This does'nt always produce an exact copy of the TZ string input of parse...().
     * @return the created TZ String in POSIX style
     */
    std::string createPosixTzString() const;

    /**
     * get the standard time zone name after parsing
     * @return the standard time zone name
     */
    std::string getStdTimezoneName() const;

    /**
     * get the DST time zone name after parsing
     * @return the DST time zone name
     */
    std::string getDstTimezoneName() const;

    /**
     * check if the parsed time zone string contains daylight saving time information
     * @return true if daylight-saving ("DST") is configured, false if not
     */
    bool hasDst() const;

    /**
     * get the offset between UTC and local time when daylight saving is not active
     * @return offset in seconds
     */
    Seconds getStdUtcOffsetSeconds() const;

    /**
     * get the offset between UTC and local time when daylight saving is active
     * @return offset in seconds
     */
    Seconds getDstUtcOffsetSeconds() const;

    /**
     * get the offset between standard time and daylight saving time
     * @return offset in seconds
     */
    Seconds getDstStdOffsetSeconds() const;

    /**
     * get the time-point (UTC) for the transition from standard to DST for a given year.
     * @param[in] year:  the number of the year
     * @return the UTC time-point when transition standard->DST (winter->summer) occurs
     */
    SystemSeconds getTimePointOfTransitionToDst(int year) const;

    /**
     * get the time-point (UTC) for the transition from from DST to standard for a given year.
     * @param[in] year:  the number of the year
     * @return the UTC time-point when transition DST->standard (summer->winter) occurs
     */
    SystemSeconds getTimePointOfTransitionToStandard(int year) const;

    /**
     * @brief Format a time in seconds into [-]h[:mm[:ss]],
     * sign only when negative,
     * h has only needed number of digits,
     * and mm and ss (2 digits) only if needed by offset granularity.
     * @param[in] offsetSec: offset/time in seconds
     * @return the formatted string
     */
    static std::string formatOffset(int offsetSec);

    /**
     * @brief Format a time in seconds into the format of time zone offsets in ISO8601.
     * @param[in] offsetSec: offset/time in seconds
     * @return the formatted string, in the format (+|-)hh:mm (both with 2 digits)
     */
    static std::string formatOffsetIso8601(int offsetSec);

private :

    /**
     * string format styles
     */
    using StringStyle_t = enum
    {
        PosixStyle,   ///< POSIX style, time zone offset negative means east of Greenwich
        IanaStyle  ///< Iana style, time zone offset negative means west of Greenwich
    };

    /**
     * type of DST transition rule
     */
    using RuleType = enum
    {
        JULIAN_DAY = 0,
        MONTH_NTH_DAY_OF_WEEK = 1,
        DAY_OF_YEAR = 2
    };

    /**
     * structure to hold the day light saving switch date & time points (relative to begin of the year)
     */
    struct DstRule
    {
        TzStringParser::RuleType type;
        int day;
        int month;
        int week;
        int32_t time;  // in seconds
    };

    /**
     * Parse the given time zone string, and update the result members internally.
     * Results are available with getter methods of this class.
     *
     * For the format see public methods parsePosixTzString and parseIanaTzString.
     *
     * @param[in] tzString: time zone string to parse
     * @param[in] style: style of the string, PosixStyle or IanaStyle
     * @return true on success, false on any error, like format or range violations
     */
    bool parseTzStringCommon(const char* tzString, StringStyle_t style);

    /**
     * Creates a time zone string from the currently active parameters.
     * Some fields depend on the given format style, see public methods parsePosixTzString and parseIanaTzString.
     *   @note No roundtrip: This does'nt always produce an exact copy of the TZ string input of parse...().
     * @return the created TZ String in Iana style
     */
    std::string createTzStringCommon(StringStyle_t style) const;

    static const char* getZoneName(const char* pTzString);

    static const char* getTzOffset(int32_t& tzOffset, const char* pTzString);

    static const char* getSecs(int32_t& secs, const char* pTzString, int maxHour);

    static const char* getNum(int& num, const char* pTzString, int min, int max);

    static const char* getRule(DstRule& rule, const char* pTzString);

    static std::string createDstRuleString(const DstRule& dstRule);

    /**
     * get the UTC transition time for a DST switch
     * @param[in] year  the number of the year
     * @param[in] dstRule  the rule of the DST transition, for summer or for winter switch
     * @param[in] offset  the time zone offset, standard or DST, corresponding to the given rule
     * @return the seconds of the transition time since 1st Januar of the given year, as UTC time
     */
    static int32_t getTransitionTime(int year, const DstRule& dstRule, int32_t offset);

    /**
     * get the time-point (UTC) for the transition for a given year and an offset from begin of the year.
     * @param[in] year  the number of the year
     * @param[in] secondsOfYear  the offset in seconds since year-01-01
     * @return the seconds of the transition time since 1st Januar of the given year, as UTC time
     */
    static SystemSeconds getTimePointOfSecondsOfYear(int year, int32_t secondsOfYear);

    std::string m_stdTzName{};
    std::string m_dstTzName{};
    int32_t m_stdTzOffsetSeconds{0};
    int32_t m_dstTzOffsetSeconds{0};
    bool m_hasDst{false};
    DstRule m_dstRuleToStd{};
    DstRule m_dstRuleToDst{};
};
}
}
}
