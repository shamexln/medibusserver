#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/CodedValueTranslation.h>
#include <Framework/Mdib/Public/Model/CodedValueTranslationSerialize.h>
#include <Framework/Mdib/Public/Model/CodingSystemSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <boost/ptr_container/serialize_ptr_vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::CodedValue)

BOOST_CLASS_VERSION(::DFL::Mdib::CodedValue, 1)

BOOST_CLASS_TRACKING(::DFL::Mdib::CodedValue, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::CodedValue* /*in*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::CodedValue& in, const unsigned int /*version*/)
{
    const DFL::Mdib::CodingSystem& cs(in.codingSystem());
    ar & make_nvp("CodingSystem", cs);
    const std::string& code(in.code().get());
    ar & make_nvp("Code", code);
    const DFL::Mdib::LocalizedTexts& conceptDescription(in.conceptDescription());
    ar & make_nvp("ConceptDescription", conceptDescription);
    const std::string& symbolicCodeName(in.symbolicCodeName());
    ar & make_nvp("SymbolicName", symbolicCodeName);
    const DFL::Mdib::CodedValueTranslations& translations(in.translations());
    ar << make_nvp("Translations", translations);
    ar & make_nvp("Extensions", in.extensions());
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::CodedValue* out, const unsigned int /*version*/)
{
    ::new(out)::DFL::Mdib::CodedValue(DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("dummy"))), DFL::Mdib::CodeId(DFL::Locale::Utf8("dummy")));
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::CodedValue& out, const unsigned int version)
{
    DFL::Mdib::CodingSystem cs(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("dummy")));
    ar & make_nvp("CodingSystem", cs);
    std::string code;
    ar & make_nvp("Code", code);

    DFL::Mdib::LocalizedTexts conceptDescription;
    ar & make_nvp("ConceptDescription", conceptDescription);
    std::string symbolicName;
    ar & make_nvp("SymbolicName", symbolicName);
    DFL::Mdib::CodedValueTranslations translations;
    ar & make_nvp("Translations", translations);

    DFL::Mdib::ExtensionTypes extensions;
    if (version > 0)
    {
        ar & make_nvp("Extensions", extensions);
    }

    out = DFL::Mdib::CodedValue(cs,
                                DFL::Mdib::CodeId(DFL::Locale::Utf8(code)),
                                conceptDescription,
                                DFL::Locale::Utf8(symbolicName),
                                translations,
                                std::move(extensions));
}

} /* namespace serialization */
} /* namespace boost */
