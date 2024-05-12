#pragma once

#include <memory>
#include <Framework/Mdib/Public/Model/Context/BaseDemographics.h>
#include <boost/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Mdib/Public/Model/CodedValueSemantic.h>

#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreData.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Builder with fluent interface for @ref PatientDemographicsCoreData
 * @ingroup Mdib
 */
class PatientDemographicsCoreDataBuilder
{
    public:
        /// @brief Typedef to the immutable @ref PatientDemographicsCoreData
        using BuiltType = PatientDemographicsCoreData;

        /// @brief Builder based on given immutable @ref PatientDemographicsCoreData
        explicit PatientDemographicsCoreDataBuilder(const PatientDemographicsCoreData& patientDemographicsCoreData=PatientDemographicsCoreData());

        /// @brief Builder based on given immutable @ref PatientDemographicsCoreData
        explicit PatientDemographicsCoreDataBuilder(const DFL::NotNull<SharedPtr<PatientDemographicsCoreData>>& patientDemographicsCoreData);

        /// @brief Overwrite all values with given immutable @ref PatientDemographicsCoreData
        PatientDemographicsCoreDataBuilder& operator=(const PatientDemographicsCoreData& patientDemographicsCoreData);

        /// @brief Explicit conversion to immutable @ref PatientDemographicsCoreData
        PatientDemographicsCoreData build() const;

        /// @brief Test whether the builder differs from the immutable @ref PatientDemographicsCoreData
        bool isChanged(const PatientDemographicsCoreData& base) const;

        /// @brief Setter for givenName
        /// @{
        PatientDemographicsCoreDataBuilder& givenName(const DFL::Locale::Utf8& givenName);
        PatientDemographicsCoreDataBuilder& givenName(DFL::Locale::Utf8&& givenName);
        /// @}

        /// @brief Setter for middleName
        /// @{
        PatientDemographicsCoreDataBuilder& middleName(const DFL::Locale::Utf8& middleName);
        PatientDemographicsCoreDataBuilder& middleName(DFL::Locale::Utf8&& middleName);
        /// @}

        /// @brief Setter for familyName
        /// @{
        PatientDemographicsCoreDataBuilder& familyName(const DFL::Locale::Utf8& familyName);
        PatientDemographicsCoreDataBuilder& familyName(DFL::Locale::Utf8&& familyName);
        /// @}

        /// @brief Setter for birthName
        /// @{
        PatientDemographicsCoreDataBuilder& birthName(const DFL::Locale::Utf8& birthName);
        PatientDemographicsCoreDataBuilder& birthName(DFL::Locale::Utf8&& birthName);
        /// @}

        /// @brief Setter for title
        /// @{
        PatientDemographicsCoreDataBuilder& title(const DFL::Locale::Utf8& title);
        PatientDemographicsCoreDataBuilder& title(DFL::Locale::Utf8&& title);
        /// @}

        /// @brief Setter for sex
        /// @{
        PatientDemographicsCoreDataBuilder& sex(Sex sex);
        /// @}

        /// @brief Setter for patientType
        /// @{
        PatientDemographicsCoreDataBuilder& patientType(PatientType patientType);
        /// @}

        /// @brief Setter for dateOfBirth
        /// @{
        PatientDemographicsCoreDataBuilder& dateOfBirth(const boost::optional<DateOfBirth>& dateOfBirth);
        /// @}

        /// @brief Setter for height
        /// @{
        PatientDemographicsCoreDataBuilder& heightInCm(const boost::optional<Decimal>& newHeightInCm);
        PatientDemographicsCoreDataBuilder& height(const boost::optional<Measurement>& height);
        PatientDemographicsCoreDataBuilder& height(boost::optional<Measurement>&& height);
        /// @}

        /// @brief Setter for weight
        /// @{
        PatientDemographicsCoreDataBuilder& weightInKilogram(const boost::optional<Decimal>& newWeightInKg);
        PatientDemographicsCoreDataBuilder& weight(const boost::optional<Measurement>& weight);
        PatientDemographicsCoreDataBuilder& weight(boost::optional<Measurement>&& weight);
        /// @}

        /// @brief Setter for race
        /// @{
        PatientDemographicsCoreDataBuilder& race(const boost::optional<CodedValue>& race);
        PatientDemographicsCoreDataBuilder& race(boost::optional<CodedValue>&& race);
        /// @}

