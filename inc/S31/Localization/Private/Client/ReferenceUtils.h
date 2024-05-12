#pragma once

#include <S31/Localization/S31Only/Client/LocalizedTextReferenceStore.h>

#include <Framework/Mdib/Public/LocalizedTextsVisitor.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/TypeTraits.h>

namespace S31::Localization::Client::References::Impl
{

/**
 * @brief Create a visitor for an @ref DFL::Mdib::Mdib or @ref DFL::Mdib::MdibChangeSet texts and extract
 * desired @ref S31::Localization::LocalizedTextReferences
 * @ingroup S31LocalizationClient
 */
template<class MdibOrChangeSet>
LocalizedTextReferenceStore ref(const MdibOrChangeSet& mdibOrChangeSet, DFL::Mdib::EntityPart part)
{
    static_assert(std::is_same<MdibOrChangeSet, DFL::Mdib::Mdib>::value || std::is_same<MdibOrChangeSet, DFL::Mdib::MdibChangeSet>::value,
                  "Reference can only be collected from a Mdib or a MdibChangeSet" );

    LocalizedTextReferences references;

    auto handler = [&](const DFL::Mdib::LocalizedTexts& texts)
    {
        for (const auto& text : texts)
        {
            if (text.version() && !text.languageTag() && !text.reference().get().empty())
            {
                references.insert(S31::Localization::LocalizedTextReference(text.reference(), *text.version(), boost::none, boost::none));
            }
        }
    };

    DFL::Mdib::LocalizedTextsVisitor visitor(mdibOrChangeSet, handler, part);
    DFL::Mdib::Entities<DFL_MDIB_ENTITY_ALL>::applyVisitor(visitor);
    LocalizedTextReferenceStore result;
    result.replaceWith(std::move(references));
    return result;
}

}
