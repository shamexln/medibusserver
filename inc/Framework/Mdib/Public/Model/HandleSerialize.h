#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Handle)

BOOST_CLASS_VERSION(::DFL::Mdib::Handle, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Handle, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Unversioned serialization support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::Handle& handle, const unsigned int /*version*/)
{
    ar & make_nvp("Handle", handle.string());
}

/**
 * @brief Unversioned deserialization support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::Handle& handle, const unsigned int /*version*/)
{
    std::string asciiString;
    ar & make_nvp("Handle", asciiString);

    handle = ::DFL::Mdib::Handle(asciiString);
}
}
}
