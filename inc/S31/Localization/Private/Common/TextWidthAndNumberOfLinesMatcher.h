#pragma once

#include <S31/Localization/Private/Common/InternalStore.h>
#include <S31/Localization/S31Only/Common/LocalizedTextFilter.h>

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>

#include <algorithm>
#include <vector>

namespace S31::Localization::Impl
{

/**
 * @brief Do the given iterators match in respect to reference/language/version?
 * @ingroup S31LocalizationCommon
 */
bool sameReferenceLanguageVersion(const StoreIterator& lhs, const StoreIterator& rhs, const StoreIterator& end);

/**
 * @brief Used to get the matching elements for a GetLocalizedText request.
 * @details This filters the matching elements within a range of texts of the same reference, language and version.
 *
 * ### Abbreviations in the code
 * tw - text witdth
 * nol - Number of lines
 *
 * ### Internal cases
 * | Case   | Filter                                                      |
 * |--------|-------------------------------------------------------------|
 * | 0      | TextWidth and NumberOfLines are empty                       |
 * | 1      | Al least one TextWidth, NumberOfLines is empty              |
 * | 2      | TextWidth is empty, at least one NumberOfLines              |
 * | 3      | TextWidth not empty, NumberOfLines not empty                |
 *
 * #### Performance considerations
 * The lookup algorithm has to cover all general/possibles cases. Most general is the following: For a certain reference, language,
 * and version there are texts in the store for multiple TWs and for each TW there are multiple texts with different NOL. These
 * have to be matched against an arbitrary filter (multiple TWs, multiple NOLs).
 *
 * For the store: in real life we can assume that for a certain reference, language, and version there are only few texts
 * with different TWs, probably for many cases there is only one text. Different NOLs are considered rare.
 *
 * For filters from requests we assume
 * - case 2 is rare
 * - the general case 3 is rare, the special case - one TW and one NOL - may occur often.
 *
 * @ingroup S31LocalizationCommon
 */
class TextWidthAndNumberOfLinesMatcher
{
    public:
        TextWidthAndNumberOfLinesMatcher(StoreIterator begin, StoreIterator end, const LocalizedTextFilter& filter):
            m_storeBegin(begin),
            m_storeEnd(end),
            m_filter(filter)
        {
        }

        class MatchResult
        {
            public:
                DFL::Mdib::LocalizedTexts texts;
                StoreIterator next;
        };

        /**
         * @brief Returns the matching texts and an iterator that is behind the matching elements.
         *
         * @details The returned @e next is somewhere behind the given start iterator. It may be even equal to
         * the start iterator. It is to be used by the caller which herself maybe iterates over the store and
         * allows her to continue the own iteration at this @e next point to avoid double evaluation of elements.
         * No special guarantees are given about the @e next iterator (e.g. maybe have same reference/language/version
         * as the start iterator or not).
         */
        MatchResult match() const
        {
            if (m_storeBegin == m_storeEnd)
            {
                return MatchResult{DFL::Mdib::LocalizedTexts(), m_storeEnd};
            }

            if (m_filter.textWidths().empty() && m_filter.numberOfLines().empty())
            {
                return matchCase0();
            }
            if (!m_filter.textWidths().empty() && m_filter.numberOfLines().empty())
            {
                return matchCase1();
            }
            if (m_filter.textWidths().empty() && !m_filter.numberOfLines().empty())
            {
                return matchCase2();
            }
            return matchCase3();
        }

    private:
        using StoreIterators = std::vector<StoreIterator>;
        using StoreIteratorsIterator = StoreIterators::const_iterator;

        /// We assume all iterators have same reference, language, version.
        /// See operator<() in @ref LocalizedTextStoreKey for comparison.
        struct StoreIteratorComparatorByNumberOfLines
        {
            bool operator()(const StoreIterator& lhs, const StoreIterator& rhs) const
            {
                const auto& lKey = lhs->first;
                const auto& rKey = rhs->first;
                if (lKey.numberOfLines() != rKey.numberOfLines())
                {
                    return lKey.numberOfLines() < rKey.numberOfLines();
                }
                if (!lKey.textWidth() && rKey.textWidth())
                {
                    return true;
                }
                if (lKey.textWidth() && !rKey.textWidth())
                {
                    return false;
                }
                return lKey.textWidth() < rKey.textWidth();
            }
        } m_compareForNolSort;

