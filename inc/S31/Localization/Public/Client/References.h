#pragma once

#include <S31/Localization/Private/Client/ReferenceUtils.h>
#include <S31/Localization/Private/Common/InternalStoreHelper.h>
#include <S31/Localization/S31Only/Client/LocalizedTextReferenceStore.h>

#include <Framework/Mdib/Public/Utils/EntityLists.h>

namespace S31::Localization::Client::References
{

/**
 * @brief Returns @ref S31::Localization::LocalizedTextReferences containing all the @ref S31::Localization::LocalizedTextReference in the @ref DFL::Mdib::Mdib
 * @details Includes references from the entity's descriptor and state
 * @ingroup S31LocalizationClient
 */
inline LocalizedTextReferences textReferenceAll(const DFL::Mdib::Mdib& mdib)
{
    LocalizedTextReferences result(std::move(Impl::ref(mdib, DFL::Mdib::EntityPart::DescriptorAndState).data()));
    return result;
}

/**
 * @brief Returns @ref S31::Localization::LocalizedTextReferences containing all the @ref S31::Localization::LocalizedTextReference in the @ref DFL::Mdib::MdibChangeSet
 * @details Includes references from the entity's descriptor and state
 * @ingroup S31LocalizationClient
 */
inline LocalizedTextReferences textReferenceAll(const DFL::Mdib::MdibChangeSet& changeSet)
{
    LocalizedTextReferences result(std::move(Impl::ref(changeSet, DFL::Mdib::EntityPart::DescriptorAndState).data()));
    return result;
}

/**
 * @brief Returns @ref S31::Localization::LocalizedTextReferences containing all the @ref S31::Localization::LocalizedTextReference in the state part of @ref DFL::Mdib::MdibChangeSet
 * @details Only includes references from the entity's state and not from it's descriptor
 * @ingroup S31LocalizationClient
 */

inline LocalizedTextReferences textReferenceStates(const DFL::Mdib::MdibChangeSet& changeSet)
{
    LocalizedTextReferences result(std::move(Impl::ref(changeSet, DFL::Mdib::EntityPart::State).data()));
    return result;
}

}
