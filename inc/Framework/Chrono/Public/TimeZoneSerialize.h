#pragma once

#include <Framework/Chrono/Public/TimeZone.h>
#include <Framework/Chrono/Private/TimeZone.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::IanaFormat)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::PosixFormat)
BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::TimeZone)

BOOST_CLASS_VERSION(::DFL::Chrono::IanaFormat, 0)
BOOST_CLASS_VERSION(::DFL::Chrono::PosixFormat, 0)
BOOST_CLASS_VERSION(::DFL::Chrono::TimeZone, 0)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save(Archive& ar, const ::DFL::Chrono::IanaFormat& iana, const unsigned int /*version*/)
{
    const auto& ianaFmt = iana.str();
    ar & make_nvp("IanaFmt", ianaFmt);
}

template<class Archive>
inline void load(Archive& ar, ::DFL::Chrono::IanaFormat& iana, const unsigned int /*version*/)
{
    std::string ianaFmt;
    ar & make_nvp("IanaFmt", ianaFmt);

    iana = ::DFL::Chrono::IanaFormat(std::move(ianaFmt));
}

template<class Archive>
inline void save(Archive& ar, const ::DFL::Chrono::PosixFormat& posix, const unsigned int /*version*/)
{
    const auto& posixFmt = posix.str();
    ar & make_nvp("PosixFmt", posixFmt);
}

template<class Archive>
inline void load(Archive& ar, ::DFL::Chrono::PosixFormat& posix, const unsigned int /*version*/)
{
    std::string posixFmt;
    ar & make_nvp("PosixFmt", posixFmt);

    posix = ::DFL::Chrono::PosixFormat(std::move(posixFmt));
}

template<class Archive>
inline void save(Archive& ar, const ::DFL::Chrono::TimeZone& timezone, const unsigned int /*version*/)
{
    const auto& zone = timezone.toIanaFormat();
    ar & make_nvp("TimeZone", zone);
}

template<class Archive>
inline void load(Archive& ar, ::DFL::Chrono::TimeZone& timezone, const unsigned int /*version*/)
{
    ::DFL::Chrono::IanaFormat zone;
    ar & make_nvp("TimeZone", zone);

    timezone = ::DFL::Chrono::TimeZone(zone);
}

}
}
