#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Oid.h>
#include <Framework/Utils/Public/OidSerialize.h>
#include <Framework/Utils/Public/Oids.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include <vector>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Oids)
BOOST_CLASS_VERSION(::DFL::Oids, 0)

namespace boost
{
namespace serialization
{
template <class Archive>
void save(Archive& ar, const ::DFL::Oids& oids, const unsigned int /*version*/)
{
    const std::vector<::DFL::Oid> vec{oids.cbegin(), oids.cend()};
    ar& boost::serialization::make_nvp("Oids", vec);
}

template <class Archive>
void load(Archive& ar, ::DFL::Oids& oids, const unsigned int /*version*/)
{
    std::vector<::DFL::Oid> vec{};
    ar& boost::serialization::make_nvp("Oids", vec);
    oids = ::DFL::Oids{vec};
}
}
}
