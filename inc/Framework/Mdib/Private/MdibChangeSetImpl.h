#pragma once

#include <Framework/Mdib/Private/MdibEntityMapUtils.h>
#include <Framework/Mdib/Private/MdibIteratorAlgorithm.h>
#include <Framework/Mdib/Private/Utils/ContainerUtils.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalVariant.h>

namespace DFL::Mdib
{
class MdibChangeSet::Impl
{
public:
    template<class T_Entity>
    void updatedEntities(const MdibEntityRange<T_Entity>& entities);

    template<class T_Entity>
    void removedEntities(const MdibEntityRange<T_Entity>& entities);

    template<class T_Entity>
    void addOneToInsert(const NotNull<SharedPtr<T_Entity>>& entity);

    template<class T_Entity>
    void addOneToUpdate(const NotNull<SharedPtr<T_Entity>>& entity);

    template<class T_Entity>
    void addOneToRemove(const NotNull<SharedPtr<T_Entity>>& entity);

    template<class T_Entity>
    void addOneToRemove(const BasicHandle<T_Entity>& handle);

    template<class T_Entity>
    void addManyToInsert(const MdibEntityRange<T_Entity>& entities);

    template<class T_Entity>
    void addManyToUpdate(const MdibEntityRange<T_Entity>& entities);

    template<class T_Entity>
    void addManyToRemove(const MdibEntityRange<T_Entity>& entities);

    template<class T_Entity>
    MdibEntityRange<T_Entity> insertedEntities() const;

    template<class T_Entity>
    MdibEntityRange<T_Entity> updatedEntities() const;

    template<class T_Entity>
    MdibEntityRange<T_Entity> removedEntities() const;

    template<class T_Entity>
    SharedPtr<T_Entity> insertedEntity(const BasicHandle<T_Entity>& handle) const;

    template<class T_Entity>
    SharedPtr<T_Entity> updatedEntity(const BasicHandle<T_Entity>& handle) const;

    template<class T_Entity>
    SharedPtr<T_Entity> removedEntity(const BasicHandle<T_Entity>& handle) const;

    void clear();

    template<class T_Entity>
    bool hasAnyChanges() const;

    bool empty() const;

    bool emptyUpdatedEntities() const;

    bool emptyInsertedEntities() const;

    bool emptyRemovedEntities() const;

    template<class T_Entity>
    bool isAlreadyInsertedOrUpdated(const BasicHandle<T_Entity>& handle) const;

    OrderedHandleRange insertionOrder() const;

private:
    DFL::Mdib::Impl::MutableMdibEntityMapContainer m_insertedEntities;
    DFL::Mdib::Impl::MutableMdibEntityMapContainer m_updatedEntities;
    DFL::Mdib::Impl::MutableMdibEntityMapContainer m_removedEntities;

    typename OrderedHandleRange::ContainerType m_insertionOrder;

    template<class T_Entity>
    void replaceEntities(DFL::Mdib::Impl::MutableMdibEntityMapContainer& entities, const MdibEntityRange<T_Entity>& entityRange);

    // returns true if there was an entity added, or false if handle was invalid or entity has been replaced
    template<class T_Entity>
    bool addOneEntity(DFL::Mdib::Impl::MutableMdibEntityMapContainer& entities, const NotNull<SharedPtr<T_Entity>>& entity);

