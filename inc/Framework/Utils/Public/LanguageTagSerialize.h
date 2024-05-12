#pragma once

#include <Framework/Utils/Public/LanguageTag.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Locale::LanguageTag)

BOOST_CLASS_VERSION(::DFL::Locale::LanguageTag, 0)

namespace boost
{
namespace serialization
{
/**
 * @brief Unversioned serialization support for Boost Serialization.
 * @ingroup Utils
 */
template<class Archive>
void save(Archive & ar, const ::DFL::Locale::LanguageTag& lt, const unsigned int /*version*/)
{
    const auto& s(lt.tag());
    ar & make_nvp("LangTag", s);
}

/**
 * @brief Unversioned deserialization support for Boost Serialization.
 * @ingroup Utils
 */
template<class Archive>
void load(Archive & ar, ::DFL::Locale::LanguageTag& lt, const unsigned int /*version*/)
{
    std::string s;
    ar & make_nvp("LangTag", s);

    lt = DFL::Locale::LanguageTag(s);
}
}
}
