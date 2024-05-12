#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/ErrorHandles.h>
#include <Framework/Mdib/Private/MdibEntityMapUtils.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalVariant.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Uri.h>
#include <Framework/Mdib/Public/Utils/Entities.h>

#include <Framework/Utils/Public/EnumClass.h>

#include <boost/optional.hpp>

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

struct IsDescriptorUpdateTag;
/**
 * @brief Indicates if an update is a descriptor update (\c true) or not (\c false).
 * @details This requires the MDIB details implementation to consider a descriptor or not consider a descriptor during version handling.
 * @ingroup Mdib
 */
using IsDescriptorUpdate = DFL::StrongTypedef<bool, IsDescriptorUpdateTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;

/**
 * @brief Definition of a result status that ensues from any MDIB tree store operation.
 * @ingroup Mdib
 */
enum class MdibTreeStoreStatus
{
    Success,                    //!< Operation was successful
    DuplicateHandle,            //!< Operation failed due to handle duplication
    HandleNotFound,             //!< Operation failed since a handle was not found
    UnknownDeletionStrategy,    //!< Operation failed since deletion strategy is unknown (abnormal error)
    ConsistencyError,           //!< Duplicate detection map and MDIB entity map diverge (abnormal error)
    InvalidHandle,              //!< Handle contains empty or invalid characters ( U+0000 to U+0020 or U+FFFD )
    DeletedEntityNotFound,      //!< After deletion the deleted entity was not found in the set of affected entities (abnormal error)
    NotAssocContextRemoved      //!< For RemoteMdib's, removed NotAssociated context will be in the result changeSet but not in the MdibTreeStore
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MdibTreeStoreStatus, (Success)(DuplicateHandle)(HandleNotFound)(UnknownDeletionStrategy)(ConsistencyError)(InvalidHandle)(DeletedEntityNotFound)(NotAssocContextRemoved))

/**
 * @brief Definition of MDIB entity presence.
 * @ingroup Mdib
 */
enum class MdibEntityPresence
{
    Present,    //!< The entity is present
    Removed    //!< The entity is marked as removed
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MdibEntityPresence, (Present)(Removed))

/**
 * @brief Definition of update strategy.
 * @ingroup Mdib
 */
enum class UpdateStrategy
{
    FullEntity,    //!< The entire entity comprising descriptor and state are updated
    StateOnly    //!< Only the state portion is updated
};
DFL_ENUM_CLASS_STREAM_OPERATOR(UpdateStrategy, (FullEntity)(StateOnly))

using ParentIndexChildContainer = std::vector<Handle>;
using ParentIndex = std::map<Handle, ParentIndexChildContainer>;
using PresenceIndex = std::map<Handle, MdibEntityPresence>;
using AlertSignalIndexMap = std::multimap<Handle, AlertSignalVariantHandle>;

/**
 * @brief Set of data that is used as a transaction context on insert and remove in \ref MdibTreeStoreBuilder.
 * @ingroup Mdib
 */
class TreeStoreTransactionContext
{
    private:
        template<class T_Entity>
        struct InitFlag
        {
            bool initialized = false;
        };

        template<template<class T> class Container>
        struct ManyInitFlags: protected EntityContainer<Container, DFL_MDIB_ENTITY_ALL, MdsParentPlaceholder>
        {
                template<class T_Entity>
                bool getAndInit();

                template<class T_Entity>
                bool get() const;
        };

    public:
        /**
         * @brief Indicates if a certain map hosted by the transaction has been accessed once.
         * @details During a transaction, entity maps are added to the transaction when needed. To avoid unnecessary copies
         * in case a map is accessed multiple times, the InitFlags class stores a flag that indicates
         * if a typed map has already been initialized within the transaction context.
         */
        using InitFlags = ManyInitFlags<InitFlag>;

        /**
         * @brief Entity map container.
         */
        using MdibEntityMap = MutableMdibEntityMapContainer;

        /**
         * @brief Constructor that takes entity type-less indices.
         * @details Entity-related data can be initially set by \ref initEntities() and
         * \ref initRemovedEntities().
         */
        TreeStoreTransactionContext(NotNull<SharedPtr<PresenceIndex>> presenceIndex,
                                    NotNull<SharedPtr<ParentIndex>> parentIndex,
                                    NotNull<SharedPtr<AlertSignalIndexMap>> alertSignalIndex);

