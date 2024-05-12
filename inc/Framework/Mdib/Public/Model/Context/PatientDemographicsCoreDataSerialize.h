#pragma once

#include <Framework/Chrono/Public/TimeOfDaySerialize.h>
#include <Framework/Chrono/Public/YearMonthDaySerialize.h>
#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/Context/DateOfBirthSerialize.h>
#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreData.h>
#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreDataBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PersonReferenceSerialize.h>
#include <Framework/Mdib/Public/Model/DecimalSerialize.h>
#include <Framework/Mdib/Public/Model/MeasurementSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <Framework/Utils/Public/Utf8Serialize.h>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <Framework/Utils/Public/SerializationHelper.h>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::PatientDemographicsCoreData)

BOOST_CLASS_VERSION(::DFL::Mdib::PatientDemographicsCoreData, 1)

BOOST_CLASS_TRACKING(::DFL::Mdib::PatientDemographicsCoreData, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::PatientDemographicsCoreData& patient, const unsigned int /*version*/)
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
    DFL::Serialization::saveNvpOptional(ar, "Race", patient.race());

    const DFL::Mdib::PatientType patientType(patient.patientType());
    ar & make_nvp("PatientType", patientType);
    const DFL::Mdib::Sex sex(patient.sex());
    ar & make_nvp("Sex", sex);

    DFL::Serialization::saveNvpOptional(ar, "DateOfBirth", patient.dateOfBirth());
    DFL::Serialization::saveNvpOptional(ar, "Height", patient.height());
    DFL::Serialization::saveNvpOptional(ar, "Weight", patient.weight());

    // neonatal
    DFL::Serialization::saveNvpOptional(ar, "GestationalAge", patient.gestationalAge());
    DFL::Serialization::saveNvpOptional(ar, "BirthLength", patient.birthLength());
    DFL::Serialization::saveNvpOptional(ar, "BirthWeight", patient.birthWeight());
    DFL::Serialization::saveNvpOptional(ar, "HeadCircumference", patient.headCircumference());
    DFL::Serialization::saveNvpOptional(ar, "Mother", patient.mother());

    ar & make_nvp("Extensions", patient.extensions());
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::PatientDemographicsCoreData& patient, const unsigned int version)
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
    boost::optional<DFL::Mdib::CodedValue> race;
    DFL::Serialization::loadNvpOptional(ar, "Race", race);

    DFL::Mdib::PatientType patientType{};
    ar & make_nvp("PatientType", patientType);
    DFL::Mdib::Sex sex{};
    ar & make_nvp("Sex", sex);

    boost::optional<DFL::Mdib::DateOfBirth> dateOfBirth;
    DFL::Serialization::loadNvpOptional(ar, "DateOfBirth", dateOfBirth);
    boost::optional<DFL::Mdib::Measurement> height;
    DFL::Serialization::loadNvpOptional(ar, "Height", height);
    boost::optional<DFL::Mdib::Measurement> weight;
    DFL::Serialization::loadNvpOptional(ar, "Weight", weight);

    // neonatal
    boost::optional<DFL::Mdib::Measurement> gestationalAge;
    DFL::Serialization::loadNvpOptional(ar, "GestationalAge", gestationalAge);
    boost::optional<DFL::Mdib::Measurement> birthLength;
    DFL::Serialization::loadNvpOptional(ar, "BirthLength", birthLength);
    boost::optional<DFL::Mdib::Measurement> birthWeight;
    DFL::Serialization::loadNvpOptional(ar, "BirthWeight", birthWeight);
    boost::optional<DFL::Mdib::Measurement> headCircumference;
    DFL::Serialization::loadNvpOptional(ar, "HeadCircumference", headCircumference);
    boost::optional<DFL::Mdib::PersonReference> mother;
    DFL::Serialization::loadNvpOptional(ar, "Mother", mother);

    DFL::Mdib::ExtensionTypes extensions;
    if (version > 0)
    {
        ar & make_nvp("Extensions", extensions);
    }

    DFL::Mdib::PatientDemographicsCoreDataBuilder builder(patient);

    builder.givenName(DFL::Locale::Utf8(givenName));
    builder.middleName(DFL::Locale::Utf8(middleName));
    builder.familyName(DFL::Locale::Utf8(familyName));
    builder.birthName(DFL::Locale::Utf8(birthName));
    builder.title(DFL::Locale::Utf8(title));
    builder.race(race);

    builder.sex(sex);
    builder.patientType(patientType);

    builder.dateOfBirth(dateOfBirth);

    builder.height(height);
    builder.weight(weight);

    builder.gestationalAge(gestationalAge);
    builder.birthLength(birthLength);
    builder.birthWeight(birthWeight);
    builder.headCircumference(headCircumference);
    builder.mother(mother);

    builder.extensions(std::move(extensions));
    patient = builder.build();
}
}
}
