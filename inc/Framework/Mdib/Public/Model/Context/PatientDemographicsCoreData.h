#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <boost/optional.hpp>
#include <utility>
#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Mdib/Public/Model/Context/BaseDemographics.h>
#include <Framework/Mdib/Public/Model/Context/DateOfBirth.h>
#include <Framework/Mdib/Public/Model/Context/PatientType.h>
#include <Framework/Mdib/Public/Model/Context/PersonReference.h>
#include <Framework/Mdib/Public/Model/Context/Sex.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Measurement.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Contains the essential (core) demographics of the patient.
 * @details This BICEPS model contains the core information derived from the
 * Patient Demographics object in ISO/IEEE 11073-10201:2004 (section&nbsp;7.10.1)
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP PatientDemographicsCoreData : public BaseDemographics
{
    public:

        /**
         * @brief Default constructor.
         * @details By default, names are set to empty strings, optional member are empty, and enum member are set to unspecified.
         */
        PatientDemographicsCoreData(
            Locale::Utf8 givenName,
            Locale::Utf8 middleName,
            Locale::Utf8 familyName,
            Locale::Utf8 birthName,
            Locale::Utf8 title,
            Sex sex,
            PatientType patientType,
            const boost::optional<DateOfBirth>& dateOfBirth,        //NOLINT(modernize-pass-by-value)
            const boost::optional<Measurement>& height,             //NOLINT(modernize-pass-by-value)
            const boost::optional<Measurement>& weight,             //NOLINT(modernize-pass-by-value)
            const boost::optional<CodedValue>& race,                //NOLINT(modernize-pass-by-value)
            const boost::optional<Measurement>& gestationalAge,     //NOLINT(modernize-pass-by-value)
            const boost::optional<Measurement>& birthLength,        //NOLINT(modernize-pass-by-value)
            const boost::optional<Measurement>& birthWeight,        //NOLINT(modernize-pass-by-value)
            const boost::optional<Measurement>& headCircumference,  //NOLINT(modernize-pass-by-value)
            const boost::optional<PersonReference>& mother,         //NOLINT(modernize-pass-by-value)
            ExtensionTypes extensions)
            : BaseDemographics(std::move(givenName),
                               std::move(middleName),
                               std::move(familyName),
                               std::move(birthName),
                               std::move(title),
                               extensions)
            , m_sex(sex)
            , m_patientType(patientType)
            , m_dateOfBirth(dateOfBirth)
            , m_height(height)
            , m_weight(weight)
            , m_race(race)
            , m_gestationalAge(gestationalAge)
            , m_birthLength(birthLength)
            , m_birthWeight(birthWeight)
            , m_headCircumference(headCircumference)
            , m_mother(mother){};

        PatientDemographicsCoreData() = default;

        /// @return sex of the patient
        Sex sex() const;

        /// @return type (category) of the patient
        PatientType patientType() const;

        /**
         * @{
         * @name Patient date of birth
         * @details Patient date of birth is typically tracked as a local date
         * (optionally with time). Thus a date (without time) and a date with
         * time information will be supported.
         */
        boost::optional<DateOfBirth> dateOfBirth() const;
        ///@}


        /**
         * @{
         * @name Patient height
         * @details Patient height shall have (according to IHE PCD TF Volume 2) a unit of cm (MDC_DIM_CENTI_M).
         *          In order to be compatible with the SDC standard, the height is also available as *any unit*.
         */

        /// @return patient height in cm
        boost::optional<Decimal> heightInCm() const;

        /// @return patient height in any unit
        boost::optional<DFL::Mdib::Measurement> height() const;

        ///@}

        /**
         * @{
         * @name Patient weight
         * @details Patient weight shall have (according to IHE PCD TF Volume 2) a unit of g or kg (MDC_DIM_X_G or MDC_DIM_KILO_G).
         *          In order to be compatible with the SDC standard, the weight is also available as *any unit*.
         */

        /// @return patient weight in kilogram
        boost::optional<Decimal> weightInKilogram() const;

        /// @return patient weight in any unit
        boost::optional<DFL::Mdib::Measurement> weight() const;

        ///@}


        /// @return race of the patient
        boost::optional<CodedValue> race() const;

        /**
         * @{
         * @name Gestational age.
         */
        const boost::optional<Measurement>& gestationalAge() const;
        ///@}

        /**
         * @{
         * @name Birth length.
         */
        const boost::optional<Measurement>& birthLength() const;
        ///@}

        /**
         * @{
         * @name Birth weight.
         */
        const boost::optional<Measurement>& birthWeight() const;
        ///@}

        /**
         * @{
         * @name Head circumference.
         */
        const boost::optional<Measurement>& headCircumference() const;
        ///@}

        /**
         * @{
         * @name Mother.
         */
        const boost::optional<PersonReference>& mother() const;
        ///@}

    private:
        Sex m_sex{Sex::Unspecified};
        PatientType m_patientType{PatientType::Unspecified};
        boost::optional<DateOfBirth> m_dateOfBirth{};
        boost::optional<Measurement> m_height{};
        boost::optional<Measurement> m_weight{};
        boost::optional<CodedValue> m_race{};

        // from pm:NeonatalPatientDemographicsCoreData
        boost::optional<Measurement> m_gestationalAge{};
        boost::optional<Measurement> m_birthLength{};
        boost::optional<Measurement> m_birthWeight{};
        boost::optional<Measurement> m_headCircumference{};
        boost::optional<PersonReference> m_mother{};
};

/**
 * @brief Equal operator for \ref PatientDemographicsCoreData.
 */
DFL_MDIB_EXPIMP bool operator ==(const PatientDemographicsCoreData& lhs, const PatientDemographicsCoreData& rhs);

/**
 * @brief Not-equal operator for \ref PatientDemographicsCoreData.
 */
DFL_MDIB_EXPIMP bool operator !=(const PatientDemographicsCoreData& lhs, const PatientDemographicsCoreData& rhs);

} /* namespace Mdib */
} /* namespace DFL */
