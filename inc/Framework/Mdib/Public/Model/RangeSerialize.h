#pragma once

#include <Framework/Mdib/Public/Model/Range.h>
#include <Framework/Mdib/Public/Model/DecimalSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Range)

BOOST_CLASS_VERSION(::DFL::Mdib::Range, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Range, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::Range& in, const unsigned int /*version*/)
{
    ar & make_nvp("Lower", in.lower());
    ar & make_nvp("Upper", in.upper());
    ar & make_nvp("StepWidth", in.stepWidth());
    ar & make_nvp("RelativeAccuracy", in.relativeAccuracy());
    ar & make_nvp("AbsoluteAccuracy", in.absoluteAccuracy());
    ar & make_nvp("Extensions", in.extensions());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::Range& out, const unsigned int /*version*/)
{
    boost::optional<::DFL::Mdib::Decimal> lower;
    ar & make_nvp("Lower", lower);

    boost::optional<::DFL::Mdib::Decimal> upper;
    ar & make_nvp("Upper", upper);

    boost::optional<::DFL::Mdib::Decimal> stepWidth;
    ar & make_nvp("StepWidth", stepWidth);

    boost::optional<::DFL::Mdib::Decimal> relativeAccuracy;
    ar & make_nvp("RelativeAccuracy", relativeAccuracy);

    boost::optional<::DFL::Mdib::Decimal> absoluteAccuracy;
    ar & make_nvp("AbsoluteAccuracy", absoluteAccuracy);

    ::DFL::Mdib::ExtensionTypes extensions;
    ar & make_nvp("Extensions", extensions);

    out = ::DFL::Mdib::Range(lower,
                             upper,
                             stepWidth,
                             relativeAccuracy,
                             absoluteAccuracy,
                             std::move(extensions));
}

}
}
