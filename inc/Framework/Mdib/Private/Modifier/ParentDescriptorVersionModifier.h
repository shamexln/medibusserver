#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Handles descriptor versioning in case of inserted/removed children.
 * @ingroup Mdib
 */
class ParentDescriptorVersionModifier : public Modifier
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
