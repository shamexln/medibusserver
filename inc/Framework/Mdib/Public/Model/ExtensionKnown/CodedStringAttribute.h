#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{
namespace Ext
{

/**
 * @brief A key value pair to include string attributes of the IEEE 11073 classic domain information model not available in the BICEPS Participant Model
 * @details Typically will be used as an identifier specific to a hospital (non-manufacturer) that is configured by (service) personnel.
 *
 * Synonyms used by different companies:
 *  - equipment label
 *  - device name
 *  - friendly name
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CodedStringAttribute
{

public:
    /**
     * @brief Constructor with all members.
     */
    explicit CodedStringAttribute(const CodedValue& mdcAttribute, Locale::Utf8 value);

    /**
     * @brief A coded value for specifying the attribute type
     * @details Note: only code, coding system and symbolicCodeName will be used in mdcAttribute when mapped to extensions.
     * See SdpiExtensions.h for details
     */
    const CodedValue& mdcAttribute() const;

    /**
     * @brief Data contained in the coded attribute
     */
    const Locale::Utf8& value() const;


private:
    CodedValue m_mdcAttribute;
    Locale::Utf8 m_value;
};

/**
 * @brief Sequence of \ref CodedStringAttribute.
 * @ingroup Mdib
 */
using CodedStringAttributes = std::vector<CodedStringAttribute>;

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const CodedStringAttribute& lhs,
                                const CodedStringAttribute& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const CodedStringAttribute& lhs,
                                const CodedStringAttribute& rhs) noexcept;

}
}
}
