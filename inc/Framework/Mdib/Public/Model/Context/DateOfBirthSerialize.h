#pragma once

#include <Framework/Mdib/Public/Model/Context/DateOfBirth.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::DateOfBirth)

BOOST_CLASS_TRACKING(::DFL::Mdib::DateOfBirth, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::DateOfBirth* /*in*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::DateOfBirth& dob, const unsigned int /*version*/)
{
    const std::string isoString(dob.isoString());
    ar & make_nvp("DateOfBirth", isoString);
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::DateOfBirth* out, const unsigned int /*version*/)
{
    // Dummy, since there is no default constructor,
    // will be replaced in load() method below.
    ::new(out)::DFL::Mdib::DateOfBirth(::DFL::Chrono::YearMonthDay(::DFL::Chrono::LocalDays(::DFL::Chrono::Days(0))));
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::DateOfBirth& dob, const unsigned int /*version*/)
{
    std::string isoString;
    ar & make_nvp("DateOfBirth", isoString);
    dob = ::DFL::Mdib::Convert::toDateOfBirth(isoString);
}

}
}
