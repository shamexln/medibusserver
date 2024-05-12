#pragma once

#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/Certificates.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include <vector>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Crypto::Certificates)
BOOST_CLASS_VERSION(::DFL::Crypto::Certificates, 0)

namespace boost
{
namespace serialization
{
template <class Archive>
inline void save(Archive& ar,
                 const ::DFL::Crypto::Certificates& r,
                 const unsigned int /*version*/)
{
    const std::vector<::DFL::Crypto::Certificate> vec{r.cbegin(), r.cend()};
    ar& boost::serialization::make_nvp("Certificates", vec);
}

template <class Archive>
inline void load(Archive& ar,
                 ::DFL::Crypto::Certificates& r,
                 const unsigned int /*version*/)
{
    std::vector<::DFL::Crypto::Certificate> vec{};
    ar& boost::serialization::make_nvp("Certificates", vec);
    r = ::DFL::Crypto::Certificates{vec.cbegin(), vec.cend()};
}
}
}
