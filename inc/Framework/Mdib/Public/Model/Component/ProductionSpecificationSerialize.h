#pragma once

#include <Framework/Mdib/Public/Model/Component/ProductionSpecification.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifierSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>
#include <Framework/Utils/Public/Utf8Serialize.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::ProductionSpecification)

BOOST_CLASS_VERSION(::DFL::Mdib::ProductionSpecification, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::ProductionSpecification, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::ProductionSpecification& src, const unsigned int /*version*/)
{
    ar & make_nvp("SpecType", src.specType());
    ar & make_nvp("ProductionSpec", src.productionSpec());
    ::DFL::Serialization::saveNvpOptional(ar, "ComponentId", src.componentId());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::ProductionSpecification* dst, const unsigned int /*version*/)
{
    ::new (dst)::DFL::Mdib::ProductionSpecification(
        ::DFL::Mdib::CodedValue(
            ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
            ::DFL::Mdib::CodeId{}),
        ::DFL::Locale::Utf8{},
        boost::none);
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::ProductionSpecification& dst, const unsigned int /*version*/)
{
    ::DFL::Mdib::CodedValue specType(
        ::DFL::Mdib::CodingSystem{::DFL::Mdib::CodingSystemId{}},
        ::DFL::Mdib::CodeId{});
    ar & make_nvp("SpecType", specType);

    ::DFL::Locale::Utf8 productionSpec;
    ar & make_nvp("ProductionSpec", productionSpec);

    boost::optional<::DFL::Mdib::InstanceIdentifier> componentId;
    ::DFL::Serialization::loadNvpOptional(ar, "ComponentId", componentId);

    dst = ::DFL::Mdib::ProductionSpecification(std::move(specType),
                                               std::move(productionSpec),
                                               std::move(componentId));
}

}
}
