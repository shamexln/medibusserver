#pragma once

#include <S31/Localization/Public/Common/NumberOfLines.h>

#include <Framework/Mdib/Public/Model/LocalizedText.h>

#include <vector>

namespace S31::Localization
{

/**
 * @brief %LocalizedText with number of lines.
 * @details
 * Rationale: Mdib's @ref DFL::Mdib::LocalizedText follows BICEPS and doesn't models the 'number of lines' property
 * that OTOH is used within Localization Service.
 *
 * Users can lookup texts from the localized text store restricted to 'number of lines'. With this class the result
 * from this lookup has the actual 'number of lines' handy for the user.
 * @ingroup S31LocalizationCommon
 */
class LocalizedText: private DFL::Mdib::LocalizedText
{
    public:
        LocalizedText();

        LocalizedText(const DFL::Locale::Utf8& localizedText,
                      const boost::optional<DFL::Locale::LanguageTag>& langTag,
                      const DFL::Mdib::LocalizedTextRef& ref,
                      const boost::optional<DFL::Mdib::VersionCounter>& version,
                      const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth,
                      NumberOfLines numberOfLines);

        using DFL::Mdib::LocalizedText::text;
        using DFL::Mdib::LocalizedText::reference;
        using DFL::Mdib::LocalizedText::version;
        using DFL::Mdib::LocalizedText::textWidth;
        using DFL::Mdib::LocalizedText::languageTag;
        using DFL::Mdib::LocalizedText::empty;

        NumberOfLines numberOfLines() const;

        friend bool operator==(const LocalizedText& lhs, const LocalizedText& rhs);
    private:
        NumberOfLines m_numberOfLines;
};

/// @brief Container of @ref LocalizedText
/// @ingroup S31LocalizationCommon
using LocalizedTexts = std::vector<LocalizedText>;

inline LocalizedText::LocalizedText():
    DFL::Mdib::LocalizedText(DFL::Locale::Utf8("")),
    m_numberOfLines(NumberOfLines(1))
{
}

inline LocalizedText::LocalizedText(
        const DFL::Locale::Utf8& localizedText,
        const boost::optional<DFL::Locale::LanguageTag>& langTag,
        const DFL::Mdib::LocalizedTextRef& ref,
        const boost::optional<DFL::Mdib::VersionCounter>& version,
        const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth,
        NumberOfLines numberOfLines):
    DFL::Mdib::LocalizedText(localizedText, langTag, ref, version, textWidth),
    m_numberOfLines(numberOfLines)
{
}

inline NumberOfLines LocalizedText::numberOfLines() const
{
    return m_numberOfLines;
}

inline bool operator==(const LocalizedText& lhs, const LocalizedText& rhs)
{
    return static_cast<const DFL::Mdib::LocalizedText&>(lhs) == static_cast<const DFL::Mdib::LocalizedText&>(rhs) &&
            lhs.numberOfLines() == rhs.numberOfLines();
}

inline bool operator!=(const LocalizedText& lhs, const LocalizedText& rhs)
{
    return !(lhs == rhs);
}

}
