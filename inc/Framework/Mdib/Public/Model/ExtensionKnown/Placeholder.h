#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

#include <Framework/Mdib/Public/Model/ExtensionKnown/DecimalWithFractionalDigits.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/PlaceholderToken.h>

#include <optional>
#include <string>
#include <vector>

namespace DFL::Mdib::Ext
{

/**
 * @brief A value for replacing placeholder tokens in a Text in a \@PlaceholderText
 * @details A placeholder must contain wither a placeholder Text or a placeholder Number
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP Placeholder
{
public:
    /**
     * @brief Constructor with Text content
     */
    Placeholder(PlaceholderToken token, std::string text);

    /**
     * @brief Constructor with Number content
     */
    Placeholder(PlaceholderToken token, DecimalWithFractionalDigits number);

    /**
     * @brief The token that signifies the marker in a localized text
     */
    const PlaceholderToken& token() const noexcept;

    /**
     * @brief A string text placeholder
     * @return Either the string text or boost::none if the placeholder is represented by a numeric value instead
     */
    const std::optional<std::string>& text() const noexcept;

    /**
     * @brief Numeric value of a placeholder with an optional precision
     * @return Either the numeric value or boost::none if the placeholder is represented by a text string instead
     */
    const std::optional<DecimalWithFractionalDigits>& number() const noexcept;

private:

    PlaceholderToken m_token;
    std::optional<std::string> m_text;
    std::optional<DecimalWithFractionalDigits> m_number;
};

using Placeholders = std::vector<Placeholder>;

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const Placeholder& lhs,
                                const Placeholder& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const Placeholder& lhs,
                                const Placeholder& rhs) noexcept;
}
