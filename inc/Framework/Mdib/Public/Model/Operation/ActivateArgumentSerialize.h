#pragma once

#include <Framework/Mdib/Public/Model/Operation/ActivateArgument.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::ActivateArgument)

BOOST_CLASS_VERSION(::DFL::Mdib::ActivateArgument, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::ActivateArgument, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::ActivateArgument& in, const unsigned int /*version*/)
{
    ar & make_nvp("Name", in.name());

    const auto& dataType = in.dataType();
    ar & make_nvp("DataType", dataType);
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::ActivateArgument* dst, const unsigned int /*version*/)
{
    ::new(dst) ::DFL::Mdib::ActivateArgument(
        ::DFL::Mdib::CodedValue(
            ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
            ::DFL::Mdib::CodeId{}),
        ::DFL::Mdib::XsdSimpleType{});
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template <class Archive>
void load(Archive& ar, ::DFL::Mdib::ActivateArgument& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::CodedValue name(
        ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
        ::DFL::Mdib::CodeId{});
    ar & make_nvp("Name", name);

    ::DFL::Mdib::XsdSimpleType dataType{};
    ar & make_nvp("DataType", dataType);

    dst = ::DFL::Mdib::ActivateArgument{name, dataType};
}

}
}
