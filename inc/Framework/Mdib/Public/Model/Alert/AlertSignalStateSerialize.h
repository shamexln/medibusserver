/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Alert/AlertSignalState.h>
#include <Framework/Chrono/Public/DurationSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/vector.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::AlertSignalState)

BOOST_CLASS_VERSION(::DFL::Mdib::AlertSignalState, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::AlertSignalState, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::AlertSignalState& src, const unsigned int /*fileVersion*/)
{
    const auto& activationState = src.activationState();
    ar & make_nvp("ActivationState", activationState);

    const auto& actualSignalGenerationDelay = src.actualSignalGenerationDelay();
    ar & make_nvp("ActualSignalGenerationDelay", actualSignalGenerationDelay);

    const auto& presence = src.presence();
    ar & make_nvp("Presence", presence);

    const auto& location = src.location();
    ar & make_nvp("Location", location);

    const auto& slot = src.slot();
    ar & make_nvp("Slot", slot);

    const auto& extensions = src.extensions();
    ar & make_nvp("Extensions", extensions);
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& ar, ::DFL::Mdib::AlertSignalState* dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::AlertActivation activationState{};
    ar & make_nvp("ActivationState", activationState);

    boost::optional<::DFL::Mdib::Duration> actualSignalGenerationDelay{};
    ar & make_nvp("ActualSignalGenerationDelay", actualSignalGenerationDelay);

    ::DFL::Mdib::AlertSignalPresence presence{};
    ar & make_nvp("Presence", presence);

    ::DFL::Mdib::AlertSignalPrimaryLocation location{};
    ar & make_nvp("Location", location);

    boost::optional<::DFL::Mdib::Slot> slot{};
    ar & make_nvp("Slot", slot);

    ::DFL::Mdib::ExtensionTypes extensions{};
    ar & make_nvp("Extensions", extensions);

    ::new(dst) ::DFL::Mdib::AlertSignalState(
        activationState,
        actualSignalGenerationDelay,
        presence,
        location,
        slot,
        std::move(extensions));
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& /*ar*/, ::DFL::Mdib::AlertSignalState& /*dst*/, const unsigned int /*version*/)
{
}

}
}
