#pragma once

#include <Framework/Chrono/Public/YearMonthDay.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::YearMonthDay)

BOOST_CLASS_VERSION(::DFL::Chrono::YearMonthDay, 0)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Chrono::YearMonthDay* /*ymd*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Chrono::YearMonthDay& ymd, const unsigned int /*version*/)
{
    const int year(ymd.year().value());
    ar & make_nvp("Year", year);
    const unsigned month(ymd.month().value());
    ar & make_nvp("Month", month);
    const unsigned day(ymd.day().value());
    ar & make_nvp("Day", day);
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Chrono::YearMonthDay* ymd, const unsigned int /*version*/)
{
    // invoke inplace constructor to initialize instance
    // fill with dummy data, will be filled in load() method below
    ::new(ymd)::DFL::Chrono::YearMonthDay(::DFL::Chrono::SystemDays(DFL::Chrono::Days(0)));
}

template<class Archive>
void load(Archive & ar, ::DFL::Chrono::YearMonthDay& ymd, const unsigned int /*version*/)
{
    int year{};
    ar & make_nvp("Year", year);
    unsigned month{};
    ar & make_nvp("Month", month);
    unsigned day{};
    ar & make_nvp("Day", day);
    ymd = DFL::Chrono::YearMonthDay(DFL::Chrono::Year(year), DFL::Chrono::Month(month), DFL::Chrono::Day(day));
}

} /* namespace serialization */
} /* namespace boost */
