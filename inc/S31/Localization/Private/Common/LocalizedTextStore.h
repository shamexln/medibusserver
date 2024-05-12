#pragma once

#include <S31/Localization/Private/Common/InternalStore.h>
#include <S31/Localization/Private/Common/InternalStoreHelper.h>
#include <S31/Localization/Public/Common/LocalizedText.h>
#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Localization/Public/Common/S31LtsExImp.h>
#include <S31/Localization/S31Only/Common/LocalizedTextFilter.h>

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>

#include <boost/optional/optional.hpp>

#include <map>
#include <string>
#include <vector>

namespace S31::Localization::Impl
{

/**
 * @brief Storage for localized texts.
 * @details For usage on client and device side. Not thread safe.
 * @ingroup S31LocalizationCommon
 */
class S31_LTS_EXPIMP LocalizedTextStore
{
    public:
        /**
         * @brief Adds a text to the store.
         */
        template<typename Text>
        void add(Text&& localizedText);

        /**
         * @brief Get a text by @ref LocalizedTextReference, 'best fitting text'.
         * @details Follows the comparison rule of BICEPS GetLocalizedText.
         *
         * This lookup is intended to be used by the user/product on client side.
         *
         * ### Detection rules
         * - reference, version, and language have to match
         *
         * #### No Number of Lines given
         * - if text width is given: the element with the matching text width matches, if no such element exist, then the
         *   the element with the next smaller text width matches, otherwise the element with no text width matches
         * - if there are multiple elements that match for one category, then the element with the lowest number of lines matches
         *
         * #### Number of Lines given
         * - the matching element is detected among all elements (candidates) that have lower or equal text witdh and number of lines
         * - an element with no text width is considered as lower than any given text width
         * - if no text width is given then any text width is taken into consideration
         * - among the candidates the matching element is selected: it is maximal with respect to number of lines, and secondary with
         *   respect to text width
         *
         * @return The text, empty if no match is in the store.
         */
        LocalizedText text(const LocalizedTextReference& reference, const DFL::Locale::LanguageTag& language) const;

        /**
         * @brief Get all texts of the given reference, maybe restricted by the given version.
         * @brief Currently restriction by language is not needed, all languages will ne returned.
         * @param reference Reference of the texts
         * @param version if given, only texts of the given version are returned
         */
        Localization::LocalizedTexts texts(
                        const DFL::Mdib::LocalizedTextRef& reference,
                        const boost::optional<DFL::Mdib::VersionCounter>& version) const;

        /**
         * @brief Returns the texts, which match the filter.
         * @details This lookup is intended to be used on device side by S31 to process a GetLocalizedText request.
         * @param filter This represents the parameter of a BICEPS GetLocalizedText request.
         */
        DFL::Mdib::LocalizedTexts texts(const LocalizedTextFilter& filter) const;

        /**
         * @brief Clears the store.
         */
        void clear();

        /**
         * @brief Checks the consistency of the store.
         * @details This is especially important for the device side (the filling of the store has to obey the following).
         *
         * It is expected from the device that if a text is given with a certain version and reference in one language that then the localized
         * text store has to contain that version and reference in any other language too.
         *
         * This follows from BICEPS implicitly because if a text referenced in a certain version in the Mdib then it has to be
         * retrievable from the LOCALIZATION SERVICE in any available language.
         *
         * Derived classes call this function every time texts are added (in the device side store, on client side the store has only
         * one language).
         *
         * If the store is inconsistent an exception is thrown.
         */
        void checkConsistency() const;

    private:

        Impl::StoreIterator textIt(const LocalizedTextReference& reference, const DFL::Locale::LanguageTag& language) const;

        Impl::StoreIterator textItByTextWidth(const LocalizedTextReference& reference, const DFL::Locale::LanguageTag& language) const;

        /**
         * @brief More complicated lookup with textWidth and numberOfLines
         * @details This is considered a special case, that means that using a numberOfLines > 1 in a lookup is rare.
         */
        Impl::StoreIterator textItByTextWidthAndNumberOfLines(const LocalizedTextReference& reference, const DFL::Locale::LanguageTag& language) const;

        Impl::StoreContainer m_data;
};

template<typename Text>
void LocalizedTextStore::add(Text&& localizedText)
{
    addToStore(m_data, std::forward<Text>(localizedText));
}


}
