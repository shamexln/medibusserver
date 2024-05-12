#pragma once

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Mdib/Public/Model/Context/BaseDemographics.h>
#include <Framework/Utils/Public/SerializationHelper.h>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::BaseDemographics)

BOOST_CLASS_VERSION(::DFL::Mdib::BaseDemographics, 1)

BOOST_CLASS_TRACKING(::DFL::Mdib::BaseDemographics, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::BaseDemographics& patient, const unsigned int /*version*/)
{
    const std::string& givenName(patient.givenName());
    ar & make_nvp("GivenName", givenName);
    const std::string& middleName(patient.middleName());
    ar & make_nvp("MiddleName", middleName);
    const std::string& familyName(patient.familyName());
    ar & make_nvp("FamilyName", familyName);
    const std::string& birthName(patient.birthName());
    ar & make_nvp("BirthName", birthName);
    const std::string& title(patient.title());
    ar & make_nvp("Title", title);
    ar & make_nvp("Extensions", patient.extensions());
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::BaseDemographics& patient, const unsigned int version)
{
    std::string givenName;
    ar & make_nvp("GivenName", givenName);
    std::string middleName;
    ar & make_nvp("MiddleName", middleName);
    std::string familyName;
    ar & make_nvp("FamilyName", familyName);
    std::string birthName;
    ar & make_nvp("BirthName", birthName);
    std::string title;
    ar & make_nvp("Title", title);

    DFL::Mdib::ExtensionTypes extensions;
    if (version > 0)
    {
        ar & make_nvp("Extensions", extensions);
    }

    patient = ::DFL::Mdib::BaseDemographics(
        DFL::Locale::Utf8(givenName),
        DFL::Locale::Utf8(middleName),
        DFL::Locale::Utf8(familyName),
        DFL::Locale::Utf8(birthName),
        DFL::Locale::Utf8(title),
        std::move(extensions));
}
}
}