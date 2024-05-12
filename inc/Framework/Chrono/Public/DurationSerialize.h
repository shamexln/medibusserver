#pragma once

#include <Framework/Chrono/Public/Duration.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Years)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Months)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Weeks)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Days)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Hours)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Minutes)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Seconds)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Milliseconds)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Microseconds)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::Nanoseconds)

BOOST_CLASS_VERSION(::DFL::Chrono::Years       , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Months      , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Weeks       , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Days        , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Hours       , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Minutes     , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Seconds     , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Milliseconds, 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Microseconds, 0)
BOOST_CLASS_VERSION(::DFL::Chrono::Nanoseconds , 0)

namespace boost
{
namespace serialization
{
template<class Archive, class Rep, class Period>
void save(Archive & ar, const DFL::Chrono::duration<Rep,Period>& duration, const unsigned int)
{
    const Rep count(duration.count());
    ar & make_nvp("Count", count);
}

template<class Archive, class Rep, class Period>
void load(Archive & ar, DFL::Chrono::duration<Rep,Period>& duration, const unsigned int)
{
    Rep count(0);
    ar & make_nvp("Count", count);
    duration = DFL::Chrono::duration<Rep,Period>(count);
}
}
}
