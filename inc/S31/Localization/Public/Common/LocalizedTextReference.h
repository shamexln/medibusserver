#pragma once

#include <S31/Localization/Public/Common/NumberOfLines.h>

#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Mdib/Public/Model/LocalizedTextWidth.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>

#include <boost/optional/optional.hpp>
#include <set>

namespace S31::Localization
{

/**
 * @brief Identifies one specific text needed for one @ref DFL::Mdib::LocalizedText (without language)
 * @details To be used by product to express the interest in this specific text.
 * Note that this does not include the language because expectation is that the product has lot of these
 * references and wants them all in the same language.
 *
 * This class shall not be confused with @ref DFL::Mdib::LocalizedTextRef (member of @ref DFL::Mdib::LocalizedText)
 * which is just the identifier to the text regardless of language, version, width, and number of lines. In contrast,
 * elements of this class reference a text (or multiple texts) in a language and version and optional with restrictions
 * to text width and number of lines.
 *
 * @ingroup S31LocalizationCommon
 */
class LocalizedTextReference
{
    public:
        template<typename T_Reference, typename T_Version, typename T_TextWidth, typename T_NumberOfLines>
        LocalizedTextReference(T_Reference&& ref, T_Version&& version, T_TextWidth&& textWidth, T_NumberOfLines&& numberOfLines):
            m_reference{std::forward<T_Reference>(ref)},
            m_version{std::forward<T_Version>(version)},
            m_textWidth{std::forward<T_TextWidth>(textWidth)},
            m_numberOfLines{std::forward<T_NumberOfLines>(numberOfLines)}
        {}

        template<typename T_Reference, typename T_Version, typename T_TextWidth>
        LocalizedTextReference(T_Reference&& ref, T_Version&& version, T_TextWidth&& textWidth):
            m_reference{std::forward<T_Reference>(ref)},
            m_version{std::forward<T_Version>(version)},
            m_textWidth{std::forward<T_TextWidth>(textWidth)},
            m_numberOfLines{boost::none}
        {}

        template<typename T_Reference, typename T_Version>
        LocalizedTextReference(T_Reference&& ref, T_Version&& version):
            m_reference{std::forward<T_Reference>(ref)},
            m_version{std::forward<T_Version>(version)},
            m_textWidth{boost::none},
            m_numberOfLines{boost::none}
        {}

        /**
         * @brief Reference of the text.
         */
        const DFL::Mdib::LocalizedTextRef& reference() const
        {
            return m_reference;
        }

        /**
         * @brief Version of the text.
         */
        const DFL::Mdib::VersionCounter& version() const
        {
            return m_version;
        }

        /**
         * @brief Text width of the text.
         * @details Optional. Not set means that all/any width are desired. Otherwise this describes a maximum.
         */
        const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth() const
        {
            return m_textWidth;
        }

        /**
         * @brief Number of lines of the text.
         * @details Optional. Not set means that all/any values are desired. Otherwise this describes a maximum.
         */
        const boost::optional<NumberOfLines>& numberOfLines() const
        {
            return m_numberOfLines;
        }

        /**
         * @brief operator ==.
         */
        friend bool operator==(const LocalizedTextReference& lhs, const LocalizedTextReference& rhs)
        {
            if (&lhs == &rhs)
            {
                return true;
            }
            return lhs.reference() == rhs.reference()
                    && lhs.version() == rhs.version()
                    && lhs.textWidth() == rhs.textWidth()
                    && lhs.numberOfLines() == rhs.numberOfLines();
        }

        /**
         * @brief operator !=.
         */
        friend bool operator!=(const LocalizedTextReference& lhs, const LocalizedTextReference& rhs)
        {
            return !(lhs == rhs);
        }

        /**
         * @brief operator <
         * @details This operator is just needed to hold references in a map/set.
         */
        friend bool operator<(const LocalizedTextReference& lhs, const LocalizedTextReference& rhs)
        {
            if (lhs.reference() != rhs.reference())
            {
                return lhs.reference() < rhs.reference();
            }
            if (lhs.version() != rhs.version())
            {
                return lhs.version() < rhs.version();
            }
            if (!lhs.textWidth() && rhs.textWidth())
            {
                return true;
            }
            if (lhs.textWidth() && !rhs.textWidth())
            {
                return false;
            }
            if (lhs.textWidth() != rhs.textWidth())
            {
                return lhs.textWidth() < rhs.textWidth();
            }
            if (!lhs.numberOfLines() && rhs.numberOfLines())
            {
                return true;
            }
            if (lhs.numberOfLines() && !rhs.numberOfLines())
            {
                return false;
            }
            return lhs.numberOfLines() < rhs.numberOfLines();
        }

    private:
        DFL::Mdib::LocalizedTextRef m_reference;
        DFL::Mdib::VersionCounter m_version;
        boost::optional<DFL::Mdib::LocalizedTextWidth> m_textWidth;
        boost::optional<NumberOfLines> m_numberOfLines;
};

/**
 * @brief Is lhs more general than rhs?
 * @details
 *
 * ### Abbreviations in the docu/code
 * - tw - text witdth
 * - nol - Number of lines
 *
 * If reference or version differ then result is false.
 *
 * ### Remaining Cases
 * There are several different types of @ref LocalizedTextReference for this.
 * LocalizedTextReference with
 * 1. tw set and nol set
 * 2. tw set, nol not set
 * 3. tw not set, nol set
 * 4. tw not set, nol not set
 *
 * - 2 is more general than 1 (if the tw are equal)
 * - 3 is more general than 1 (if the nol are equal)
 * - 4 is more general than 1, 2, 3
 *
 * @return true if so, false if not or equal.
 */
inline bool isMoreGeneral(const LocalizedTextReference& lhs, const LocalizedTextReference& rhs)
{
    if (lhs.reference() != rhs.reference() || lhs.version() != rhs.version())
    {
        return false;
    }

    if (!lhs.numberOfLines() && !lhs.textWidth())
    {
        return rhs.numberOfLines() || rhs.textWidth();
    }

    if (lhs.numberOfLines() && lhs.textWidth())
    {
        return false;
    }

    if (!lhs.numberOfLines())
    {
        return rhs.numberOfLines() && lhs.textWidth() == rhs.textWidth();
    }

    return rhs.textWidth() && lhs.numberOfLines() == rhs.numberOfLines();
}

/**
 * @brief Identifies multiple specific texts (without language)
 * @ingroup S31LocalizationCommon
 */
using LocalizedTextReferences = std::set<LocalizedTextReference>;

}
