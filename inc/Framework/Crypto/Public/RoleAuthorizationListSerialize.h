#pragma once

#include <Framework/Crypto/Public/RoleAuthorizationList.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Crypto::RoleAuthorizationList)
BOOST_CLASS_VERSION(::DFL::Crypto::RoleAuthorizationList, 0)

namespace boost
{
namespace serialization
{
template <class Archive>
void save(Archive& ar,
          const ::DFL::Crypto::RoleAuthorizationList& r,
          const unsigned int /*version*/)
{
    const std::string& s{r.str()};
    ar& boost::serialization::make_nvp("RawString", s);
}

template <class Archive>
void load(Archive& ar,
          ::DFL::Crypto::RoleAuthorizationList& r,
          const unsigned int /*version*/)
{
    std::string s{};
    ar& boost::serialization::make_nvp("RawString", s);
    r = ::DFL::Crypto::RoleAuthorizationList{std::move(s)};
}
}
}
