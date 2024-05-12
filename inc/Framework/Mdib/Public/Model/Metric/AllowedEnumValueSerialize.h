#pragma once

#include <Framework/Mdib/Public/Model/Metric/AllowedEnumValue.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifierSerialize.h>
#include <Framework/Mdib/Public/Model/MeasurementSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>
#include <Framework/Utils/Public/Utf8Serialize.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::AllowedEnumValue)

BOOST_CLASS_VERSION(::DFL::Mdib::AllowedEnumValue, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::AllowedEnumValue, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::AllowedEnumValue& src, const unsigned int /*version*/)
{
    ar & make_nvp("Value", src.value());
    ::DFL::Serialization::saveNvpOptional(ar, "Type", src.type());
    ::DFL::Serialization::saveNvpOptional(ar, "Identification", src.identification());
    ::DFL::Serialization::saveNvpOptional(ar, "Characteristic", src.characteristic());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::AllowedEnumValue* dst, const unsigned int /*version*/)
{
    ::new(dst) ::DFL::Mdib::AllowedEnumValue{::DFL::Locale::Utf8{}};
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::AllowedEnumValue& dst, const unsigned int /*version*/)
{
    ::DFL::Locale::Utf8 value;
    ar & make_nvp("Value", value);

    boost::optional<::DFL::Mdib::CodedValue> type;
    ::DFL::Serialization::loadNvpOptional(ar, "Type", type);

    boost::optional<::DFL::Mdib::InstanceIdentifier> identification;
    ::DFL::Serialization::loadNvpOptional(ar, "Identification", identification);

    boost::optional<::DFL::Mdib::Measurement> characteristic;
    ::DFL::Serialization::loadNvpOptional(ar, "Characteristic", characteristic);

    dst = ::DFL::Mdib::AllowedEnumValue{value,
                                        type,
                                        identification,
                                        characteristic};
}

}
}