        /**
         * @brief Map of handles to \ref MdibEntityPresence enumeration.
         * @details Keeps track of entities being deleted and re-spawned.
         */
        const NotNull<SharedPtr<PresenceIndex>>& presenceIndex() const;

        /**
         * @brief Map that stores children of parents.
         */
        const NotNull<SharedPtr<ParentIndex>>& parentIndex() const;

        /**
         * @brief Index to store signal-to-condition relationships for MDS-based signals.
         */
        const NotNull<SharedPtr<AlertSignalIndexMap>>& alertSignalIndex() const;

        /**
         * @brief Index to store signal-to-condition relationships for MDS-based signals.
         */
        void alertSignalIndex(NotNull<SharedPtr<AlertSignalIndexMap>>&& updatedIndex);

        /**
         * @brief Initializes transaction for a specific entity map type.
         * @details Call this on every access to a specific type. The given map is only copied once.
         */
        template<class T_Entity>
        void initEntities(const SingleMap<T_Entity>& entities);

        /**
         * @brief Initializes transaction for a specific removed entity map type.
         * @details Call this on every access to a specific type. The given map is only copied once.
         */
        template<class T_Entity>
        void initRemovedEntities(const SingleMap<T_Entity>& removedEntities);

        /**
         * @brief Retrieve current state of the entity map.
         */
        MdibEntityMap& entities();

        /**
         * @brief Retrieve current state of the initialization flags for stored entities.
         */
        InitFlags& entitiesInitFlags();

        /**
         * @brief Retrieve current state of the entity map that represents removed entities.
         */
        MdibEntityMap& removedEntities();

        /**
         * @brief Retrieve current state of the initialization flags for stored removed entities.
         */
        InitFlags& removedEntitiesInitFlags();

        /**
         * @brief Call this function in order to indicate if an error occurred during transaction processing.
         * @details \ref valid() will return \c false afterwards. Invalidation cannot be undone.
         */
        void invalidate();

        /**
         * @brief Check if a transaction is valid (\c true) or not (\c false).
         */
        bool valid() const;

    private:
        NotNull<SharedPtr<PresenceIndex>> m_presenceIndex;
        NotNull<SharedPtr<ParentIndex>> m_parentIndex;
        NotNull<SharedPtr<AlertSignalIndexMap>> m_alertSignalIndex;

        InitFlags m_entitiesInitFlags;
        MdibEntityMap m_entities;
        InitFlags m_removedEntitiesInitFlags;
        MdibEntityMap m_removedEntities;
        bool m_valid{true};
};

/**
 * @brief Definition of a result object that ensues from any MDIB tree store operation.
 * @details The \ref MdibTreeStoreResult encloses
 *
 * - an operation result status and
 * - depending on the operation a map of affected MDIB entities (optional).
 * @ingroup Mdib
 */
template<typename T_Entity>
class MdibTreeStoreResult
{
    public:
        using HandleEntityMap = SingleMap<T_Entity>;

        /**
         * @brief Create result with given MDIB entity.
         */
        MdibTreeStoreResult(MdibTreeStoreStatus status, const T_Entity& entity);

        /**
         * @brief Create result with given MDIB entities.
         */
        MdibTreeStoreResult(MdibTreeStoreStatus status,
                            SharedPtr<const HandleEntityMap> entities);

        /**
         * @brief Retrieve entities
         * @return A range that allows to iterate over the entities in this store.
         */
        MdibEntityRange<T_Entity> entities() const;

        size_t size() const;

        /**
         * @brief Retrieve status.
         */
        MdibTreeStoreStatus status() const;

        ErrorHandles errorHandles() const;

    private:
        MdibTreeStoreStatus m_status;
        SharedPtr<const HandleEntityMap> m_entities;
        ErrorHandles m_errorHandles;
};

inline TreeStoreTransactionContext::TreeStoreTransactionContext(NotNull<SharedPtr<PresenceIndex>> presenceIndex,
                                                                NotNull<SharedPtr<ParentIndex>> parentIndex,
                                                                NotNull<SharedPtr<AlertSignalIndexMap>> alertSignalIndex) :
        m_presenceIndex(std::move(presenceIndex)),
        m_parentIndex(std::move(parentIndex)),
        m_alertSignalIndex(std::move(alertSignalIndex)),
        m_entities(),
        m_removedEntities()
{
}

