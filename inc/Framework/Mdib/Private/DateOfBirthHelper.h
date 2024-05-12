#pragma once

#include <Framework/Chrono/Public/TimeOfDay.h>
#include <Framework/Chrono/Public/YearMonthDay.h>
#include <Framework/Chrono/Public/ZonedTime.h>
#include <Framework/Mdib/Private/ExpImp.h>

#include <boost/optional/optional.hpp>

#include <variant>

namespace DFL::Mdib::Impl
{

using DateOfBirthVariant =
    std::variant<Chrono::LocalSeconds, // 1980-05-23T14:57:43
                 Chrono::Year,         // 1980
                 Chrono::YearMonth,    // 1980-05
                 Chrono::YearMonthDay, // 1980-05-23
                 Chrono::ZonedTime>;   // 1980-05-23T14:57:43+02:00;

boost::optional<DateOfBirthVariant> optionalDateOfBirthFromIsoString(const std::string& isoString);

std::string toIsoString(const DateOfBirthVariant& dateOfBirth);

DFL_MDIB_EXPIMP boost::optional<Chrono::Years> calcAgeInOptionalYears(const Chrono::YearMonthDay& today, const DateOfBirthVariant& dateOfBirth);
DFL_MDIB_EXPIMP boost::optional<Chrono::Months> calcAgeInOptionalMonths(const Chrono::YearMonthDay& today, const DateOfBirthVariant& dateOfBirth);

Chrono::Year toYear(const DateOfBirthVariant& dateOfBirth);
boost::optional<Chrono::Month> toOptionalMonth(const DateOfBirthVariant& dateOfBirth);
boost::optional<Chrono::Day> toOptionalDay(const DateOfBirthVariant& dateOfBirth);
boost::optional<Chrono::YearMonthDay> toOptionalYearMonthDay(const DateOfBirthVariant& dateOfBirth);
boost::optional<Chrono::TimeOfDay<Chrono::Seconds> > toOptionalTimeOfDay(const DateOfBirthVariant& dateOfBirth);

}
