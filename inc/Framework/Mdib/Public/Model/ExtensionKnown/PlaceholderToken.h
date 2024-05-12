#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

#include <string>

namespace DFL::Mdib::Ext
{

/**
 * @brief The token that signifies the marker in a LocalizedText
 **/
class DFL_MDIB_EXPIMP PlaceholderToken
{
public: 
    /**
     * @brief Constructor with token content
     * @details On construction, checks content with restriction pattern = ^[a-zA-Z0-9_]+$
     */
    PlaceholderToken(std::string token);

    /**
     * @brief Token text with verified characters
     */
    const std::string& text() const noexcept;

private:

    std::string m_token;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const PlaceholderToken& lhs,
                                const PlaceholderToken& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const PlaceholderToken& lhs,
                                const PlaceholderToken& rhs) noexcept;
}
