#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Oid.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <string>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Oid)
BOOST_CLASS_VERSION(::DFL::Oid, 0)
BOOST_CLASS_TRACKING(::DFL::Oid, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
template <class Archive>
inline void save_construct_data(Archive& /*ar*/,
                                const ::DFL::Oid* /*in*/,
                                const unsigned int /*version*/)
{
}

template <class Archive>
void save(Archive& ar, const ::DFL::Oid& oid, const unsigned int /*version*/)
{
    ar& boost::serialization::make_nvp("Oid", oid.dotNotation().get());
}

template <class Archive>
void load(Archive& ar, ::DFL::Oid& oid, const unsigned int /*version*/)
{
    std::string dotStr{};
    ar& boost::serialization::make_nvp("Oid", dotStr);
    oid = ::DFL::Oid{::DFL::Oid::DotNotation{dotStr}};
}

template <class Archive>
inline void load_construct_data(Archive& /*ar*/,
                                ::DFL::Oid* out,
                                const unsigned int /*version*/)
{
    ::new (out)::DFL::Oid{::DFL::Oid::DotNotation{"0"}};
}
}
}