    template<class T_Entity>
    void addManyEntities(DFL::Mdib::Impl::MutableMdibEntityMapContainer& entities, const MdibEntityRange<T_Entity>& entityRange);

};

template<class T_Entity>
inline MdibEntityRange<T_Entity> MdibChangeSet::Impl::insertedEntities() const
{
    return m_insertedEntities.range<T_Entity>();
}

template<class T_Entity>
inline MdibEntityRange<T_Entity> MdibChangeSet::Impl::updatedEntities() const
{
    return m_updatedEntities.range<T_Entity>();
}

template<class T_Entity>
inline MdibEntityRange<T_Entity> MdibChangeSet::Impl::removedEntities() const
{
    return m_removedEntities.range<T_Entity>();
}

template<class T_Entity>
inline SharedPtr<T_Entity> MdibChangeSet::Impl::insertedEntity(const BasicHandle<T_Entity>& handle) const
{
    if constexpr (std::is_same_v<T_Entity, AlertSignalVariant>)
    {
        if (auto entity = m_insertedEntities.entity(MdsAlertSignalHandle{handle.string()}))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
        if (auto entity = m_insertedEntities.entity(VmdAlertSignalHandle{handle.string()}))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
        return {};
    }
    else
    {
        return m_insertedEntities.entity(handle);
    }
}

template<class T_Entity>
inline SharedPtr<T_Entity> MdibChangeSet::Impl::updatedEntity(const BasicHandle<T_Entity>& handle) const
{
    if constexpr (std::is_same_v<T_Entity, AlertSignalVariant>)
    {
        if (auto entity = m_updatedEntities.entity(MdsAlertSignalHandle{handle.string()}))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
        if (auto entity = m_updatedEntities.entity(VmdAlertSignalHandle{handle.string()}))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
        return {};
    }
    else
    {
        return m_updatedEntities.entity(handle);
    }
}

template<class T_Entity>
inline SharedPtr<T_Entity> MdibChangeSet::Impl::removedEntity(const BasicHandle<T_Entity>& handle) const
{
    if constexpr (std::is_same_v<T_Entity, AlertSignalVariant>)
    {
        if (auto entity = m_removedEntities.entity(MdsAlertSignalHandle{handle.string()}))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
        if (auto entity = m_removedEntities.entity(VmdAlertSignalHandle{handle.string()}))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
        return {};
    }
    else
    {
        return m_removedEntities.entity(handle);
    }
}

template<class T_Entity>
inline void MdibChangeSet::Impl::updatedEntities(const MdibEntityRange<T_Entity>& entities)
{
    replaceEntities(m_updatedEntities, entities);
}

template<class T_Entity>
inline void MdibChangeSet::Impl::removedEntities(const MdibEntityRange<T_Entity>& entities)
{
    replaceEntities(m_removedEntities, entities);
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addOneToInsert(const NotNull<SharedPtr<T_Entity>>& entity)
{
    if (addOneEntity(m_insertedEntities, entity))
    {
        m_insertionOrder.push_back(toHandle(entity->handle()));
    }
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addOneToUpdate(const NotNull<SharedPtr<T_Entity>>& entity)
{
    addOneEntity(m_updatedEntities, entity);
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addOneToRemove(const NotNull<SharedPtr<T_Entity>>& entity)
{
    addOneEntity(m_removedEntities, entity);
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addOneToRemove(const BasicHandle<T_Entity>& handle)
{
    addOneEntity(m_removedEntities, EntityFactory::create(handle, BasicHandle<typename T_Entity::ParentType>()));
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addManyToInsert(const MdibEntityRange<T_Entity>& entities)
{
    for (const auto& entity : entities)
    {
        addOneToInsert(entity);
    }
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addManyToUpdate(const MdibEntityRange<T_Entity>& entities)
{
    addManyEntities(m_updatedEntities, entities);
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addManyToRemove(const MdibEntityRange<T_Entity>& entities)
{
    addManyEntities(m_removedEntities, entities);
}

template<class T_Entity>
inline void MdibChangeSet::Impl::replaceEntities(DFL::Mdib::Impl::MutableMdibEntityMapContainer& entities, const MdibEntityRange<T_Entity>& entityRange)
{
    entities.modifiableMap<T_Entity>().clear();
    addManyEntities(entities, entityRange);
}

template<class T_Entity>
inline bool MdibChangeSet::Impl::addOneEntity(DFL::Mdib::Impl::MutableMdibEntityMapContainer& entities, const NotNull<SharedPtr<T_Entity>>& entity)
{
    if (!entity->handle().isValid())
    {
        return false;
    }
    if constexpr (std::is_same_v<T_Entity, AlertSignalVariant>)
    {
        auto variant = entity->sharedVariant();
        if (variant.index() == 0)
        {
            if (auto specializedEntity = std::get<0>(variant))
            {
                return addOneEntity(entities, asNotNull(specializedEntity));
            }
        }
        if (variant.index() == 1)
        {
            if (auto specializedEntity = std::get<1>(variant))
            {
                return addOneEntity(entities, asNotNull(specializedEntity));
            }
        }
        return false;
    }
    else
    {
        auto& map = entities.modifiableMap<T_Entity>();
        return DFL::Mdib::Impl::replaceInMap(map, entity->handle(), entity) ==
               DFL::Mdib::Impl::ReplaceInMapResult::ValueInserted;
    }
}

template<class T_Entity>
inline void MdibChangeSet::Impl::addManyEntities(DFL::Mdib::Impl::MutableMdibEntityMapContainer& entities, const MdibEntityRange<T_Entity>& entityRange)
{
    if constexpr (std::is_same_v<T_Entity, AlertSignalVariant>)
    {
        // Since there are different maps for the different signals, we have to
        // insert them one by one to select the correct map
        for (const auto& entity : entityRange)
        {
            addOneEntity(entities, entity);
        }
    }
    else
    {
        // There is one map for all entities to add to
        auto&& map = entities.modifiableMap<T_Entity>();
        for (const auto& entity : entityRange)
        {
            DFL::Mdib::Impl::replaceInMap(map, entity->handle(), entity);
        }
    }
}

inline void MdibChangeSet::Impl::clear()
{
    m_insertedEntities = DFL::Mdib::Impl::MutableMdibEntityMapContainer();
    m_updatedEntities = DFL::Mdib::Impl::MutableMdibEntityMapContainer();
    m_removedEntities = DFL::Mdib::Impl::MutableMdibEntityMapContainer();
    m_insertionOrder.clear();
}

template<class T_Entity>
inline bool MdibChangeSet::Impl::isAlreadyInsertedOrUpdated(const BasicHandle<T_Entity>& handle) const
{
    return insertedEntity(handle) || updatedEntity(handle);
}

template<class T_Entity>
inline bool MdibChangeSet::Impl::hasAnyChanges() const
{
    return !insertedEntities<T_Entity>().empty() || !updatedEntities<T_Entity>().empty() || !removedEntities<T_Entity>().empty();
}

inline bool MdibChangeSet::Impl::empty() const
{
    return m_insertedEntities.empty() && m_updatedEntities.empty() && m_removedEntities.empty();
}

inline bool MdibChangeSet::Impl::emptyUpdatedEntities() const
{
    return m_updatedEntities.empty();
}

inline bool MdibChangeSet::Impl::emptyInsertedEntities() const
{
    return m_insertedEntities.empty();
}

inline bool MdibChangeSet::Impl::emptyRemovedEntities() const
{
    return m_removedEntities.empty();
}

inline OrderedHandleRange MdibChangeSet::Impl::insertionOrder() const
{
    return {m_insertionOrder.begin(), m_insertionOrder.end()};
}

}
