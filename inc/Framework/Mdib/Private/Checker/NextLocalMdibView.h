#pragma once

#include <Framework/Mdib/Private/Checker/NextLocalMdibViewRange.h>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Combined access to an MDIB and a change set that would be applied.
 *
 * @details
 * Sometime there exist an MDIB instance and a change set that should be
 * applied. Before the change set is applied some checks or modifications are
 * required. In these situations it is helpful to have a helper tool to access
 * the MDIB and change set as if it were already applied.
 *
 * **Attenion:** This is intended to be used on a local Mdib only, it will provide
 * incorrect data on a remote Mdib. This is because of the different allowed
 * @ref DFL::Mdib::MdibChangeSet "change sets".
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP NextLocalMdibView
{
    public:
        /**
         * @brief Input data that is combined when using access functions.
         *
         * @details
         * This class is only a view. Customers have to take care that the
         * lifetime of the MDIB and the changeset is guaranteed.
         *
         * The MDIB change type is required to make sure the correct descriptor
         * is provided when getting an entity. E.g., when having a component
         * report only the MDS state is updated not the descriptor.
         */
        NextLocalMdibView(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType);

        /**
         * @brief No temporary objects for views.
         */
        NextLocalMdibView(const Mdib& mdib, MdibChangeSet&& changes, MdibChangeType changeType) = delete;

        /**
         * @brief Provides access to the entity as if the change set where
         * applied to the MDIB.
         */
        template<class T_Entity>
        SharedPtr<T_Entity> entity(const BasicHandle<T_Entity>& handle) const;

        /**
         * @brief Provides access to a range of entity as if the change set were
         * applied to the MDIB.
         * @details Iterates through the entire MDIB, whether entities were changed or not.
         */
        template<class T_Entity>
        NextLocalMdibViewRange<T_Entity> range() const;

        /**
         * @brief Provides access to entities modified in this specific changeSet as if they
         * were applied to the MDIB.
         * @details Use when only interested in updated/inserted entities. This does not
         * provide access to unchanged entities in the MDIB like range() does.
         */
        template<class T_Entity>
        NextLocalMdibViewRange<T_Entity> modified() const;

    private:
        const Mdib& m_mdib;
        const MdibChangeSet& m_changes;
        const MdibChangeType m_changeType;
};

template<class T_Entity>
NextLocalMdibViewRange<T_Entity> NextLocalMdibView::range() const
{
    return NextLocalMdibViewRange<T_Entity>(m_mdib, m_changes, m_changeType, IterationMode::AllEntities);
}

template<class T_Entity>
NextLocalMdibViewRange<T_Entity> NextLocalMdibView::modified() const
{
    return NextLocalMdibViewRange<T_Entity>(m_mdib, m_changes, m_changeType, IterationMode::ModifiedOnly);
}

}
}
