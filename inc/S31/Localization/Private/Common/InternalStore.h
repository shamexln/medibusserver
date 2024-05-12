#pragma once

#include <S31/Localization/Public/Common/NumberOfLines.h>

#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Mdib/Public/Model/LocalizedTextWidth.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>

#include <map>
#include <vector>

namespace S31::Localization::Impl
{

/**
 * @brief Key that orders the entities in @ref StoreContainer.
 * @details The key elements correspond to the elements of @ref DFL::Mdib::LocalizedText (besides the actual text) plus number of lines.
 *
 * ### Order
 * The key defines an order as follows
 * - significance of key elements (more significant first): reference, language, version, text width, number of lines
 * - within key elements (except version): natural (lexicographical, numerical), note that language is case insensitive
 * - within version: reversed (higher version comes first). This is an optimization to access the latest version.
 * - text width is optional, here holds: @e none comes before any other value
 *
 * @ingroup S31LocalizationCommon
 */
class LocalizedTextStoreKey
{
    public:
        template<typename T_Reference, typename T_Language, typename T_Version, typename T_TextWidth, typename T_NumberOfLines>
        LocalizedTextStoreKey(T_Reference&& ref, T_Language&& lang, T_Version&& version, T_TextWidth&& textWidth, T_NumberOfLines&& numberOfLines):
            m_reference(std::forward<T_Reference>(ref)),
            m_language(std::forward<T_Language>(lang)),
            m_version(std::forward<T_Version>(version)),
            m_textWidth(std::forward<T_TextWidth>(textWidth)),
            m_numberOfLines(std::forward<T_NumberOfLines>(numberOfLines))
        {}

        template<typename T_Reference, typename T_Language, typename T_Version, typename T_TextWidth>
        LocalizedTextStoreKey(T_Reference&& ref, T_Language&& lang, T_Version&& version, T_TextWidth&& textWidth):
            m_reference(std::forward<T_Reference>(ref)),
            m_language(std::forward<T_Language>(lang)),
            m_version(std::forward<T_Version>(version)),
            m_textWidth(std::forward<T_TextWidth>(textWidth)),
            m_numberOfLines(1)
        {}

        template<typename T_Reference, typename T_Language, typename T_Version>
        LocalizedTextStoreKey(T_Reference&& ref, T_Language&& lang, T_Version&& version):
            m_reference(std::forward<T_Reference>(ref)),
            m_language(std::forward<T_Language>(lang)),
            m_version(std::forward<T_Version>(version)),
            m_textWidth(),
            m_numberOfLines(1)
        {}

        const DFL::Mdib::LocalizedTextRef& reference() const
        {
            return m_reference;
        }

        const DFL::Locale::LanguageTag& language() const
        {
            return m_language;
        }

        const DFL::Mdib::VersionCounter& version() const
        {
            return m_version;
        }

        const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth() const
        {
            return m_textWidth;
        }

        const NumberOfLines& numberOfLines() const
        {
            return m_numberOfLines;
        }

        friend bool operator<(const LocalizedTextStoreKey& lhs, const LocalizedTextStoreKey& rhs)
        {
            if (lhs.reference() != rhs.reference())
            {
                return lhs.reference() < rhs.reference();
            }
            if (lhs.language() != rhs.language())
            {
                return lhs.language() < rhs.language();
            }
            if (lhs.version() != rhs.version())
            {
                // reverse order, to have the latest version first
                return lhs.version() > rhs.version();
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
            return lhs.numberOfLines() < rhs.numberOfLines();
        }

        friend bool operator==(const LocalizedTextStoreKey& lhs, const LocalizedTextStoreKey& rhs)
        {
            if (&lhs == &rhs)
            {
                return true;
            }
            return lhs.reference() == rhs.reference()
                    && lhs.language() == rhs.language()
                    && lhs.version() == rhs.version()
                    && lhs.textWidth() == rhs.textWidth()
                    && lhs.numberOfLines() == rhs.numberOfLines();
        }

        friend bool operator!=(const LocalizedTextStoreKey& lhs, const LocalizedTextStoreKey& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        DFL::Mdib::LocalizedTextRef m_reference;
        DFL::Locale::LanguageTag m_language;
        DFL::Mdib::VersionCounter m_version;
        boost::optional<DFL::Mdib::LocalizedTextWidth> m_textWidth;
        NumberOfLines m_numberOfLines = NumberOfLines(1);

};

/**
 * @brief Internal data structure in the @ref S31::Localization::Impl::LocalizedTextStore
 * @ingroup S31LocalizationCommon
 */
using StoreContainer = std::map<LocalizedTextStoreKey, DFL::Locale::Utf8>;

/**
 * @brief Iterator for the internal data structure in the @ref S31::Localization::Impl::LocalizedTextStore
 * @ingroup S31LocalizationCommon
 */
using StoreIterator = StoreContainer::const_iterator;

}
