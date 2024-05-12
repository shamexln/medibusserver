#pragma once

#include <Framework/Mdib/Public/Model/Metric/Annotation.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Annotation)

BOOST_CLASS_VERSION(::DFL::Mdib::Annotation, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Annotation, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::Annotation& src, const unsigned int /*version*/)
{
    ar & make_nvp("CodedValue", static_cast<const ::DFL::Mdib::CodedValue&>(src));
    ar & make_nvp("AnnotationExtensions", src.annotationExtensions());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::Annotation* dst, const unsigned int /*version*/)
{
    ::new(dst) ::DFL::Mdib::Annotation(
        ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
        ::DFL::Mdib::CodeId{});
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::Annotation& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::CodedValue codedValue(
        ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
        ::DFL::Mdib::CodeId{});
    ar & make_nvp("CodedValue", codedValue);

    ::DFL::Mdib::ExtensionTypes annotationExtensions;
    ar & make_nvp("AnnotationExtensions", annotationExtensions);

    dst = ::DFL::Mdib::Annotation(codedValue, std::move(annotationExtensions));
}

}
}
