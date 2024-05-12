#pragma once

#include <Framework/Utils/Public/Application/Identifier.h>
#include <Framework/Utils/Public/Application/SoftwareVersionNumber.h>
#include <Framework/Utils/Public/Application/SoftwareVersionNumberSerialize.h>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

#include <string>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Application::Identifier)

BOOST_CLASS_VERSION(::DFL::Application::Identifier, 0)

namespace boost
{
namespace serialization
{
/**
 * @brief Saves given application identifier in given archive.
 *
 * @ingroup Utils
 */
template <class Archive>
void save(Archive& ar, const ::DFL::Application::Identifier& id, const unsigned int /*version*/)
{
    ar & boost::serialization::make_nvp("MaterialNumber", id.materialNumber().get());
    ar & boost::serialization::make_nvp("SerialNumber", id.serialNumber().get());
    ar & boost::serialization::make_nvp("SoftwareVersionNumber", id.softwareVersionNumber());
}
/**
 * @brief Loads given application identifier from given archive.
 *
 * @ingroup Utils
 */
template <class Archive>
void load(Archive& ar, ::DFL::Application::Identifier& id, const unsigned int /*version*/)
{
    std::string materialNumber{};
    ar & boost::serialization::make_nvp("MaterialNumber", materialNumber);

    std::string serialNumber{};
    ar & boost::serialization::make_nvp("SerialNumber", serialNumber);

    ::DFL::Application::SoftwareVersionNumber softwareVersionNumber{};
    ar & boost::serialization::make_nvp("SoftwareVersionNumber", softwareVersionNumber);

    ::DFL::Application::Identifier tmp{
        ::DFL::Application::MaterialNumber{materialNumber},
        ::DFL::Application::SerialNumber{serialNumber},
        softwareVersionNumber};
    id.swap(tmp);
}
}
}
