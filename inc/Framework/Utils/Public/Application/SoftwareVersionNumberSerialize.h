#pragma once

#include <Framework/Utils/Public/Application/SoftwareVersionNumber.h>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Application::SoftwareVersionNumber)

BOOST_CLASS_VERSION(::DFL::Application::SoftwareVersionNumber, 0)

namespace boost
{
namespace serialization
{
/**
 * @brief Saves given software version number in given archive.
 *
 * @ingroup Utils
 */
template <class Archive>
void save(Archive& ar, const ::DFL::Application::SoftwareVersionNumber& v, const unsigned int /*version*/)
{
    const unsigned int majorVersion = v.major().get();
    ar & boost::serialization::make_nvp("MajorVersion", majorVersion);

    const unsigned int minorVersion = v.minor().get();
    ar & boost::serialization::make_nvp("MinorVersion", minorVersion);

    const unsigned int patchVersion = v.patch().get();
    ar & boost::serialization::make_nvp("PatchVersion", patchVersion);
}
/**
 * @brief Loads given software version number from given archive.
 *
 * @ingroup Utils
 */
template <class Archive>
void load(Archive& ar, ::DFL::Application::SoftwareVersionNumber& v, const unsigned int /*version*/)
{
    unsigned int majorVersion{};
    ar & boost::serialization::make_nvp("MajorVersion", majorVersion);

    unsigned int minorVersion{};
    ar & boost::serialization::make_nvp("MinorVersion", minorVersion);

    unsigned int patchVersion{};
    ar & boost::serialization::make_nvp("PatchVersion", patchVersion);

    ::DFL::Application::SoftwareVersionNumber tmp{
        ::DFL::Application::MajorVersion{majorVersion},
        ::DFL::Application::MinorVersion{minorVersion},
        ::DFL::Application::PatchVersion{patchVersion}};
    v.swap(tmp);
}
}
}