        class allForReferenceLanguageVersionResult
        {
            public:
                StoreIterators iters;
                StoreIterator next;
        };

        allForReferenceLanguageVersionResult allForReferenceLanguageVersion() const
        {
            allForReferenceLanguageVersionResult result;
            auto itStore = m_storeBegin;
            while (itStore != m_storeEnd
                   && sameReferenceLanguageVersion(m_storeBegin, itStore, m_storeEnd))
            {
                result.iters.push_back(itStore);
                ++itStore;
            }
            result.next = itStore;
            return result;
        }

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        void copy(DFL::Mdib::LocalizedTexts& texts, const StoreIterator& rangeBegin, const StoreIterator& rangeEnd) const
        {
            if (rangeBegin == m_storeEnd)
            {
                return;
            }
            for (auto it = rangeBegin; it != rangeEnd; ++it)
            {
                texts.push_back(makeMdibText(it));
            }
        }

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        static void copy(DFL::Mdib::LocalizedTexts& texts, const StoreIteratorsIterator& rangeBegin, const StoreIteratorsIterator& rangeEnd, const StoreIteratorsIterator& end)
        {
            if (rangeBegin == end)
            {
                return;
            }
            for (auto it = rangeBegin; it != rangeEnd; ++it)
            {
                texts.push_back(makeMdibText(*it));
            }
        }

        void moveToNextTextWidth(StoreIterator& it) const
        {
            const auto tw = it->first.textWidth();
            while (true)
            {
                ++it;
                if (!sameReferenceLanguageVersion(m_storeBegin, it, m_storeEnd) || tw != it->first.textWidth())
                {
                    return;
                }
            }
        }

        MatchResult matchCase0() const
        {
            MatchResult result;
            auto it = m_storeBegin;
            while (it != m_storeEnd && sameReferenceLanguageVersion(m_storeBegin, it, m_storeEnd))
            {
                result.texts.push_back(makeMdibText(it));
                ++it;
            }
            result.next = it;
            return result;
        }

        MatchResult matchCase1() const
        {
            const auto twEnd = m_filter.textWidths().cend();
            auto itStore = m_storeBegin;
            auto itFilter = m_filter.textWidths().begin();
            // candidates form a range, it contains texts of a certain TW with different NOLs.
            auto itCandidateBegin = m_storeEnd;
            MatchResult result;
            while (itStore != m_storeEnd
                   && sameReferenceLanguageVersion(m_storeBegin, itStore, m_storeEnd)
                   && itFilter != twEnd)
            {
                const auto& key = itStore->first;
                const auto& filterTw = *itFilter;

                // explicitly skip texts without tw
                if (!key.textWidth())
                {
                    ++itStore;
                    continue;
                }

                const auto& keyTw = *key.textWidth();

                if (keyTw <= filterTw)
                {
                    if (itCandidateBegin == m_storeEnd)
                    {
                        // beginning of a first group of candidates for this filter tw
                        itCandidateBegin = itStore;
                    }
                    if (itCandidateBegin != m_storeEnd &&
                            itCandidateBegin->first.textWidth() < keyTw)
                    {
                        // that's the beginning of a better group of candidates
                        itCandidateBegin = itStore;
                    }
                }
                else
                {
                    copy(result.texts, itCandidateBegin, itStore);
                    itCandidateBegin = m_storeEnd;
                    ++itFilter;
                    continue;
                }

                ++itStore;
            }

            copy(result.texts, itCandidateBegin, itStore); // itStore here either is end() or 1st element of next block (new reference, new lang, ..)
            result.next = itStore;
            return result;
        }

