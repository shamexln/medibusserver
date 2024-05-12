#pragma once

#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Localization/Public/Common/S31LtsExImp.h>

namespace S31::Localization
{

/**
 * @name Internal data structure
 * @brief Internal data structure in the @ref S31::Localization::LocalizedTextReferenceStore
 * @ingroup S31LocalizationCommon
 */
///@{
using ReferenceStoreContainer = LocalizedTextReferences;
using ReferenceStoreIterator = ReferenceStoreContainer::const_iterator;
///@}


/**
 * @brief Storage for @ref LocalizedTextReference.
 * @details For usage on client side. Not thread safe.
 * @ingroup S31LocalizationCommon
 */
class S31_LTS_EXPIMP LocalizedTextReferenceStore
{
    public:
        /**
         * @brief Adds the given ref to the store.
         * @details Handles 'is more general' semantics. That is that:
         * - if there is a more general reference already in the store, then nothings is added
         * - More specialized references in the store will be removed
         */
        void add(const LocalizedTextReference& ref);

        /**
         * @brief Merges the given store in this one.
         * @details The rules of @ref add() apply here too.
         */
        void merge(const LocalizedTextReferenceStore& other);

        /**
         * @brief Moves the text references into this one.
         * @details Changes ownership of the LocalizedTextReferences passed in
         */
        void replaceWith(LocalizedTextReferences&& refs);

        /**
         * @brief Checks if the given reference is covered by the store.
         *
         * @note Special case of a store that contains all textwidths (for one ref, version, and number of lines):
         * Then this function will return @c false for the according reference with no textwidth set.
         *
         * @return returns true if ref or a more general reference is contained in the store; false otherwise
         */
        bool isCovered(const LocalizedTextReference& ref) const;

        /// The size (this is only used in testing and should not be inherited in derived classes).
        size_t size() const
        {
            return m_data.size();
        }

        /// Modifiable access to the underlying datastructure.
        ReferenceStoreContainer& data()
        {
            return m_data;
        }

    private:
        ReferenceStoreContainer m_data;
};

}
