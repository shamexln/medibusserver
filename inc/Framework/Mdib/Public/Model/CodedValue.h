#pragma once

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodingSystem.h>
#include <Framework/Mdib/Public/Model/CodedValueTranslation.h>
#include <Framework/Mdib/Public/Model/CodeId.h>
#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Code to identify the concept (semantic) of an object.
 * @details
 * Biceps:
 * > In general, in an interoperability format, objects,
 * > attributes, and methods are identified by nomenclature codes.
 * > CodedValue offers the ability to represent such nomenclature
 * > codes.
 *
 * The concept of a _Coded Value_ is also defined in HL7 FHIR.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CodedValue: public Impl::HasExtensions
{
    public:

        /**
         * @brief Constructs a code with all members.
         * @param codingSystem Coding system for the code.
         * @param code Code from coding system.
         * @param localizedConceptDescription Description of the concept behind the code.
         * For displaying purposes only.
         * @param symbolicCodeName Name of the codeId. (Some nomenclature define a symbolic name for there code.)
         * @param codedValueTranslations List of Translations of the coded value
         * @param extensions \ref DFL::Mdib::ExtensionType "Extensions" of any kind
         */
        CodedValue(CodingSystem codingSystem,
                   CodeId code,
                   LocalizedTexts localizedConceptDescription = {},
                   Locale::Utf8 symbolicCodeName = {},
                   CodedValueTranslations codedValueTranslations = {},
                   ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Provides the coding system.
         */
        const CodingSystem& codingSystem() const;

        /**
         * @brief Provides the code identifier.
         */
        const CodeId& code() const;

        /**
         * @name Concept description.
         * @brief The concept description is a human-readable description of the code.
         * @details Example for *MDC_EVT_LIMIT_AL_HI* would be: "A metric exceeds a given threshold".
         * @{
         */
        const LocalizedTexts& conceptDescription() const;
        ///@}

        /**
         * @name Symbolic code name.
         * @brief Optional symbolic name that may be defined for a code of a coding system.
         * @details Typically the symbolic code name is used as a constant name
         * for codes of a coding system.
         * For the ISO/IEEE 11073-10101:2004 standard MDC_DIM_PERCENT is the symbolic code name
         * for the percent unit (symbol %) and the CodeIdentifier 262688
         * @{
         */
        const Locale::Utf8& symbolicCodeName() const;
        ///@}

        /**
         * @anchor CodedValue_Translations
         * @name Translation
         * @brief Set of alternative or equivalent representations.
         *
         * @details It should be used to specify codes from different
         * coding systems with the same concept.
         *
         * BICEPS models translations through allowing coded values to contain other coded values (recursively).
         * Here recursion is not possible/allowed.
         */
        ///@{
        void clearTranslations();
        const CodedValueTranslations& translations() const;
        ///@}

        friend  bool operator==(const CodedValue& lhs, const CodedValue& rhs) noexcept;

    private:
        CodingSystem m_codingSystem;
        CodeId m_code;
        LocalizedTexts m_conceptDescription;
        Locale::Utf8 m_symbolicCodeName;
        CodedValueTranslations m_translations;
};

/**
 * @brief Equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare
 * @param rhs Instance to compare with
 * @return \c true in case all members equals.
 */
inline bool operator==(const CodedValue& lhs, const CodedValue& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }

    return lhs.m_code == rhs.m_code &&
           lhs.m_conceptDescription == rhs.m_conceptDescription &&
           lhs.m_symbolicCodeName == rhs.m_symbolicCodeName &&
           lhs.m_translations == rhs.m_translations &&
           lhs.m_codingSystem == rhs.m_codingSystem &&
           lhs.extensions() == rhs.extensions();
}

/**
 * @brief Not equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare
 * @param rhs Instance to compare with
 * @return \c true in case at least one member does not equal.
 */
inline bool operator!=(const CodedValue& lhs, const CodedValue& rhs) noexcept
{
    return !(lhs == rhs);
}

/**
 * @brief Sequence of \ref CodedValue "coded values".
 * @ingroup Mdib
 */
using CodedValues = std::vector<CodedValue>;


inline const CodingSystem& CodedValue::codingSystem() const
{
    return m_codingSystem;
}

inline const CodeId& CodedValue::code() const
{
    return m_code;
}

inline const LocalizedTexts& CodedValue::conceptDescription() const
{
    return m_conceptDescription;
}

inline const CodedValueTranslations& CodedValue::translations() const
{
    return m_translations;
}

}
}
