#pragma once

#include <Framework/Mdib/Private/ContextDescriptorEntity.h>
#include <Framework/Mdib/Private/ContextStateEntity.h>
#include <Framework/Mdib/Private/MdibTreeStoreHelper.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Describes specific behavior for local MDIBs.
 * @details
 * - Pick the version of inserted entities from the internal storage.
 * - Automatic version increment on inserted/updated elements
 * - Continue version of removed objects from the point where they were deleted.
 * - Take care of containment tree stability (no children without parents)
 * @ingroup Mdib
 */
class MdibAccessLocalDetails
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
