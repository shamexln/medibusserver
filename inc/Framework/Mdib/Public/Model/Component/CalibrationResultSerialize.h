#pragma once

#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationResult.h>
#include <Framework/Mdib/Public/Model/MeasurementSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::CalibrationResult)

BOOST_CLASS_VERSION(::DFL::Mdib::CalibrationResult, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::CalibrationResult, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::CalibrationResult& src, const unsigned int /*version*/)
{
    ar & make_nvp("Code", src.code());
    ar & make_nvp("Value", src.value());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::CalibrationResult* dst, const unsigned int /*version*/)
{
    ::new (dst)::DFL::Mdib::CalibrationResult(
        ::DFL::Mdib::CodedValue(
            ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
            ::DFL::Mdib::CodeId{}),
        ::DFL::Mdib::Measurement(
            ::DFL::Mdib::Decimal{},
            ::DFL::Mdib::Unit(
                ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
                ::DFL::Mdib::CodeId{})));
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::CalibrationResult& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::CodedValue code(
        ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
        ::DFL::Mdib::CodeId{});
    ar & make_nvp("Code", code);

    ::DFL::Mdib::Measurement value(
        ::DFL::Mdib::Decimal{},
        ::DFL::Mdib::Unit(
            ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
            ::DFL::Mdib::CodeId{}));
    ar & make_nvp("Value", value);

    dst = ::DFL::Mdib::CalibrationResult{code, value};
}

}
}
