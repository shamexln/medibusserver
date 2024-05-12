#pragma once

#include <Framework/Mdib/Private/MdibTreeStoreHelper.h>
#include <Framework/Mdib/Private/AlertSignalIndexHandling.h>
#include <Framework/Mdib/Private/Utils/SmartPtrLib.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/// A base class for MdibTreeStore and MdibTreeStoreBuilder
template<class T_Map>
class MdibTreeStoreBase
{
    public:
        MdibTreeStoreBase():
            m_entityMap(),
            m_removedEntityMap(),
            m_parentIndex(makeShared<const ParentIndex>()),
            m_presenceIndex(makeShared<const PresenceIndex>()),
            m_alertSignalIndex(makeShared<const AlertSignalIndexMap>())
        {}

        template<class T_SrcMap>
        MdibTreeStoreBase(T_SrcMap entityMap,
                          T_SrcMap removedEntityMap,
                          DFL::NotNull<SharedPtr<const ParentIndex>> parentIndex,
                          DFL::NotNull<SharedPtr<const PresenceIndex>> presenceIndex,
                          DFL::NotNull<SharedPtr<const AlertSignalIndexMap>> alertSignalIndex):
            m_entityMap(std::move(entityMap)),
            m_removedEntityMap(std::move(removedEntityMap)),
            m_parentIndex(std::move(parentIndex)),
            m_presenceIndex(std::move(presenceIndex)),
            m_alertSignalIndex(std::move(alertSignalIndex))
        {}

        SharedPtr<AlertSignalVariant> entity(const BasicHandle<AlertSignalVariant>& handle) const;

        template<class T_Entity>
        SharedPtr<T_Entity> entity(const BasicHandle<T_Entity>& handle) const;

        [[nodiscard]] bool isHandlePresent(const Handle& handle, const PresenceIndex& presenceIndex) const;

        [[nodiscard]] bool isHandlePresent(const Handle& handle) const;

        const T_Map& entityMap() const;

        const T_Map& removedEntityMap() const;

        [[nodiscard]] const DFL::NotNull<SharedPtr<const ParentIndex>>& parentIndex() const;

        [[nodiscard]] const DFL::NotNull<SharedPtr<const PresenceIndex>>& presenceIndex() const;

        [[nodiscard]] const DFL::NotNull<SharedPtr<const AlertSignalIndexMap>>& alertSignalIndex() const;


        template<class T_Entity>
        bool isEntityPresent(const SharedPtr<T_Entity>& entity) const;

    protected:
        template<class T_Entity>
        void entityMap(const SharedPtr<const std::map<DFL::Mdib::BasicHandle<T_Entity>, NotNull<SharedPtr<T_Entity>>>>& map);

        T_Map& entityMap();
        T_Map& removedEntityMap();

        void parentIndex(const DFL::NotNull<SharedPtr<const ParentIndex>> &index);

        void presenceIndex(const DFL::NotNull<SharedPtr<const PresenceIndex>> &index);

        void alertSignalIndex(const DFL::NotNull<SharedPtr<const AlertSignalIndexMap>>& index);

    private:

        T_Map m_entityMap;           ///< Holds all entities
        T_Map m_removedEntityMap;    ///< Holds removed entities if required

        DFL::NotNull<SharedPtr<const ParentIndex>> m_parentIndex;    ///< Holds child info
        DFL::NotNull<SharedPtr<const PresenceIndex>> m_presenceIndex;

        DFL::NotNull<SharedPtr<const AlertSignalIndexMap>> m_alertSignalIndex;

};

template<class T_Map>
inline SharedPtr<AlertSignalVariant> MdibTreeStoreBase<T_Map>::entity(const BasicHandle<AlertSignalVariant>& handle) const
{
    {
        auto entity = entityMap().entity(MdsAlertSignalHandle{handle.string()});
        if (isEntityPresent(entity))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
    }
    {
        auto entity = entityMap().entity(VmdAlertSignalHandle{handle.string()});
        if (isEntityPresent(entity))
        {
            return DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(asNotNull(entity));
        }
    }
    return nullptr;
}

template<class T_Map>
template<class T_Entity>
inline SharedPtr<T_Entity> MdibTreeStoreBase<T_Map>::entity(const BasicHandle<T_Entity>& handle) const
{
    auto entity = entityMap().entity(handle);
    if (isEntityPresent<T_Entity>(entity))
    {
        return entity;
    }
    return nullptr;
}

template<class T_Map>
inline bool MdibTreeStoreBase<T_Map>::isHandlePresent(const Handle& handle, const PresenceIndex& presenceIndex) const
{
    auto duplicateDetectionResult = presenceIndex.find(handle);
    if (duplicateDetectionResult == presenceIndex.end())
    {
        return false;
    }
    return duplicateDetectionResult->second == MdibEntityPresence::Present;
}

template<class T_Map>
inline bool MdibTreeStoreBase<T_Map>::isHandlePresent(const Handle& handle) const
{
    return isHandlePresent(handle, *presenceIndex());
}

template<class T_Map>
inline const T_Map& MdibTreeStoreBase<T_Map>::entityMap() const
{
    return m_entityMap;
}

template<class T_Map>
inline const T_Map& MdibTreeStoreBase<T_Map>::removedEntityMap() const
{
    return m_removedEntityMap;
}

template<class T_Map>
inline const DFL::NotNull<SharedPtr<const ParentIndex>>& MdibTreeStoreBase<T_Map>::parentIndex() const
{
    return m_parentIndex;
}

template<class T_Map>
inline const DFL::NotNull<SharedPtr<const PresenceIndex>>& MdibTreeStoreBase<T_Map>::presenceIndex() const
{
    return m_presenceIndex;
}

template<class T_Map>
inline const DFL::NotNull<SharedPtr<const AlertSignalIndexMap>>& MdibTreeStoreBase<T_Map>::alertSignalIndex() const
{
    return m_alertSignalIndex;
}


template<class T_Map>
template<class T_Entity>
inline bool MdibTreeStoreBase<T_Map>::isEntityPresent(const SharedPtr<T_Entity>& entity) const
{
    return entity != nullptr && isHandlePresent(toHandle(entity->handle()));
}

template<class T_Map>
template<class T_Entity>
inline void MdibTreeStoreBase<T_Map>::entityMap(const SharedPtr<const std::map<DFL::Mdib::BasicHandle<T_Entity>, NotNull<SharedPtr<T_Entity>>>>& map)
{
    m_entityMap.template map<T_Entity>(map);
}

template<class T_Map>
inline T_Map& MdibTreeStoreBase<T_Map>::entityMap()
{
    return m_entityMap;
}

template<class T_Map>
inline T_Map& MdibTreeStoreBase<T_Map>::removedEntityMap()
{
    return m_removedEntityMap;
}

template<class T_Map>
inline void MdibTreeStoreBase<T_Map>::parentIndex(const DFL::NotNull<SharedPtr<const ParentIndex>> &index)
{
    m_parentIndex = index;
}

template<class T_Map>
inline void MdibTreeStoreBase<T_Map>::presenceIndex(const DFL::NotNull<SharedPtr<const PresenceIndex>> &index)
{
    m_presenceIndex = index;
}

template<class T_Map>
inline void MdibTreeStoreBase<T_Map>::alertSignalIndex(const DFL::NotNull<SharedPtr<const AlertSignalIndexMap>>& index)
{
    m_alertSignalIndex = index;
}

}
}
}
