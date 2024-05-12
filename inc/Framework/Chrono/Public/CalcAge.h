#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/Month.h>
#include <Framework/Chrono/Public/Round.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/YearMonthDay.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Given the dates of today and birthday calculates the age.
 *
 * Only implemented for @ref DFL::Chrono::Years and @ref DFL::Chrono::Months.
 * If a higher resolution is wanted
 * use time points instead.
 *
 * @tparam DurationType Period in which age shall be returned.
 * @param today Date of today.
 * @param birthday Date of birth.
 * @return Age in given duration.
 * @ingroup Chrono
 */
template<class DurationType>
DurationType calcAge(const YearMonthDay& today, const YearMonthDay& birthday);
/**
 * @brief Given the dates of today and birthday calculates the age in @ref DFL::Chrono::Years.
 *
 * @param today Date of today.
 * @param birthday Date of birth.
 * @return Age @ref DFL::Chrono::Years.
 * @ingroup Chrono
 */
template<>
Years calcAge<Years>(const YearMonthDay& today, const YearMonthDay& birthday);
/**
 * @brief Given the dates of today and birthday calculates the age in @ref DFL::Chrono::Months.
 *
 * @param today Date of today.
 * @param birthday Date of birth.
 * @return Age @ref DFL::Chrono::Months.
 * @ingroup Chrono
 */
template<>
Months calcAge<Months>(const YearMonthDay& today, const YearMonthDay& birthday);
/**
 * @brief Given the birthday calculates the age. Today is retrieved from @ref DFL::Chrono::SystemClock::now().
 *
 * @tparam DurationType Period in which age shall be returned.
 * @param birthday Date of birth.
 * @return Age in given duration.
 * @ingroup Chrono
 */
template<class DurationType>
DurationType calcAge(const YearMonthDay& birthday);
template<>
/**
 * @brief Given the birthday calculates the age in @ref DFL::Chrono::Years.
 *
 * @param birthday Date of birth.
 * @return Age @ref DFL::Chrono::Years.
 * @ingroup Chrono
 */
Years calcAge<Years>(const YearMonthDay& birthday);
template<>
/**
 * @brief Given the birthday calculates the age in @ref DFL::Chrono::Months.
 *
 * @param birthday Date of birth.
 * @return Age @ref DFL::Chrono::Months.
 * @ingroup Chrono
 */
Months calcAge<Months>(const YearMonthDay& birthday);

template<>
inline Years calcAge<Years>(const YearMonthDay& today, const YearMonthDay& birthday)
{
    return floor<Years>(calcAge<Months>(today, birthday));
}

//! [CalcAge]
template <>
inline Months calcAge<Months>(const YearMonthDay& today,
                              const YearMonthDay& birthday)
{
    return (today.year() / today.month()) -
           (birthday.year() / birthday.month()) -
           Months{today.day() < birthday.day()};
}

template<>
inline Years calcAge<Years>(const YearMonthDay& birthday)
{
    return floor<Years>(calcAge<Months>(birthday));
}
//! [CalcAge]

template<>
inline Months calcAge<Months>(const YearMonthDay& birthday)
{
    return calcAge<Months>(floor<Days>(SystemClock::now()), birthday);
}
}
}
