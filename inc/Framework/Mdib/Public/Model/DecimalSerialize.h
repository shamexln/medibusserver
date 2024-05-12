#pragma once

#include <Framework/Mdib/Public/Model/Decimal.h>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Decimal)

BOOST_CLASS_VERSION(::DFL::Mdib::Decimal, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Decimal, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::Decimal& in, const unsigned int /*version*/)
{
    const int value(in.intValue());
    ar & make_nvp("Value", value);
    const int exponent(in.intExponent());
    ar & make_nvp("Exponent", exponent);
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::Decimal& out, const unsigned int /*version*/)
{
    int value{};
    ar & make_nvp("Value", value);
    int exponent{};
    ar & make_nvp("Exponent", exponent);
    out = DFL::Mdib::Decimal(value, exponent);
}
}
}
