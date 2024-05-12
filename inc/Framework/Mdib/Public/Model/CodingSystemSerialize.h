#pragma once

#include <Framework/Mdib/Public/Model/CodingSystem.h>
#include <Framework/Mdib/Public/Model/LocalizedTextSerialize.h>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::CodingSystem)

BOOST_CLASS_VERSION(::DFL::Mdib::CodingSystem, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::CodingSystem, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::CodingSystem* /*in*/, const unsigned int /*version*/)
{
}
template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::CodingSystem& in, const unsigned int /*version*/)
{

    const std::string& id(in.id().get().get());
    ar & make_nvp("Id", id);
    const std::string& version(in.version().get());
    ar & make_nvp("Version", version);
    const DFL::Mdib::LocalizedTexts& names(in.names());
    ar & make_nvp("Names", names);
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::CodingSystem* out, const unsigned int /*version*/)
{
    ::new(out)::DFL::Mdib::CodingSystem(::DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("dummy")));
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::CodingSystem& out, const unsigned int /*version*/)
{
    std::string id;
    ar & make_nvp("Id", id);
    std::string version;
    ar & make_nvp("Version", version);
    DFL::Mdib::LocalizedTexts names;
    ar & make_nvp("Names", names);
    out = ::DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri(id)), DFL::Mdib::CodingSystemVersion(DFL::Locale::Utf8(version)), names);
}
}
}
