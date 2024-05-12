#pragma once

#include <Framework/Mdib/Public/Model/Component/Udi.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifierSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>
#include <Framework/Utils/Public/Utf8Serialize.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Udi)

BOOST_CLASS_VERSION(::DFL::Mdib::Udi, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Udi, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::Udi& src, const unsigned int /*version*/)
{
    ar & make_nvp("DeviceIdentifier", src.deviceIdentifier());
    ar & make_nvp("HumanReadableForm", src.humanReadableForm());
    ar & make_nvp("Issuer", src.issuer());
    ::DFL::Serialization::saveNvpOptional(ar, "Jurisdiction", src.jurisdiction());
    ar & make_nvp("Extensions", src.extensions());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::Udi* dst, const unsigned int /*version*/)
{
    ::new (dst)::DFL::Mdib::Udi(
        ::DFL::Mdib::DeviceIdentifier{},
        ::DFL::Mdib::HumanReadableForm{},
        ::DFL::Mdib::InstanceIdentifier{::DFL::Mdib::Root{DFL::Mdib::Uri{}}});
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::Udi& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::DeviceIdentifier deviceIdentifier;
    ar & make_nvp("DeviceIdentifier", deviceIdentifier);

    ::DFL::Mdib::HumanReadableForm humanReadableForm;
    ar & make_nvp("HumanReadableForm", humanReadableForm);

    ::DFL::Mdib::InstanceIdentifier issuer{::DFL::Mdib::Root{DFL::Mdib::Uri{}}};
    ar & make_nvp("Issuer", issuer);

    boost::optional<::DFL::Mdib::InstanceIdentifier> jurisdiction;
    ::DFL::Serialization::loadNvpOptional(ar, "Jurisdiction", jurisdiction);

    DFL::Mdib::ExtensionTypes extensions;
    ar & make_nvp("Extensions", extensions);

    dst = ::DFL::Mdib::Udi(deviceIdentifier,
                           humanReadableForm,
                           issuer,
                           jurisdiction,
                           std::move(extensions));
}

}
}
