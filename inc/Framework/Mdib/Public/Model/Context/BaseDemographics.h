#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Private/HasExtensionsMutable.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Definition of basic demographic information.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP BaseDemographics: public Impl::HasExtensions
{
public:
    explicit BaseDemographics(Locale::Utf8 givenName,
                     Locale::Utf8 middleName,
                     Locale::Utf8 familyName,
                     Locale::Utf8 birthName,
                     Locale::Utf8 title,
                     ExtensionTypes extensions = {});

    explicit BaseDemographics() = default;

    /**
     * @{
     * @name Patient name
     * @details Given name and family name are used here, since first name and
     * last name are not clearly defined. In some areas the family name comes
     * first (Hungary, parts of Africa and most East Asia).
     */
    /// @return given name of the patient
    Locale::Utf8 givenName() const;

    /// @return middle names (space separated) of the patient
    Locale::Utf8 middleName() const;

    /// @return family name of the patient
    Locale::Utf8 familyName() const;

    /// @return birth name of the patient
    Locale::Utf8 birthName() const;

    /// @return title of the patient
    Locale::Utf8 title() const;

    ///@}
private:
    Locale::Utf8 m_givenName;
    Locale::Utf8 m_middleName = {};
    Locale::Utf8 m_familyName = {};
    Locale::Utf8 m_birthName = {};
    Locale::Utf8 m_title = {};
};

/**
 * @brief Equal compare of \ref BaseDemographics.
 * @return \c true in case all value are equal.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool operator==(const BaseDemographics& lhs, const BaseDemographics& rhs);

/**
 * @brief Not equal compare of \ref BaseDemographics.
 * @return \c true if any value is different.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool operator!=(const BaseDemographics& lhs, const BaseDemographics& rhs);

} /* namespace Mdib */
} /* namespace DFL */