        /// @brief Setter for gestationalAge
        /// @{
        PatientDemographicsCoreDataBuilder& gestationalAge(const boost::optional<Measurement>& gestationalAge);
        PatientDemographicsCoreDataBuilder& gestationalAge(boost::optional<Measurement>&& gestationalAge);
        /// @}

        /// @brief Setter for birthLength
        /// @{
        PatientDemographicsCoreDataBuilder& birthLength(const boost::optional<Measurement>& birthLength);
        PatientDemographicsCoreDataBuilder& birthLength(boost::optional<Measurement>&& birthLength);
        /// @}

        /// @brief Setter for birthWeight
        /// @{
        PatientDemographicsCoreDataBuilder& birthWeight(const boost::optional<Measurement>& birthWeight);
        PatientDemographicsCoreDataBuilder& birthWeight(boost::optional<Measurement>&& birthWeight);
        /// @}

        /// @brief Setter for headCircumference
        /// @{
        PatientDemographicsCoreDataBuilder& headCircumference(const boost::optional<Measurement>& headCircumference);
        PatientDemographicsCoreDataBuilder& headCircumference(boost::optional<Measurement>&& headCircumference);
        /// @}

        /// @brief Setter for mother
        /// @{
        PatientDemographicsCoreDataBuilder& mother(const boost::optional<PersonReference>& mother);
        PatientDemographicsCoreDataBuilder& mother(boost::optional<PersonReference>&& mother);
        /// @}

        /// @brief Setter for extensions
        /// @{
        PatientDemographicsCoreDataBuilder& extensions(const ExtensionTypes& extensions);
        PatientDemographicsCoreDataBuilder& extensions(ExtensionTypes&& extensions);
        /// @}

        /// @brief Setter for BaseDemographics
        /// @{
        PatientDemographicsCoreDataBuilder& baseDemographics(const DFL::Mdib::BaseDemographics& bd);
        /// @}

        /// @brief Getter for givenName
        /// @{
        DFL::Locale::Utf8& givenName();
        DFL::Locale::Utf8 givenName() const;
        /// @}

        /// @brief Getter for middleName
        /// @{
        DFL::Locale::Utf8& middleName();
        DFL::Locale::Utf8 middleName() const;
        /// @}

        /// @brief Getter for familyName
        /// @{
        DFL::Locale::Utf8& familyName();
        DFL::Locale::Utf8 familyName() const;
        /// @}

        /// @brief Getter for birthName
        /// @{
        DFL::Locale::Utf8& birthName();
        DFL::Locale::Utf8 birthName() const;
        /// @}

        /// @brief Getter for title
        /// @{
        DFL::Locale::Utf8& title();
        DFL::Locale::Utf8 title() const;
        /// @}

        /// @brief Getter for sex
        /// @{
        Sex& sex();
        Sex sex() const;
        /// @}

        /// @brief Getter for patientType
        /// @{
        PatientType& patientType();
        PatientType patientType() const;
        /// @}

        /// @brief Getter for dateOfBirth
        /// @{
        boost::optional<DateOfBirth>& dateOfBirth();
        boost::optional<DateOfBirth> dateOfBirth() const;
        /// @}

        /// @brief Getter for height
        /// @{
        boost::optional<Measurement>& height();
        boost::optional<Measurement> height() const;
        boost::optional<Decimal> heightInCm() const;
        /// @}

        /// @brief Getter for weight
        /// @{
        boost::optional<Measurement>& weight();
        boost::optional<Measurement> weight() const;
        boost::optional<Decimal> weightInKilogram() const;
        /// @}

        /// @brief Getter for race
        /// @{
        boost::optional<CodedValue>& race();
        boost::optional<CodedValue> race() const;
        /// @}

        /// @brief Getter for gestationalAge
        /// @{
        boost::optional<Measurement>& gestationalAge();
        boost::optional<Measurement> gestationalAge() const;
        /// @}

        /// @brief Getter for birthLength
        /// @{
        boost::optional<Measurement>& birthLength();
        boost::optional<Measurement> birthLength() const;
        /// @}

        /// @brief Getter for birthWeight
        /// @{
        boost::optional<Measurement>& birthWeight();
        boost::optional<Measurement> birthWeight() const;
        /// @}

