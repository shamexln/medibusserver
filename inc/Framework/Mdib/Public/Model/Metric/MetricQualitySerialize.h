/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Metric/MetricQuality.h>
#include <Framework/Mdib/Public/Model/DecimalSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::MetricQuality)

BOOST_CLASS_VERSION(::DFL::Mdib::MetricQuality, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::MetricQuality, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::MetricQuality& src, const unsigned int /*fileVersion*/)
{
    const auto& validity = src.validity();
    ar & make_nvp("Validity", validity);

    const auto& mode = src.mode();
    ar & make_nvp("Mode", mode);

    const auto& qualityIndicator = src.qualityIndicator();
    ar & make_nvp("QualityIndicator", qualityIndicator);

    const auto& extensions = src.extensions();
    ar & make_nvp("Extensions", extensions);
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::MetricQuality& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::MeasurementValidity validity{};
    ar & make_nvp("Validity", validity);

    ::DFL::Mdib::GenerationMode mode{};
    ar & make_nvp("Mode", mode);

    ::DFL::Mdib::QualityIndicator qualityIndicator{};
    ar & make_nvp("QualityIndicator", qualityIndicator);

    ::DFL::Mdib::ExtensionTypes extensions{};
    ar & make_nvp("Extensions", extensions);

    dst = ::DFL::Mdib::MetricQuality(
        validity,
        mode,
        qualityIndicator,
        std::move(extensions));
}

}
}