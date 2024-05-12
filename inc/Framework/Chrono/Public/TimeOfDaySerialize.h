#pragma once

#include <Framework/Chrono/Public/DurationSerialize.h>
#include <Framework/Chrono/Public/TimeOfDay.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::TimeOfDay<::DFL::Chrono::Hours>)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::TimeOfDay<::DFL::Chrono::Minutes>)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::TimeOfDay<::DFL::Chrono::Seconds>)

BOOST_CLASS_VERSION(::DFL::Chrono::TimeOfDay<::DFL::Chrono::Hours>  , 0)
BOOST_CLASS_VERSION(::DFL::Chrono::TimeOfDay<::DFL::Chrono::Minutes>, 0)
BOOST_CLASS_VERSION(::DFL::Chrono::TimeOfDay<::DFL::Chrono::Seconds>, 0)

namespace boost
{
namespace serialization
{
// boost macro BOOST_SERIALIZATION_SPLIT_FREE does not allow templates
template<class Archive, class Duration>
inline void serialize(Archive & ar, ::DFL::Chrono::TimeOfDay<Duration> & t, const unsigned int version)
{
    split_free(ar, t, version);
}


// separate implementation are provided, to allow in XML view for example separate values

// hours
template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Hours>* /*tod*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Hours>& tod, const unsigned int /*version*/)
{
    const ::DFL::Chrono::Hours hours(tod.hours());
    ar & make_nvp("Hours", hours);
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Hours>* tod, const unsigned int /*version*/)
{
    // invoke inplace constructor to initialize instance
    // fill with dummy data, will be filled in load() method below
    ::new(tod)::DFL::Chrono::TimeOfDay<::DFL::Chrono::Hours>(::DFL::Chrono::Hours(0));
}

template<class Archive>
void load(Archive & ar, ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Hours>& tod, const unsigned int /*version*/)
{
    DFL::Chrono::Hours hours;
    ar & make_nvp("Hours", hours);
    tod = DFL::Chrono::TimeOfDay<DFL::Chrono::Hours>(hours);
}

// minutes
template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Minutes>* /*tod*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Minutes>& tod, const unsigned int /*version*/)
{
    const ::DFL::Chrono::Hours hours(tod.hours());
    ar & make_nvp("Hours", hours);
    const ::DFL::Chrono::Minutes minutes(tod.minutes());
    ar & make_nvp("Minutes", minutes);
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Minutes>* tod, const unsigned int /*version*/)
{
    // invoke inplace constructor to initialize instance
    // fill with dummy data, will be filled in load() method below
    ::new(tod)::DFL::Chrono::TimeOfDay<::DFL::Chrono::Minutes>(::DFL::Chrono::Minutes(0));
}

template<class Archive>
void load(Archive & ar, ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Minutes>& tod, const unsigned int /*version*/)
{
    DFL::Chrono::Hours hours;
    ar & make_nvp("Hours", hours);
    DFL::Chrono::Minutes minutes;
    ar & make_nvp("Minutes", minutes);
    tod = DFL::Chrono::TimeOfDay<DFL::Chrono::Minutes>(hours, minutes);
}

// seconds
template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Seconds>* /*tod*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Seconds>& tod, const unsigned int /*version*/)
{
    const ::DFL::Chrono::Hours hours(tod.hours());
    ar & make_nvp("Hours", hours);
    const ::DFL::Chrono::Minutes minutes(tod.minutes());
    ar & make_nvp("Minutes", minutes);
    const ::DFL::Chrono::Seconds seconds(tod.seconds());
    ar & make_nvp("Seconds", seconds);
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Seconds>* tod, const unsigned int /*version*/)
{
    // invoke inplace constructor to initialize instance
    // fill with dummy data, will be filled in load() method below
    ::new(tod)::DFL::Chrono::TimeOfDay<::DFL::Chrono::Seconds>(::DFL::Chrono::Seconds(0));
}

template<class Archive>
void load(Archive & ar, ::DFL::Chrono::TimeOfDay<::DFL::Chrono::Seconds>& tod, const unsigned int /*version*/)
{
    DFL::Chrono::Hours hours;
    ar & make_nvp("Hours", hours);
    DFL::Chrono::Minutes minutes;
    ar & make_nvp("Minutes", minutes);
    DFL::Chrono::Seconds seconds;
    ar & make_nvp("Seconds", seconds);
    tod = DFL::Chrono::TimeOfDay<DFL::Chrono::Seconds>(hours, minutes, seconds);
}

// sub-seconds
template<class Archive, class Duration>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Chrono::TimeOfDay<Duration>* /*tod*/, const unsigned int /*version*/)
{
}

template<class Archive, class Duration>
void save(Archive & ar, const ::DFL::Chrono::TimeOfDay<Duration>& tod, const unsigned int /*version*/)
{
    const ::DFL::Chrono::Hours hours(tod.hours());
    ar & make_nvp("Hours", hours);
    const ::DFL::Chrono::Minutes minutes(tod.minutes());
    ar & make_nvp("Minutes", minutes);
    const ::DFL::Chrono::Seconds seconds(tod.seconds());
    ar & make_nvp("Seconds", seconds);
    const Duration subseconds(tod.subseconds());
    ar & make_nvp("Subseconds", subseconds);
}

template<class Archive, class Duration>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Chrono::TimeOfDay<Duration>* tod, const unsigned int /*version*/)
{
    // invoke inplace constructor to initialize instance
    // fill with dummy data, will be filled in load() method below
    ::new(tod)::DFL::Chrono::TimeOfDay<Duration>(Duration(0));
}

template<class Archive, class Duration>
void load(Archive & ar, ::DFL::Chrono::TimeOfDay<Duration>& tod, const unsigned int /*version*/)
{
    DFL::Chrono::Hours hours;
    ar & make_nvp("Hours", hours);
    DFL::Chrono::Minutes minutes;
    ar & make_nvp("Minutes", minutes);
    DFL::Chrono::Seconds seconds;
    ar & make_nvp("Seconds", seconds);
    Duration subseconds(0);
    ar & make_nvp("Subseconds", subseconds);
    tod = DFL::Chrono::TimeOfDay<Duration>(hours, minutes, seconds, subseconds);
}
}
}