        MatchResult matchCase2() const
        {
            auto reSorted = allForReferenceLanguageVersion();
            auto begin = reSorted.iters.begin();
            auto end = reSorted.iters.end();
            std::sort(begin, end, m_compareForNolSort);

            const auto nolEnd = m_filter.numberOfLines().cend();
            auto itStore = begin;
            auto itFilter = m_filter.numberOfLines().begin();
            // candidates form a range, it contains texts of a certain NOL with different TWs.
            auto itCandidateBegin = end;
            MatchResult result;
            result.next = reSorted.next;
            while (itStore != end
                   && itFilter != nolEnd)
            {
                const auto& key = (*itStore)->first;
                const auto& filterNol = *itFilter;
                const auto& keyNol = key.numberOfLines();

                if (keyNol <= filterNol)
                {
                    if (itCandidateBegin == end)
                    {
                        // beginning of a first group of candidates for this filter nol
                        itCandidateBegin = itStore;
                    }
                    if (itCandidateBegin != end &&
                            (*itCandidateBegin)->first.numberOfLines() < keyNol)
                    {
                        // that's the beginning of a better group of candidates
                        itCandidateBegin = itStore;
                    }
                }
                else
                {
                    copy(result.texts, itCandidateBegin, itStore, end);
                    itCandidateBegin = end;
                    ++itFilter;
                    continue;
                }

                ++itStore;
            }

            copy(result.texts, itCandidateBegin, end, end);
            return result;
        }

        MatchResult matchCase3() const
        {
            MatchResult result;
            result.next = m_storeEnd;
            auto it = m_storeBegin;

            // skip texts without tw
            while (it != m_storeEnd
                   && sameReferenceLanguageVersion(m_storeBegin, it, m_storeEnd)
                   && !(it->first.textWidth()))
            {
                ++it;
            }

            if (!sameReferenceLanguageVersion(m_storeBegin, it, m_storeEnd))
            {
                // there are only texts without tw in the store, hence no match possible
                result.next = it;
                return result;
            }

            // generally, we have to go over every combination of the given tws and nols
            for (auto itFilterTw = m_filter.textWidths().begin(); itFilterTw != m_filter.textWidths().end(); ++itFilterTw)
            {
                if (it == m_storeEnd)
                {
                    break;
                }

                // find the range of potential matches for the current filterTw
                auto itTwRangeBegin = m_storeEnd;
                while (it != m_storeEnd
                       && sameReferenceLanguageVersion(m_storeBegin, it, m_storeEnd)
                       && *itFilterTw >= *(it->first.textWidth()))
                {
                    itTwRangeBegin = it;
                    moveToNextTextWidth(it);
                }

                if (itTwRangeBegin == m_storeEnd)
                {
                    // there is no match for this filterTw, or texts that would be match are already in the result set
                    continue;
                }

                const auto& itTwRangeEnd = it;
                auto itTwRange = itTwRangeBegin;
                auto itCandidate = itTwRangeEnd;
                auto itFilterNol = m_filter.numberOfLines().begin();
                const auto nolEnd = m_filter.numberOfLines().cend();
                // we already have here the range of one tw (from store) that whould match the current filter tw
                // now finding in this range the elements that match against the nols
                while (itTwRange != itTwRangeEnd
                       && itFilterNol != nolEnd)
                {
                    const auto& filterNol = *itFilterNol;
                    const auto& keyNol = itTwRange->first.numberOfLines();

                    if (keyNol <= filterNol)
                    {
                        if (itCandidate == itTwRangeEnd)
                        {
                            // first time here, we have a candidate
                            itCandidate = itTwRange;
                        }

                        if (itCandidate != itTwRangeEnd &&
                                itCandidate->first.numberOfLines() < keyNol)
                        {
                            // we have a better candidate
                            itCandidate = itTwRange;
                        }
                    }
                    else
                    {
                        if (itCandidate != itTwRangeEnd)
                        {
                            copy(result.texts, itCandidate, itTwRange); // this is exactly 1 element
                        }
                        itCandidate = itTwRangeEnd;
                        ++itFilterNol;
                        continue;
                    }

                    ++itTwRange;
                }

                if (itCandidate != itTwRangeEnd)
                {
                    copy(result.texts, itCandidate, itTwRange); // this is maximal 1 element
                }
                result.next = itTwRange;
            }

            return result;
        }

        StoreIterator m_storeBegin;
        StoreIterator m_storeEnd;
        const LocalizedTextFilter& m_filter;
};


inline bool sameReferenceLanguageVersion(const StoreIterator& lhs, const StoreIterator& rhs, const StoreIterator& end)
{
    if (lhs == end || rhs == end)
    {
        return false;
    }

    const auto& lhsKey = lhs->first;
    const auto& rhsKey = rhs->first;

    return lhsKey.reference() == rhsKey.reference()
            && lhsKey.language() == rhsKey.language()
            && lhsKey.version() == rhsKey.version();
}

}
