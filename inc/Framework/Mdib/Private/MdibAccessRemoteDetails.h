#pragma once

#include <Framework/Mdib/Private/MdibTreeStoreHelper.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Describes specific behavior for remote MDIBs.
 * @details
 * - Pick the version of the elements that are inserted.
 * - No automatic version increment
 * - Children MUST have a parent in the MDIB.
 * @ingroup Mdib
 */
class MdibAccessRemoteDetails
{
public:
    template <class T_Entity>
    static NotNull<SharedPtr<T_Entity>> handleVersion(
        const SharedPtr<MdibEntity<T_Entity,
                                   typename T_Entity::DescriptorBuilderType,
                                   typename T_Entity::StateBuilderType,
                                   typename T_Entity::ParentType>>& oldEntity,
        const NotNull<SharedPtr<T_Entity>>& newEntity);

    template <class T_Entity>
    static NotNull<SharedPtr<T_Entity>> handleVersion(
        IsDescriptorUpdate isDescriptorUpdate,
        const SharedPtr<MdibEntity<T_Entity,
                                   typename T_Entity::DescriptorBuilderType,
                                   typename T_Entity::StateBuilderType,
                                   typename T_Entity::ParentType>>& oldEntity,
        const NotNull<SharedPtr<T_Entity>>& newEntity);

    template <class T_Entity>
    static NotNull<SharedPtr<T_Entity>> handleVersion(
        const SharedPtr<
            ContextDescriptorEntity<T_Entity,
                                    typename T_Entity::DescriptorBuilderType,
                                    typename T_Entity::StateBuilderType,
                                    typename T_Entity::ParentType>>& oldEntity,
        const NotNull<SharedPtr<T_Entity>>& newEntity);

    template <class T_Entity>
    static NotNull<SharedPtr<T_Entity>> handleVersion(
        IsDescriptorUpdate isDescriptorUpdate,
        const SharedPtr<
            ContextDescriptorEntity<T_Entity,
                                    typename T_Entity::DescriptorBuilderType,
                                    typename T_Entity::StateBuilderType,
                                    typename T_Entity::ParentType>>& oldEntity,
        const NotNull<SharedPtr<T_Entity>>& newEntity);

    template <class T_Entity>
    static NotNull<SharedPtr<T_Entity>> handleVersion(
        const SharedPtr<
            ContextStateEntity<T_Entity,
                               typename T_Entity::DescriptorBuilderType,
                               typename T_Entity::StateBuilderType,
                               typename T_Entity::ParentType>>& oldEntity,
        const NotNull<SharedPtr<T_Entity>>& newEntity);

    template <class T_Entity>
    static NotNull<SharedPtr<T_Entity>> handleVersion(
        IsDescriptorUpdate isDescriptorUpdate,
        const SharedPtr<
            ContextStateEntity<T_Entity,
                               typename T_Entity::DescriptorBuilderType,
                               typename T_Entity::StateBuilderType,
                               typename T_Entity::ParentType>>& oldEntity,
        const NotNull<SharedPtr<T_Entity>>& newEntity);
};
}
}
}
