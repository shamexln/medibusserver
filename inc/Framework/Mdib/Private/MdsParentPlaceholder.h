#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/MdsDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/MdsStateBuilder.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

class MdsParentPlaceholder;
using MdsParentPlaceholderHandle = BasicHandle<MdsParentPlaceholder>;

/**
 * @brief Placeholder class that is required by template functions that expect \ref MdibEntity interfaces.
 * @details \note The placeholder should only be instantiated by factories or in private code.
 * @ingroup Mdib
 */
class MdsParentPlaceholder: public MdibEntity<MdsParentPlaceholder, MdsDescriptorBuilder, MdsStateBuilder, MdsParentPlaceholder>
{
    public:
        MdsParentPlaceholder(const MdsParentPlaceholderHandle& handle,
                             const DFL::NotNull<MdsDescriptorSharedPtr>& descriptor,
                             VersionCounter descriptorVersion,
                             const DFL::NotNull<MdsStateSharedPtr>& state,
                             VersionCounter stateVersion,
                             const MdsParentPlaceholderHandle& parent);
};

inline MdsParentPlaceholder::MdsParentPlaceholder(const MdsParentPlaceholderHandle& handle,
                                                  const DFL::NotNull<MdsDescriptorSharedPtr>& descriptor,
                                                  VersionCounter descriptorVersion,
                                                  const DFL::NotNull<MdsStateSharedPtr>& state,
                                                  VersionCounter stateVersion,
                                                  const MdsParentPlaceholderHandle& /*parent*/) :
        MdibEntity(handle, descriptor, descriptorVersion, state, stateVersion, handle)
{
}

}
}
}
