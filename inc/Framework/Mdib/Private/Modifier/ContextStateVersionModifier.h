#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Handles ContextStates descriptor versioning for changes in ContextDescriptor.
 * @ingroup Mdib
 */
class ContextStateVersionModifier : public Modifier
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
