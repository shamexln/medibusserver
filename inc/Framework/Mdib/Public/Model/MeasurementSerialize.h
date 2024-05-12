#pragma once

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <Framework/Mdib/Public/Model/DecimalSerialize.h>
#include <Framework/Mdib/Public/Model/Measurement.h>
#include <Framework/Mdib/Public/Model/UnitSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Measurement)

BOOST_CLASS_VERSION(::DFL::Mdib::Measurement, 1)

BOOST_CLASS_TRACKING(::DFL::Mdib::Measurement, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::Measurement* /*src*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::Measurement& src, const unsigned int /*version*/)
{
    ar & make_nvp("Value", src.value());
    ar & make_nvp("Unit", src.unit());
    ar & make_nvp("Extensions", src.extensions());
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::Measurement* dst, const unsigned int /*version*/)
{
    // invoke inplace constructor with dummy data
    ::new(dst)::DFL::Mdib::Measurement{DFL::Mdib::Decimal{}, DFL::Mdib::Unit::UNSPECIFIED};
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::Measurement& dst, const unsigned int version)
{
    DFL::Mdib::Decimal value;
    ar & make_nvp("Value", value);
    DFL::Mdib::Unit unit{""};
    ar & make_nvp("Unit", unit);

    DFL::Mdib::ExtensionTypes extensions;
    if (version > 0)
    {
        ar & make_nvp("Extensions", extensions);
    }

    dst = ::DFL::Mdib::Measurement(value, unit, std::move(extensions));
}
}
}
