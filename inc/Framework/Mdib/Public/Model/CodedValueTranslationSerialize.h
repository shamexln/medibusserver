#pragma once

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <Framework/Mdib/Public/Model/CodedValueTranslation.h>
#include <Framework/Mdib/Public/Model/CodingSystemSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::CodedValueTranslation)

BOOST_CLASS_VERSION(::DFL::Mdib::CodedValueTranslation, 1)

BOOST_CLASS_TRACKING(::DFL::Mdib::CodedValueTranslation, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::CodedValueTranslation* /*in*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::CodedValueTranslation& in, const unsigned int /*version*/)
{
    const DFL::Mdib::CodingSystem& cs(in.codingSystem());
    ar & make_nvp("CodingSystem", cs);
    const std::string& code(in.code().get());
    ar & make_nvp("Code", code);
    ar & make_nvp("Extensions", in.extensions());
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::CodedValueTranslation* out, const unsigned int /*version*/)
{
    ::new(out)::DFL::Mdib::CodedValueTranslation(DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("dummy"))), DFL::Mdib::CodeId(DFL::Locale::Utf8("dummy")));
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::CodedValueTranslation& out, const unsigned int version)
{
    DFL::Mdib::CodingSystem cs(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("dummy")));
    ar & make_nvp("CodingSystem", cs);
    std::string code;
    ar & make_nvp("Code", code);

    DFL::Mdib::ExtensionTypes extensions;
    if (version > 0)
    {
        ar & make_nvp("Extensions", extensions);
    }

    out = DFL::Mdib::CodedValueTranslation(cs,
                                           DFL::Mdib::CodeId(DFL::Locale::Utf8(code)),
                                           std::move(extensions));
}

} /* namespace serialization */
} /* namespace boost */
