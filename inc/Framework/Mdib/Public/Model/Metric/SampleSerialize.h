#pragma once

#include <Framework/Mdib/Public/Model/Metric/Sample.h>
#include <Framework/Mdib/Public/Model/DecimalSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/AnnotationSerialize.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Sample)

BOOST_CLASS_VERSION(::DFL::Mdib::Sample, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Sample, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::Sample& src, const unsigned int /*version*/)
{
    const auto& value = src.value();
    ar & make_nvp("Value", value);
    ar & make_nvp("Annotations", src.annotations());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::Sample* dst, const unsigned int /*version*/)
{
    ::new(dst) ::DFL::Mdib::Sample{::DFL::Mdib::Decimal{}};
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::Sample& dst, const unsigned int /*version*/)
{
    DFL::Mdib::Decimal value;
    ar & make_nvp("Value", value);

    DFL::Mdib::Annotations annotations;
    ar & make_nvp("Annotations", annotations);

    dst = ::DFL::Mdib::Sample{value, std::move(annotations)};
}

}
}
