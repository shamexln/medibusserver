#pragma once

#include <Framework/Mdib/Public/Model/Metric/Relation.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Mdib/Public/Model/HandleSerialize.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifierSerialize.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Relation)

BOOST_CLASS_VERSION(::DFL::Mdib::Relation, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Relation, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void save(Archive& ar, const ::DFL::Mdib::Relation& src, const unsigned int /*version*/)
{
    const auto& kind = src.kind();
    ar & make_nvp("Kind", kind);
    ar & make_nvp("Entries", src.entries());
    ::DFL::Serialization::saveNvpOptional(ar, "Code", src.code());
    ::DFL::Serialization::saveNvpOptional(ar, "Identification", src.identification());
    ar & make_nvp("Extensions", src.extensions());
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load_construct_data(Archive& /*ar*/, ::DFL::Mdib::Relation* dst, const unsigned int /*version*/)
{
    ::new(dst) ::DFL::Mdib::Relation(::DFL::Mdib::Kind{},
                                     ::DFL::Mdib::Handles{},
                                     boost::none,
                                     boost::none);
}

/**
 * @brief Support for Boost Serialization.
 * @ingroup Mdib
 */
template<class Archive>
void load(Archive& ar, ::DFL::Mdib::Relation& dst, const unsigned int /*version*/)
{
    DFL::Mdib::Kind kind{};
    ar & make_nvp("Kind", kind);

    DFL::Mdib::Handles entries;
    ar & make_nvp("Entries", entries);

    boost::optional<::DFL::Mdib::CodedValue> code;
    ::DFL::Serialization::loadNvpOptional(ar, "Code", code);

    boost::optional<::DFL::Mdib::InstanceIdentifier> identification;
    ::DFL::Serialization::loadNvpOptional(ar, "Identification", identification);

    DFL::Mdib::ExtensionTypes extensions;
    ar & make_nvp("Extensions", extensions);

    dst = ::DFL::Mdib::Relation(kind,
                                entries,
                                code,
                                identification,
                                std::move(extensions));
}

}
}
