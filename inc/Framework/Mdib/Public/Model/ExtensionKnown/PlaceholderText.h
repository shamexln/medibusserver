#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/Placeholder.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>

namespace DFL::Mdib::Ext
{
/**
 * @brief
 * Used by an SDC SERVICE PROVIDER to communicate texts in which placeholder tokens which are replaced by specific values.
 *
 * @details
 * Allows for fewer translations when different texts are needed for a labeled parameter. 
 * Also allows for richer alarm text to be shown to the user ("HR > 80 vs "HR HIGH"")
 *
 * Example usage in code:
 * @snippet Mdib/Test/UnitTest/TestPlaceholderTextExtension.cpp PlaceholderTextUsage
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP PlaceholderText
{
public:
    /**
     * @brief Full Constructor
     */
    PlaceholderText(DFL::Mdib::LocalizedTexts texts, DFL::Mdib::Ext::Placeholders placeholders);

    /**
     * @brief Localized texts or text references containing placeholder tokens. 
     * @details Placeholder tokens are markers that are enclosed by dollar characters ($). Example: $LIMIT$. 
     *          Placeholder Tokens are there to be replaced with placeholder values. 
     *          Multiple texts allowed for multiple languages.
     */
    const DFL::Mdib::LocalizedTexts& texts() const noexcept;

    /**
     * @brief List of placeholder values for replacing placeholder tokens in Text
     */
    const Placeholders& placeholders() const noexcept;


private:
    DFL::Mdib::LocalizedTexts m_texts;
    Placeholders m_placeholders;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const PlaceholderText& lhs,
                                const PlaceholderText& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const PlaceholderText& lhs,
                                const PlaceholderText& rhs) noexcept;

}
