#pragma once

#include <S31/Localization/Public/Common/NumberOfLines.h>

#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Mdib/Public/Model/LocalizedTextWidth.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Utils/Public/LanguageTag.h>

#include <boost/optional/optional.hpp>

#include <set>
#include <string>
#include <vector>

namespace S31::Localization
{

/**
 * @brief Parameter of BICEPS GetLocalizedText.
 *
 * @ingroup S31LocalizationCommon
 */
class LocalizedTextFilter
{
    public:
        template<class T>
        using Container = std::set<T>;

        template<class T>
        using Iterator = typename Container<T>::const_iterator;

        LocalizedTextFilter():
            m_references{},
            m_version{},
            m_languages{},
            m_textWidths{},
            m_numberOfLines{}
        {}

        /// @brief Full Constructor
        template<typename T_References, typename T_Version, typename T_Languages, typename T_TextWidths, typename T_NumberOfLines>
        LocalizedTextFilter(T_References&& refs, T_Version&& version, T_Languages&& langs, T_TextWidths&& textWidths, T_NumberOfLines&& numberOfLines) :
            m_references{std::forward<T_References>(refs)},
            m_version{std::forward<T_Version>(version)},
            m_languages{std::forward<T_Languages>(langs)},
            m_textWidths{std::forward<T_TextWidths>(textWidths)},
            m_numberOfLines{std::forward<T_NumberOfLines>(numberOfLines)}
        {}

        /// @brief Zero or more reference names of the texts that are requested.
        const Container<DFL::Mdib::LocalizedTextRef>& references() const
        {
            return m_references;
        }

        /// @brief Revision of the referenced text that is requested.
        const boost::optional<DFL::Mdib::VersionCounter>& version() const
        {
            return m_version;
        }

        /// @brief Zero or more language identifiers.
        const Container<DFL::Locale::LanguageTag>& languages() const
        {
            return m_languages;
        }

        /// @brief Zero or more pm:LocalizedTextWidth identifiers to filter for different text widths.
        const Container<DFL::Mdib::LocalizedTextWidth>& textWidths() const
        {
            return m_textWidths;
        }

        /// @brief Zero or more numbers to filter for number of lines.
        const Container<NumberOfLines>& numberOfLines() const
        {
            return m_numberOfLines;
        }

        friend bool operator==(const LocalizedTextFilter& lhs, const LocalizedTextFilter& rhs)
        {
            return lhs.m_references == rhs.m_references
                    && lhs.m_version == rhs.m_version
                    && lhs.m_languages == rhs.m_languages
                    && lhs.m_textWidths == rhs.m_textWidths
                    && lhs.m_numberOfLines == rhs.m_numberOfLines;
        }

        friend bool operator!=(const LocalizedTextFilter& lhs, const LocalizedTextFilter& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        Container<DFL::Mdib::LocalizedTextRef> m_references;
        boost::optional<DFL::Mdib::VersionCounter> m_version;
        Container<DFL::Locale::LanguageTag> m_languages;
        Container<DFL::Mdib::LocalizedTextWidth> m_textWidths;
        Container<NumberOfLines> m_numberOfLines;
};

using LocalizedTextFilters = std::vector<LocalizedTextFilter>;

}
