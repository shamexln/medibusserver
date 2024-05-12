#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/DateOfBirthHelper.h>

#include <Framework/Chrono/Public/TimeOfDay.h>
#include <Framework/Chrono/Public/YearMonthDay.h>

#include <boost/optional.hpp>

#include <string>

namespace DFL
{
namespace Mdib
{

class DateOfBirth;

namespace Convert
{
/**
 * @brief Parses a partial ISO string with optional time and time zone.
 * @details Parsing errors lead to \c boost::none.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<DateOfBirth> toOptionalDateOfBirth(const std::string& partialIsoString);
}


/**
 * @brief Container for date of birth variants.
 * @details
 * The date of birth can be specified with different precisions.
 * Sometime it is possible to have only the year of birth,
 * while in other circumstances a local time of day is also provided.
 * Examples for valid date of birth strings are:
 * - 1980
 * - 1980-11
 * - 1980-11-23
 * - 1980-11-23T02:08:23 (local time)
 * - 1980-11-23T02:08:23+02:00 (local time plus timezone, equal to 1980-11-23T00:08:23Z)
 * - 1980-11-23T02:08:23Z ("Z" is same as "+00:00")
 *
 * According to XML Schema "1980-11-23T02:08" is an invalid value as it lacks the required seconds portion.
 * In case the seconds are not defined, %DateOfBirth assumes "00".
 *
 * It is a partial ISO string.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP DateOfBirth
{
    public:
        /**
         * @brief Default constructs a date of birth.
         *
         * Same as with int the value held is undefined.
         */
        DateOfBirth();
        /**
         * @brief Creates a date of birth from a date.
         */
        explicit DateOfBirth(const Chrono::YearMonthDay& ymd);

        /**
         * @brief Provides the partial ISO string.
         * @details For the UTC timezone 'Z' is used instead of '+00:00' or '-00:00'.
         */
        std::string isoString() const;

        /**
         * @brief Provides the year of birth.
         * @details The year of birth is the only information in date of birth that is always given.
         */
        Chrono::Year year() const;

        /**
         * @brief Provides the month of birth if given.
         */
        boost::optional<Chrono::Month> month() const;

        /**
         * @brief Provides the day of birth with respect to the month and year if available.
         */
        boost::optional<Chrono::Day> day() const;

        /**
         * @brief Provides the day of birth (if available).
         * @details In case only the year of birth or year-month is available,
         * this functions return \c boost::none, since the day is missing.
         */
        boost::optional<Chrono::YearMonthDay> date() const;

        /**
         * @brief Optional time of day.
         * @details In some cases the time of day is additionally available to the date.
         */
        boost::optional<Chrono::TimeOfDay<Chrono::Seconds>> timeOfDay() const;

        /**
         * @name Age calculation
         * @details In the calculation a given month or day is respected in age calculation,
         * while the time of day (and time zone information) is ignored.
         * (E.g, if someone is born at 4:00 am, but it is still 3:00 am the day counts in age calculation)
         * @{
         */
        boost::optional<Chrono::Years> calcAgeInYears(const Chrono::YearMonthDay& today) const;
        boost::optional<Chrono::Months> calcAgeInMonths(const Chrono::YearMonthDay& today) const;
        /** @} */

        /**
         * @brief Checks for equality.
         */
        bool equals(const DateOfBirth& rhs) const;

    private:
        DateOfBirth(Impl::DateOfBirthVariant dob);
        Impl::DateOfBirthVariant m_dateOfBirth;
        friend boost::optional<DateOfBirth> Convert::toOptionalDateOfBirth(const std::string&);
};

namespace Convert
{
/**
 * @brief Parses a partial ISO string with optional time and time zone.
 * @details Parsing errors lead to an exception.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP DateOfBirth toDateOfBirth(const std::string& partialIsoString);
}

/**
 * @brief Check for equality of two \ref DateOfBirth instances.
 */
bool operator==(const DateOfBirth& lhs, const DateOfBirth& rhs);

/**
 * @brief Check for inequality of two \ref DateOfBirth instances.
 */
bool operator!=(const DateOfBirth& lhs, const DateOfBirth& rhs);

inline bool operator ==(const DateOfBirth& lhs, const DateOfBirth& rhs)
{
    return lhs.equals(rhs);
}

inline bool operator !=(const DateOfBirth& lhs, const DateOfBirth& rhs)
{
    return !lhs.equals(rhs);
}

}
}
