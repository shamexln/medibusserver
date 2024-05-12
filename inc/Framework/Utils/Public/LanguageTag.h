#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Config/Public/Attributes.h>
#include <string>

namespace DFL
{
namespace Locale
{

/**
 * @brief A wrapper around language tags as in RFC&nbsp;5646 [Tags for Identifying Languages](http://tools.ietf.org/html/rfc5646).
 *
 * @details
 * This is a simplified representation of language tags that provides:
 * - storage of the tag (get/set)
 * - get the language represented in the tag (i.e. a ISO&nbsp;639 code)
 *
 * Currently there is no specific support for other language tag features like 'regions' or 'scripts'. This class is just a
 * storage, no validity checks are done on the language tag. But the class can check whether the tag is of the form
 * ll-CC (language-country).
 *
 * Examples of language tags (more in RFC&nbsp;5646 - Appendix A):
 * - de: German (simple Language subtag)
 * - zh-Hant: Chinese written using the Traditional Chinese script (Language subtag plus Script subtag)
 * - en-US: English as used in the United States (Language-Region)
 * - zh-cmn-Hans-CN: (Chinese, Mandarin, Simplified script, as used in China)
 * - sr-Latn-RS
 * - es-419
 * - invalid tags example: de-419-DE (no check is done, here allowed)
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP LanguageTag
{
    public:
        LanguageTag();

        /**
         * @brief Constructs a new language tag
         * @param tag The language tag
         */
        explicit LanguageTag(const std::string &tag);

        /**
         * @brief Returns the stored language tag
         * @return the tag
         */
        const std::string& tag() const;

        /**
         * @brief Returns the language contained in the language tag.
         * @details
         * Results consists of a ISO&nbsp;639 code (2 or 3 letters) and optional extlang parts.
         * This is detected according the grammar described in RFC&nbsp;5646. No checks is done whether
         * the language is a valid ISO&nbsp;639 code or not.
         *
         * e.g.:
         * - de &rarr; de
         * - en-GB &rarr; en
         * - zh-cmn-Hans-CN &rarr; zh-cmn
         *
         * @return the tag if valid (according grammar), empty if invalid or no language defined in the language tag.
         */
        std::string language() const;

        /**
         * @brief Checks whether the language tag is about the given language or not.
         * @details This works case insensitive.
         * @param language eg.: "en" (same result with "EN"); "" will always return @e false
         * @return true if given language matches. (eg. in "en-GB")
         */
        bool isLanguage(const std::string &language) const;

        /**
         * @brief Checks whether the tag has the form 'll-CC' (\<language\>-\<country\>).
         * @details
         * The language part is checked against the 2-letter codes from  ISO 639-1.
         * The country part is checked against the ALPHA-2 codes from ISO 3166-1.
         * Other language tag parts art not allowed.
         *
         * e.g.:
         * - allowed: 'en-US'
         * - not allowed: 'en', 'en-409', 'en-us-x-somethingextra'
         *
         * @return true if the language tag is of the desired form.
         */
        bool is2LetterLangAnd2LetterCountry() const;

        /**
         * @name Comparison operators
         * @details Perform lexicographic comparison (case insensitive)
         */
        ///@{
        friend bool operator==(const LanguageTag& lhs, const LanguageTag& rhs);
        friend bool operator!=(const LanguageTag& lhs, const LanguageTag& rhs);
        friend bool operator<(const LanguageTag& lhs, const LanguageTag& rhs);
        friend bool operator>(const LanguageTag& lhs, const LanguageTag& rhs);
        friend bool operator<=(const LanguageTag& lhs, const LanguageTag& rhs);
        friend bool operator>=(const LanguageTag& lhs, const LanguageTag& rhs);
        ///@}

    private:
        std::string m_tag;
        std::string m_tag_as_lower;
};

inline const std::string& LanguageTag::tag() const
{
    return m_tag;
}

/// @brief Operator == for @ref LanguageTag
inline bool operator==(const LanguageTag& lhs, const LanguageTag& rhs)
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.m_tag_as_lower == rhs.m_tag_as_lower;
}

/// @brief Operator != for @ref LanguageTag
inline bool operator!=(const LanguageTag& lhs, const LanguageTag& rhs)
{
    return !(lhs == rhs);
}

/// @brief Operator <= for @ref LanguageTag
inline bool operator<(const LanguageTag& lhs, const LanguageTag& rhs)
{
    if (&lhs == &rhs)
    {
        return false;
    }
    return lhs.m_tag_as_lower < rhs.m_tag_as_lower;
}

/// @brief Operator > for @ref LanguageTag
inline bool operator>(const LanguageTag& lhs, const LanguageTag& rhs)
{
    if (&lhs == &rhs)
    {
        return false;
    }
    return lhs.m_tag_as_lower > rhs.m_tag_as_lower;
}

/// @brief Operator <= for @ref LanguageTag
inline bool operator<=(const LanguageTag& lhs, const LanguageTag& rhs)
{
    return lhs == rhs || lhs < rhs;
}

/// @brief Operator >= for @ref LanguageTag
inline bool operator>=(const LanguageTag& lhs, const LanguageTag& rhs)
{
    return lhs == rhs || lhs > rhs;
}


}
}
