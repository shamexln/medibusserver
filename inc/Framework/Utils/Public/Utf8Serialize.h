#pragma once

#include <Framework/Utils/Public/Utf8.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Locale::Utf8)

BOOST_CLASS_VERSION(::DFL::Locale::Utf8, 0)

namespace boost
{
namespace serialization
{
/**
 * @brief Unversioned serialization support for Boost Serialization.
 * @ingroup Utils
 */
template<class Archive>
void save(Archive & ar, const ::DFL::Locale::Utf8& utf8, const unsigned int /*version*/)
{
    const std::string& utf8string(utf8.value());
    ar & make_nvp("Utf8", utf8string);
}

/**
 * @brief Unversioned deserialization support for Boost Serialization.
 * @ingroup Utils
 */
template<class Archive>
void load(Archive & ar, ::DFL::Locale::Utf8& utf8, const unsigned int /*version*/)
{
    std::string utf8string;
    ar & make_nvp("Utf8", utf8string);

    utf8 = DFL::Locale::Utf8(utf8string);;
}
}
}