        /// @brief Getter for headCircumference
        /// @{
        boost::optional<Measurement>& headCircumference();
        boost::optional<Measurement> headCircumference() const;
        /// @}

        /// @brief Getter for mother
        /// @{
        boost::optional<PersonReference>& mother();
        boost::optional<PersonReference> mother() const;
        /// @}

        /// @brief Getter for extensions
        /// @{
        ExtensionTypes& extensions();
        const ExtensionTypes& extensions() const;
        /// @}

    private:
        DFL::Locale::Utf8 m_givenName;
        DFL::Locale::Utf8 m_middleName;
        DFL::Locale::Utf8 m_familyName;
        DFL::Locale::Utf8 m_birthName;
        DFL::Locale::Utf8 m_title;
        Sex m_sex;
        PatientType m_patientType;
        boost::optional<DateOfBirth> m_dateOfBirth;
        boost::optional<Measurement> m_height;
        boost::optional<Measurement> m_weight;
        boost::optional<CodedValue> m_race;
        boost::optional<Measurement> m_gestationalAge;
        boost::optional<Measurement> m_birthLength;
        boost::optional<Measurement> m_birthWeight;
        boost::optional<Measurement> m_headCircumference;
        boost::optional<PersonReference> m_mother;
        ExtensionTypes m_extensions;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator==(const PatientDemographicsCoreDataBuilder& lhs, const PatientDemographicsCoreDataBuilder& rhs);
DFL_MDIB_EXPIMP bool operator==(const PatientDemographicsCoreDataBuilder& lhs, const PatientDemographicsCoreData& rhs);
bool operator==(const PatientDemographicsCoreData& lhs, const PatientDemographicsCoreDataBuilder& rhs);
/// @}

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
/// @{
bool operator!=(const PatientDemographicsCoreDataBuilder& lhs, const PatientDemographicsCoreDataBuilder& rhs);
bool operator!=(const PatientDemographicsCoreData& lhs, const PatientDemographicsCoreDataBuilder& rhs);
bool operator!=(const PatientDemographicsCoreDataBuilder& lhs, const PatientDemographicsCoreData& rhs);
/// @}

/**
 * @brief Factory function to create %Builder based on given immutable @ref PatientDemographicsCoreData
 * @ingroup Mdib
 */
/// @{
PatientDemographicsCoreDataBuilder getBuilder(const PatientDemographicsCoreData& patientDemographicsCoreData);
PatientDemographicsCoreDataBuilder getBuilder(const DFL::NotNull<SharedPtr<PatientDemographicsCoreData>>& patientDemographicsCoreData);
/// @}

/**
 * @brief Helper function throws runtime_error in case of a not equal member
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP void assertEqual(const PatientDemographicsCoreData& lhs, const PatientDemographicsCoreData& rhs);

inline PatientDemographicsCoreDataBuilder::PatientDemographicsCoreDataBuilder(const PatientDemographicsCoreData& patientDemographicsCoreData) :
    m_givenName(patientDemographicsCoreData.givenName()),
    m_middleName(patientDemographicsCoreData.middleName()),
    m_familyName(patientDemographicsCoreData.familyName()),
    m_birthName(patientDemographicsCoreData.birthName()),
    m_title(patientDemographicsCoreData.title()),
    m_sex(patientDemographicsCoreData.sex()),
    m_patientType(patientDemographicsCoreData.patientType()),
    m_dateOfBirth(patientDemographicsCoreData.dateOfBirth()),
    m_height(patientDemographicsCoreData.height()),
    m_weight(patientDemographicsCoreData.weight()),
    m_race(patientDemographicsCoreData.race()),
    m_gestationalAge(patientDemographicsCoreData.gestationalAge()),
    m_birthLength(patientDemographicsCoreData.birthLength()),
    m_birthWeight(patientDemographicsCoreData.birthWeight()),
    m_headCircumference(patientDemographicsCoreData.headCircumference()),
    m_mother(patientDemographicsCoreData.mother()),
    m_extensions(patientDemographicsCoreData.extensions())
{
}

inline PatientDemographicsCoreDataBuilder::PatientDemographicsCoreDataBuilder(const DFL::NotNull<SharedPtr<PatientDemographicsCoreData>>& patientDemographicsCoreData) :
    m_givenName(patientDemographicsCoreData->givenName()),
    m_middleName(patientDemographicsCoreData->middleName()),
    m_familyName(patientDemographicsCoreData->familyName()),
    m_birthName(patientDemographicsCoreData->birthName()),
    m_title(patientDemographicsCoreData->title()),
    m_sex(patientDemographicsCoreData->sex()),
    m_patientType(patientDemographicsCoreData->patientType()),
    m_dateOfBirth(patientDemographicsCoreData->dateOfBirth()),
    m_height(patientDemographicsCoreData->height()),
    m_weight(patientDemographicsCoreData->weight()),
    m_race(patientDemographicsCoreData->race()),
    m_gestationalAge(patientDemographicsCoreData->gestationalAge()),
    m_birthLength(patientDemographicsCoreData->birthLength()),
    m_birthWeight(patientDemographicsCoreData->birthWeight()),
    m_headCircumference(patientDemographicsCoreData->headCircumference()),
    m_mother(patientDemographicsCoreData->mother()),
    m_extensions(patientDemographicsCoreData->extensions())
{
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::operator=(const PatientDemographicsCoreData& patientDemographicsCoreData)
{
    m_givenName = patientDemographicsCoreData.givenName();
    m_middleName = patientDemographicsCoreData.middleName();
    m_familyName = patientDemographicsCoreData.familyName();
    m_birthName = patientDemographicsCoreData.birthName();
    m_title = patientDemographicsCoreData.title();
    m_sex = patientDemographicsCoreData.sex();
    m_patientType = patientDemographicsCoreData.patientType();
    m_dateOfBirth = patientDemographicsCoreData.dateOfBirth();
    m_height = patientDemographicsCoreData.height();
    m_weight = patientDemographicsCoreData.weight();
    m_race = patientDemographicsCoreData.race();
    m_gestationalAge = patientDemographicsCoreData.gestationalAge();
    m_birthLength = patientDemographicsCoreData.birthLength();
    m_birthWeight = patientDemographicsCoreData.birthWeight();
    m_headCircumference = patientDemographicsCoreData.headCircumference();
    m_mother = patientDemographicsCoreData.mother();
    m_extensions = patientDemographicsCoreData.extensions();
    return *this;
}

inline PatientDemographicsCoreData PatientDemographicsCoreDataBuilder::build() const
{
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return PatientDemographicsCoreData(m_givenName, m_middleName, m_familyName, m_birthName, m_title, m_sex, m_patientType, m_dateOfBirth, m_height, m_weight, m_race, m_gestationalAge, m_birthLength, m_birthWeight, m_headCircumference, m_mother, m_extensions);
}

inline bool PatientDemographicsCoreDataBuilder::isChanged(const PatientDemographicsCoreData& base) const
{
    return build() != base;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::givenName(const DFL::Locale::Utf8& givenName)
{
    m_givenName = givenName;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::givenName(DFL::Locale::Utf8&& givenName)
{
    m_givenName = std::move(givenName);
    return *this;
}

inline DFL::Locale::Utf8& PatientDemographicsCoreDataBuilder::givenName()
{
    return m_givenName;
}

inline DFL::Locale::Utf8 PatientDemographicsCoreDataBuilder::givenName() const
{
    return m_givenName;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::middleName(const DFL::Locale::Utf8& middleName)
{
    m_middleName = middleName;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::middleName(DFL::Locale::Utf8&& middleName)
{
    m_middleName = std::move(middleName);
    return *this;
}

inline DFL::Locale::Utf8& PatientDemographicsCoreDataBuilder::middleName()
{
    return m_middleName;
}

inline DFL::Locale::Utf8 PatientDemographicsCoreDataBuilder::middleName() const
{
    return m_middleName;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::familyName(const DFL::Locale::Utf8& familyName)
{
    m_familyName = familyName;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::familyName(DFL::Locale::Utf8&& familyName)
{
    m_familyName = std::move(familyName);
    return *this;
}

inline DFL::Locale::Utf8& PatientDemographicsCoreDataBuilder::familyName()
{
    return m_familyName;
}

inline DFL::Locale::Utf8 PatientDemographicsCoreDataBuilder::familyName() const
{
    return m_familyName;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::birthName(const DFL::Locale::Utf8& birthName)
{
    m_birthName = birthName;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::birthName(DFL::Locale::Utf8&& birthName)
{
    m_birthName = std::move(birthName);
    return *this;
}

inline DFL::Locale::Utf8& PatientDemographicsCoreDataBuilder::birthName()
{
    return m_birthName;
}

inline DFL::Locale::Utf8 PatientDemographicsCoreDataBuilder::birthName() const
{
    return m_birthName;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::title(const DFL::Locale::Utf8& title)
{
    m_title = title;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::title(DFL::Locale::Utf8&& title)
{
    m_title = std::move(title);
    return *this;
}

inline DFL::Locale::Utf8& PatientDemographicsCoreDataBuilder::title()
{
    return m_title;
}

inline DFL::Locale::Utf8 PatientDemographicsCoreDataBuilder::title() const
{
    return m_title;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::baseDemographics(const DFL::Mdib::BaseDemographics& bd)
{
    m_givenName = bd.givenName();
    m_middleName = bd.middleName();
    m_familyName = bd.familyName();
    m_birthName = bd.birthName();
    m_title = bd.title();
    this->extensions(bd.extensions());
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::sex(Sex sex)
{
    m_sex = sex;
    return *this;
}

inline Sex& PatientDemographicsCoreDataBuilder::sex()
{
    return m_sex;
}

inline Sex PatientDemographicsCoreDataBuilder::sex() const
{
    return m_sex;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::patientType(PatientType patientType)
{
    m_patientType = patientType;
    return *this;
}

inline PatientType& PatientDemographicsCoreDataBuilder::patientType()
{
    return m_patientType;
}

inline PatientType PatientDemographicsCoreDataBuilder::patientType() const
{
    return m_patientType;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::dateOfBirth(const boost::optional<DateOfBirth>& dateOfBirth)
{
    m_dateOfBirth = dateOfBirth;
    return *this;
}

inline boost::optional<DateOfBirth>& PatientDemographicsCoreDataBuilder::dateOfBirth()
{
    return m_dateOfBirth;
}

inline boost::optional<DateOfBirth> PatientDemographicsCoreDataBuilder::dateOfBirth() const
{
    return m_dateOfBirth;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::heightInCm(const boost::optional<Decimal>& newHeightInCm)
{
    if(newHeightInCm)
    {
        m_height = DFL::Mdib::Measurement(*newHeightInCm, Unit::CENTI_M);
    }
    else
    {
        m_height = boost::none;
    }
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::height(boost::optional<Measurement>&& height)
{
    m_height = std::move(height);
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::height(const boost::optional<Measurement>& height)
{
    m_height = height;
    return *this;
}

inline boost::optional<Measurement>& PatientDemographicsCoreDataBuilder::height()
{
    return m_height;
}

inline boost::optional<Measurement> PatientDemographicsCoreDataBuilder::height() const
{
    return m_height;
}


inline boost::optional<Decimal> PatientDemographicsCoreDataBuilder::heightInCm() const
{
    if(m_height && DFL::Mdib::isSemanticallyEqual(m_height->unit(), Unit::CENTI_M))
    {
        return m_height->value();
    }
    return boost::none;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::weightInKilogram(const boost::optional<Decimal>& newWeightInKg)
{
    if(newWeightInKg)
    {
        m_weight = DFL::Mdib::Measurement(*newWeightInKg, Unit::KILO_G);
    }
    else
    {
        m_weight = boost::none;
    }
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::weight(boost::optional<Measurement>&& weight)
{
    m_weight = std::move(weight);
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::weight(const boost::optional<Measurement>& weight)
{
    m_weight = weight;
    return *this;
}

inline boost::optional<Measurement>& PatientDemographicsCoreDataBuilder::weight()
{
    return m_weight;
}

inline boost::optional<Measurement> PatientDemographicsCoreDataBuilder::weight() const
{
    return m_weight;
}

inline boost::optional<Decimal> PatientDemographicsCoreDataBuilder::weightInKilogram() const
{
    if(m_weight && DFL::Mdib::isSemanticallyEqual(m_weight->unit(), Unit::KILO_G))
    {
        return m_weight->value();
    }
    return boost::none;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::race(const boost::optional<CodedValue>& race)
{
    m_race = race;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::race(boost::optional<CodedValue>&& race)
{
    m_race = std::move(race);
    return *this;
}

inline boost::optional<CodedValue>& PatientDemographicsCoreDataBuilder::race()
{
    return m_race;
}

inline boost::optional<CodedValue> PatientDemographicsCoreDataBuilder::race() const
{
    return m_race;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::gestationalAge(const boost::optional<Measurement>& gestationalAge)
{
    m_gestationalAge = gestationalAge;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::gestationalAge(boost::optional<Measurement>&& gestationalAge)
{
    m_gestationalAge = std::move(gestationalAge);
    return *this;
}

inline boost::optional<Measurement>& PatientDemographicsCoreDataBuilder::gestationalAge()
{
    return m_gestationalAge;
}

inline boost::optional<Measurement> PatientDemographicsCoreDataBuilder::gestationalAge() const
{
    return m_gestationalAge;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::birthLength(const boost::optional<Measurement>& birthLength)
{
    m_birthLength = birthLength;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::birthLength(boost::optional<Measurement>&& birthLength)
{
    m_birthLength = std::move(birthLength);
    return *this;
}

inline boost::optional<Measurement>& PatientDemographicsCoreDataBuilder::birthLength()
{
    return m_birthLength;
}

inline boost::optional<Measurement> PatientDemographicsCoreDataBuilder::birthLength() const
{
    return m_birthLength;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::birthWeight(const boost::optional<Measurement>& birthWeight)
{
    m_birthWeight = birthWeight;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::birthWeight(boost::optional<Measurement>&& birthWeight)
{
    m_birthWeight = std::move(birthWeight);
    return *this;
}

inline boost::optional<Measurement>& PatientDemographicsCoreDataBuilder::birthWeight()
{
    return m_birthWeight;
}

inline boost::optional<Measurement> PatientDemographicsCoreDataBuilder::birthWeight() const
{
    return m_birthWeight;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::headCircumference(const boost::optional<Measurement>& headCircumference)
{
    m_headCircumference = headCircumference;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::headCircumference(boost::optional<Measurement>&& headCircumference)
{
    m_headCircumference = std::move(headCircumference);
    return *this;
}

inline boost::optional<Measurement>& PatientDemographicsCoreDataBuilder::headCircumference()
{
    return m_headCircumference;
}

inline boost::optional<Measurement> PatientDemographicsCoreDataBuilder::headCircumference() const
{
    return m_headCircumference;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::mother(const boost::optional<PersonReference>& mother)
{
    m_mother = mother;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::mother(boost::optional<PersonReference>&& mother)
{
    m_mother = std::move(mother);
    return *this;
}

inline boost::optional<PersonReference>& PatientDemographicsCoreDataBuilder::mother()
{
    return m_mother;
}

inline boost::optional<PersonReference> PatientDemographicsCoreDataBuilder::mother() const
{
    return m_mother;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::extensions(const ExtensionTypes& extensions)
{
    m_extensions = extensions;
    return *this;
}

inline PatientDemographicsCoreDataBuilder& PatientDemographicsCoreDataBuilder::extensions(ExtensionTypes&& extensions)
{
    m_extensions = std::move(extensions);
    return *this;
}

inline ExtensionTypes& PatientDemographicsCoreDataBuilder::extensions()
{
    return m_extensions;
}

inline const ExtensionTypes& PatientDemographicsCoreDataBuilder::extensions() const
{
    return m_extensions;
}

inline bool operator==(const PatientDemographicsCoreData& lhs, const PatientDemographicsCoreDataBuilder& rhs)
{
    return rhs == lhs;
}

inline bool operator!=(const PatientDemographicsCoreDataBuilder& lhs, const PatientDemographicsCoreDataBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const PatientDemographicsCoreData& lhs, const PatientDemographicsCoreDataBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const PatientDemographicsCoreDataBuilder& lhs, const PatientDemographicsCoreData& rhs)
{
    return !(lhs == rhs);
}

inline PatientDemographicsCoreDataBuilder getBuilder(const PatientDemographicsCoreData& patientDemographicsCoreData)
{
    return PatientDemographicsCoreDataBuilder(patientDemographicsCoreData);
}

inline PatientDemographicsCoreDataBuilder getBuilder(const DFL::NotNull<SharedPtr<PatientDemographicsCoreData>>& patientDemographicsCoreData)
{
    return PatientDemographicsCoreDataBuilder(patientDemographicsCoreData);
}

}
}
