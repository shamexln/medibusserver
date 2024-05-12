/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Component/PhysicalConnectorInfo.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Mdib/Public/Model/LocalizedTextSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/vector.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::PhysicalConnectorInfo)

BOOST_CLASS_VERSION(::DFL::Mdib::PhysicalConnectorInfo, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::PhysicalConnectorInfo, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::PhysicalConnectorInfo& src, const unsigned int /*fileVersion*/)
{
    const auto& number = src.number();
    ar & make_nvp("Number", number);

    const auto& labels = src.labels();
    ar & make_nvp("Labels", labels);

    const auto& extensions = src.extensions();
    ar & make_nvp("Extensions", extensions);
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::PhysicalConnectorInfo& dst, const unsigned int /*version*/)
{
    boost::optional<::DFL::Mdib::PhysicalConnectorNumber> number{};
    ar & make_nvp("Number", number);

    ::DFL::Mdib::LocalizedTexts labels{};
    ar & make_nvp("Labels", labels);

    ::DFL::Mdib::ExtensionTypes extensions{};
    ar & make_nvp("Extensions", extensions);

    dst = ::DFL::Mdib::PhysicalConnectorInfo(
        number,
        labels,
        std::move(extensions));
}

}
}
