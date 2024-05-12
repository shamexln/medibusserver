#pragma once

#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/Unit.h>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Unit)

BOOST_CLASS_VERSION(::DFL::Mdib::Unit, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Unit, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::Unit* /*in*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::Unit& in, const unsigned int /*version*/)
{
    const DFL::Mdib::CodedValue& cv(in);
    ar & make_nvp("Unit", cv);
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::Unit* out, const unsigned int /*version*/)
{
    ::new(out)::DFL::Mdib::Unit("");
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::Unit& out, const unsigned int /*version*/)
{
    DFL::Mdib::CodedValue cv(DFL::Mdib::CodingSystem{DFL::Mdib::CodingSystemId{DFL::Mdib::Uri{""}}},
                             DFL::Mdib::CodeId{DFL::Locale::Utf8{""}});
    ar & make_nvp("Unit", cv);

    out = DFL::Mdib::Unit(cv);
}

} /* namespace serialization */
} /* namespace boost */
