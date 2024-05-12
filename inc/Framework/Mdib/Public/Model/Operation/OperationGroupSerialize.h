#pragma once

#include <Framework/Mdib/Public/Model/Operation/OperationGroup.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Mdib/Public/Model/HandleSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::OperationGroup)

BOOST_CLASS_VERSION(::DFL::Mdib::OperationGroup, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::OperationGroup, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::OperationGroup& src, const unsigned int /*version*/)
{
    const auto& operatingMode = src.operatingMode();
    ar & make_nvp("OperatingMode", operatingMode);
    ar & make_nvp("Operations", src.operations());
    ar & make_nvp("Type", src.type());
    ar & make_nvp("Extensions", src.extensions());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::OperationGroup* dst, const unsigned int /*version*/)
{
    ::new(dst) ::DFL::Mdib::OperationGroup(
        ::DFL::Mdib::OperatingMode{},
        ::DFL::Mdib::Handles{},
        ::DFL::Mdib::CodedValue(
            ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
            ::DFL::Mdib::CodeId{}));
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template <class Archive>
void load(Archive& ar, ::DFL::Mdib::OperationGroup& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::OperatingMode operatingMode{};
    ar & make_nvp("OperatingMode", operatingMode);

    ::DFL::Mdib::Handles operations;
    ar & make_nvp("Operations", operations);

    ::DFL::Mdib::CodedValue type(
            ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
            ::DFL::Mdib::CodeId{});
    ar & make_nvp("Type", type);

    ::DFL::Mdib::ExtensionTypes extensions;
    ar & make_nvp("Extensions", extensions);

    dst = ::DFL::Mdib::OperationGroup(operatingMode,
                                      operations,
                                      type,
                                      std::move(extensions));
}

}
}
