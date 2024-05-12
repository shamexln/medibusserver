#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Handles deleting ContextStates when a ContextIndicator is deleted.
 * @details Applicable for Remote Mdib only as there is no explicit way to delete remote context states
 * @ingroup Mdib
 */
class OrphanedContextStateModifier : public Modifier
{
public:
    ModifierResult modifyFromConstChangeSet(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        std::optional<Timestamp> time,
        const MdibChangeSet& changes) override;
    ModifierResult modifyFromMutableChangeSet(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        std::optional<Timestamp> time,
        const NotNull<MdibChangeSetSharedPtr>& changes) override;
};

}