template<class T_Entity>
inline void TreeStoreTransactionContext::initEntities(const SingleMap<T_Entity>& entities)
{
    if (!m_entitiesInitFlags.getAndInit<T_Entity>())
    {
        // Only copy if not copied before
        m_entities.replaceMap<T_Entity>(entities);
    }
}

template<class T_Entity>
inline void TreeStoreTransactionContext::initRemovedEntities(const SingleMap<T_Entity>& removedEntities)
{
    if (!m_removedEntitiesInitFlags.getAndInit<T_Entity>())
    {
        // Only copy if not copied before
        m_removedEntities.replaceMap<T_Entity>(removedEntities);
    }
}

inline void TreeStoreTransactionContext::invalidate()
{
    m_valid = false;
}

inline TreeStoreTransactionContext::MdibEntityMap& TreeStoreTransactionContext::entities()
{
    return m_entities;
}

inline TreeStoreTransactionContext::InitFlags& TreeStoreTransactionContext::entitiesInitFlags()
{
    return m_entitiesInitFlags;
}

inline TreeStoreTransactionContext::MdibEntityMap& TreeStoreTransactionContext::removedEntities()
{
    return m_removedEntities;
}

inline TreeStoreTransactionContext::InitFlags& TreeStoreTransactionContext::removedEntitiesInitFlags()
{
    return m_removedEntitiesInitFlags;
}

inline const NotNull<SharedPtr<PresenceIndex>>& TreeStoreTransactionContext::presenceIndex() const
{
    return m_presenceIndex;
}

inline const NotNull<SharedPtr<ParentIndex>>& TreeStoreTransactionContext::parentIndex() const
{
    return m_parentIndex;
}

inline const NotNull<SharedPtr<AlertSignalIndexMap>>& TreeStoreTransactionContext::alertSignalIndex() const
{
    return m_alertSignalIndex;
}
inline void TreeStoreTransactionContext::alertSignalIndex(NotNull<SharedPtr<AlertSignalIndexMap>>&& updatedIndex)
{
    m_alertSignalIndex = std::move(updatedIndex);
}

inline bool TreeStoreTransactionContext::valid() const
{
    return m_valid;
}

template<template<class T> class Container>
template<class T_Entity>
inline bool TreeStoreTransactionContext::ManyInitFlags<Container>::getAndInit()
{
    if (!InitFlag<T_Entity>::initialized)
    {
        InitFlag<T_Entity>::initialized = true;
        return false;
    }
    return true;
}

template<template<class T> class Container>
template<class T_Entity>
inline bool TreeStoreTransactionContext::ManyInitFlags<Container>::get() const
{
    return InitFlag<T_Entity>::initialized;
}

template<typename T_Entity>
MdibTreeStoreResult<T_Entity>::MdibTreeStoreResult(MdibTreeStoreStatus status, const T_Entity& entity) :
        m_status(status),
        m_entities(DFL_MDIB_MAKE_SHARED<HandleEntityMap>()),
        m_errorHandles(toHandle(entity.handle()), toHandle(entity.parent()))
{
}

template<class T_Entity>
MdibTreeStoreResult<T_Entity>::MdibTreeStoreResult(MdibTreeStoreStatus status,
                                                   SharedPtr<const HandleEntityMap> entities) :
        m_status(status),
        m_entities(std::move(entities)),
        m_errorHandles()
{
}

template<class T_Entity>
MdibEntityRange<T_Entity> MdibTreeStoreResult<T_Entity>::entities() const
{
    return toMdibEntityRange(*m_entities);
}

template<class T_Entity>
MdibTreeStoreStatus MdibTreeStoreResult<T_Entity>::status() const
{
    return m_status;
}

template<typename T_Entity>
size_t MdibTreeStoreResult<T_Entity>::size() const
{
    return m_entities->size();
}

template<typename T_Entity>
ErrorHandles MdibTreeStoreResult<T_Entity>::errorHandles() const
{
    return m_errorHandles;
}

} /* namespace Impl */
} /* namespace Mdib */
} /* namespace DFL */
