#pragma once

#include <Framework/Mdib/Public/Model/Component/CalibrationDocumentation.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationResultSerialize.h>
#include <Framework/Mdib/Public/Model/LocalizedTextSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::CalibrationDocumentation)

BOOST_CLASS_VERSION(::DFL::Mdib::CalibrationDocumentation, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::CalibrationDocumentation, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::CalibrationDocumentation& src, const unsigned int /*version*/)
{
    ar & make_nvp("LocalizedTexts", src.localizedTexts());
    ar & make_nvp("CalibrationResults", src.calibrationResults());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::CalibrationDocumentation& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::LocalizedTexts localizedTexts;
    ar & make_nvp("LocalizedTexts", localizedTexts);

    ::DFL::Mdib::CalibrationResults calibrationResults;
    ar & make_nvp("CalibrationResults", calibrationResults);

    dst = ::DFL::Mdib::CalibrationDocumentation{localizedTexts,
                                                calibrationResults};
}

}
}
