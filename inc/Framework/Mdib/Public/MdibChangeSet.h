#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Public/Model/HandleRange.h>
#include <Framework/Mdib/Public/Model/EntityFactory.h>

#include <memory>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Builder class to orchestrate MDIB change sets.
 *
 * @details *Informal:* A change set represents a transaction over the MDIB. It represents changes that are
 * applied to an MDIB or represents the changes of an MDIB in an change observer callback.
 *
 * ### Invalid handles
 * It is not possible to add entities with invalid handle to the change set.
 * If a function of this class is called with such an entity, this entity will be skipped.
 *
 * ### Entities in different parts of the change set
 * There are restrictions in which part of the change set a entity may occur. If an entity violates these
 * restriction then the change set cannot be written into the Mdib.
 *
 * #### For use with Local Mdibs
 *
 * An entity can occur only in one part of the change set - its either @c inserted, @c updated, or @c removed.
 *
 * #### For use with Remote Mdibs
 * Note: Remote Mdibs typically cannot be changed by end users/products but other components (S31) uses them.
 *
 * An entity can occur in different parts of change set. in that case evaluation order matters. An entity cannot
 * be **removed** and **updated** but not **inserted**.
 *
 * **Semantic order: remove - insert - update**
 *
 * Example:
 * If an entity is in the change set as @c removed and @c inserted, then it was in that transaction
 * removed first and after that inserted. The new MDIB will contain that entity.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP MdibChangeSet
{
    public:
        /**
         * @brief Constructor.
         */
        MdibChangeSet();

        /**
         * @brief Destructor.
         */
        ~MdibChangeSet() noexcept;

        /**
         * @brief Copy constructor.
         */
        MdibChangeSet(const MdibChangeSet& rhs);

        /**
         * @brief Move constructor.
         */
        MdibChangeSet(MdibChangeSet&& rhs) noexcept;

        /**
         * @brief Copy assign.
         */
        MdibChangeSet& operator=(const MdibChangeSet& rhs);

        /**
         * @brief Move assign.
         */
        MdibChangeSet& operator=(MdibChangeSet&& rhs) noexcept;

        /**
         * @brief Replace updated entities.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& updatedEntities(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief Replace removed entities.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& removedEntities(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief Add one inserted entity.
         * @details \attention The order in which the entities are added to the change set matters.
         *                     If you add an entity twice, the position of the first insert is taken
         *                     into consideration.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& addOneToInsert(const NotNull<SharedPtr<T_Entity>>& entity);

        /**
         * @brief Add one updated entity.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& addOneToUpdate(const NotNull<SharedPtr<T_Entity>>& entity);

        /**
         * @brief Add one removed entity.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& addOneToRemove(const NotNull<SharedPtr<T_Entity>>& entity);

        /**
         * @brief Add one removed entity.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& addOneToRemove(const BasicHandle<T_Entity>& handle);

        /**
         * @brief Add many inserted entities.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& addManyToInsert(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief Add many updated entities.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& addManyToUpdate(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief Add many removed entities.
         * @tparam T_Entity The affected entity type.
         */
        template<class T_Entity>
        MdibChangeSet& addManyToRemove(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief Retrieve all inserted entities.
         * @tparam T_Entity The entity type to retrieve.
         */
        template<class T_Entity>
        MdibEntityRange<T_Entity> insertedEntities() const;

        /**
         * @brief Retrieve all updated entities.
         * @tparam T_Entity The entity type to retrieve.
         */
        template<class T_Entity>
        MdibEntityRange<T_Entity> updatedEntities() const;

        /**
         * @brief Retrieve all removed entities.
         * @tparam T_Entity The entity type to retrieve.
         */
        template<class T_Entity>
        MdibEntityRange<T_Entity> removedEntities() const;

        /**
         * @brief Retrieve one inserted entity.
         * @tparam T_Entity The entity type to retrieve.
         */
        template<class T_Entity>
        SharedPtr<T_Entity> insertedEntity(const BasicHandle<T_Entity>& handle) const;

        /**
         * @brief Retrieve one updated entity.
         * @tparam T_Entity The entity type to retrieve.
         */
        template<class T_Entity>
        SharedPtr<T_Entity> updatedEntity(const BasicHandle<T_Entity>& handle) const;

        /**
         * @brief Retrieve one removed entity.
         * @tparam T_Entity The entity type to retrieve.
         */
        template<class T_Entity>
        SharedPtr<T_Entity> removedEntity(const BasicHandle<T_Entity>& handle) const;

        /**
         * @brief Resets inserted, updated and removed entities.
         */
        void clear();

        /**
         * @brief Checks if there are any changes to a specific type.
         * @return \c true if at least one entity of the given type \c T_Entity was inserted, updated or removed, otherwise false.
         */
        template<class T_Entity>
        bool hasAnyChanges() const;

        /// Returns @c true iif there are no entities in the change set.
        bool empty() const;

        /// Returns @c true iif there are no entities for update in the change set.
        bool emptyUpdatedEntities() const;

        /// Returns @c true iif there are no entities for insertion in the change set.
        bool emptyInsertedEntities() const;

        /// Returns @c true iif there are no entities for removal in the change set.
        bool emptyRemovedEntities() const;

        /**
         * @brief Checks if the handle is already inserted or updated in the MdibChangeSet.
         * @return \c true if the handle is duplicate \c false otherwise.
         */
        template<class T_Entity>
        bool isAlreadyInsertedOrUpdated(const BasicHandle<T_Entity>& handle) const;

        /**
         * @brief Get range that reflects an ordered, untyped set of handles of the inserted entities.
         */
        OrderedHandleRange insertionOrder() const;

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
};
/**
 * @brief Add an entity given by their builders, either to the change set for description update or
 * to the change set for state update.
 *
 * This function can be used to filter changed entities in such that have changed descriptors and
 * maybe states, and such that have only changed states. This differentiation is needed for SDC (to transmit
 * state changes only if descriptor was not changed.
 *
 * If there are no changes in descriptor nor state, the entity is not added to any change set.
 *
 * If oldEntity is empty - nothing is added (there is no handle)
 *
 * @param[in] descriptorBuilder builder of the entity
 * @param[in] stateBuilder builder of the entity
 * @param[in,out] changeSetDescription change set for description changes
 * @param[in,out] changeSetState change set for state changes
 * @param[in] oldEntity old entity (used for comparison for changes)
 * @ingroup Mdib
 */
template<class T_Entity, class T_Entity_Descriptor_Builder, class T_Entity_State_Builder>
inline void distributeToChangeSetsForUpdate(
        const T_Entity_Descriptor_Builder &descriptorBuilder,
        const T_Entity_State_Builder &stateBuilder,
        MdibChangeSet &changeSetDescription,
        MdibChangeSet &changeSetState,
        const SharedPtr<T_Entity> &oldEntity)
{
    if (oldEntity && descriptorBuilder.isChanged(*oldEntity->descriptor()))
    {
        auto updated = DFL::Mdib::EntityFactory::create(oldEntity->handle(),
                                                        descriptorBuilder,
                                                        stateBuilder,
                                                        oldEntity->parent());
        changeSetDescription.addOneToUpdate(updated);
    }
    else if (oldEntity && stateBuilder.isChanged(*oldEntity->state()))
    {
        auto updated = DFL::Mdib::EntityFactory::create(asNotNull(oldEntity), stateBuilder);
        changeSetState.addOneToUpdate(updated);
    }
}

/**
 * @brief Definition of shared pointer type \ref MdibChangeSetSharedPtr for the \ref MdibChangeSet.
 */
using MdibChangeSetSharedPtr = SharedPtr<MdibChangeSet>;

/**
 * @brief Definition of shared pointer const type \ref ConstMdibChangeSetSharedPtr for the \ref MdibChangeSet.
 */
using ConstMdibChangeSetSharedPtr = SharedPtr<const MdibChangeSet>;

}
}
