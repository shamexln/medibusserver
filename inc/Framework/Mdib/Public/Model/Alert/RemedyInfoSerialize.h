#pragma once

#include <Framework/Mdib/Public/Model/Alert/RemedyInfo.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Mdib/Public/Model/LocalizedTextSerialize.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::RemedyInfo)

BOOST_CLASS_VERSION(::DFL::Mdib::RemedyInfo, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::RemedyInfo, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::RemedyInfo& src, const unsigned int /*version*/)
{
    ar & make_nvp("Description", src.description());
    ar & make_nvp("Extensions", src.extensions());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::RemedyInfo* dst, const unsigned int /*version*/)
{
    ::new(dst) ::DFL::Mdib::RemedyInfo{::DFL::Mdib::LocalizedTexts{}};
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::RemedyInfo& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::LocalizedTexts description;
    ar & make_nvp("Description", description);

    ::DFL::Mdib::ExtensionTypes extensions;
    ar & make_nvp("Extensions", extensions);

    dst = ::DFL::Mdib::RemedyInfo(description, std::move(extensions));
}

}
}
