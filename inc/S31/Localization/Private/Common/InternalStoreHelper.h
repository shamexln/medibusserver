#pragma once

#include <S31/Localization/Private/Common/InternalStore.h>
#include <S31/Localization/Public/Common/LocalizedText.h>
#include <S31/Localization/Public/Common/S31LtsExImp.h>
#include <S31/Localization/S31Only/Common/LocalizedTextFilter.h>

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Utils/Public/Utf8.h>

#include <set>

namespace S31::Localization::Impl
{

/**
 * @brief Returns the number of line breaks in the given Utf8.
 * @details Handles *Line Breaking Classes* that cause a line break according to *UNICODE LINE BREAKING ALGORITHM*,
 * see http://www.unicode.org/reports/tr14/tr14-43.html
 *
 * @ingroup S31LocalizationCommon
 */
S31_LTS_EXPIMP unsigned int numberOfLineBreaks(const DFL::Locale::Utf8& utf8);

/**
 * @brief Create a @ref DFL::Mdib::LocalizedText from the given store element.
 * @details Does not check whether the iterator is valid or not.
 * @ingroup S31LocalizationCommon
 */
DFL::Mdib::LocalizedText makeMdibText(const StoreIterator& it);

/**
 * @brief Create a @ref S31::Localization::LocalizedText from the given store element.
 * @details Does not check whether the iterator is valid or not.
 * @ingroup S31LocalizationCommon
 */
S31::Localization::LocalizedText makeS31Text(const StoreIterator& it);

/**
 * @brief Get the texts that match the filter in a store.
 * @details This implements the lookup needed for the SDC GetLocalizedText() request.
 *
 * ### Additional/dissenting lookup rules to the matching rules described in the standard
 *
 * The content with respect to 'text width' and 'number of lines' of a @ref LocalizedTextFilter is matched as follows:
 * - if @ref LocalizedTextFilter::textWidths() and @ref LocalizedTextFilter::numberOfLines() contain at most 1 element each,
 *   then all text elements match that match both of these filter elements (all that is less or equal)
 * - if @ref LocalizedTextFilter::textWidths() or @ref LocalizedTextFilter::numberOfLines() contain more than 1 element,
 *   then all text elements match
 * - With respect to 'text width' only: a text without textWidth matches always.
 *
 * @ingroup S31LocalizationCommon
 */
class LocalizedTextFilterMatcher
{
    public:
        LocalizedTextFilterMatcher(const StoreContainer& store, const LocalizedTextFilter& filter):
            m_store(store),
            m_filter(filter)
        {}

        /**
         * @brief Get the matching texts.
         */
        DFL::Mdib::LocalizedTexts match() const;
    private:
        const StoreContainer& m_store;
        const LocalizedTextFilter& m_filter;
};

/**
 * @brief Adds a text to the store.
 * @details If a text with the same key is already in the store, then the text is not added.
 * @ingroup S31LocalizationCommon
 */
template<typename Text>
void addToStore(StoreContainer& store, Text&& localizedText)
{
    static_assert(std::is_same<typename std::remove_reference<Text>::type, DFL::Mdib::LocalizedText>::value,
            "addToStore() can be used only with DFL::Mdib::LocalizedText");

    const auto& reference = localizedText.reference();
    const auto& language = localizedText.languageTag();
    const auto& version = localizedText.version();
    const auto& textWidth = localizedText.textWidth();
    const auto numberOfLines = NumberOfLines(numberOfLineBreaks(localizedText.text()) + 1);

    if (reference.get().empty() || !language || !version)
    {
        return;
    }

    const LocalizedTextStoreKey k(reference, *language, *version, textWidth, numberOfLines);
    // text is invariant by definition - requirement: The module shall ignore added texts when provided texts already exist
    if (store.find(k) == store.end())
    {
        store[k] = std::forward<Text>(localizedText).text();
    }
}

inline DFL::Mdib::LocalizedText makeMdibText(const StoreIterator& it)
{
    return {it->second, it->first.language(), it->first.reference(), it->first.version(), it->first.textWidth()};
}

inline S31::Localization::LocalizedText makeS31Text(const StoreIterator& it)
{
    return {it->second,
            it->first.language(),
            it->first.reference(),
            it->first.version(),
            it->first.textWidth(),
            it->first.numberOfLines()};
}
}
