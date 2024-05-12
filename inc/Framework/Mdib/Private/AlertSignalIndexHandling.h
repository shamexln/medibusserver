#pragma once

#include <map>
#include <Framework/Mdib/Private/MdibTreeStoreHelper.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

template <class T_Index>
class AlertSignalIndex
{
    public:
        explicit AlertSignalIndex(const T_Index& alertSigIndex);

        const T_Index& alertSignalIndex() const;
        bool hasAlertSignalIndexChanged() const;
        SharedPtr<T_Index> alertSignalIndex();

    private:
        SharedPtr<T_Index> m_alertSignalIndex;
        const T_Index& m_constRefAlertSignalIndex;
};

template <class T_Index>
inline AlertSignalIndex<T_Index>::AlertSignalIndex(const T_Index& alertSigIndex) :
        m_alertSignalIndex(nullptr),
        m_constRefAlertSignalIndex(alertSigIndex)
{
}

template <class T_Index>
inline const T_Index& AlertSignalIndex<T_Index>::alertSignalIndex() const
{
    if (m_alertSignalIndex)
    {
        return *m_alertSignalIndex;
    }
    return m_constRefAlertSignalIndex;
}

template <class T_Index>
inline bool AlertSignalIndex<T_Index>::hasAlertSignalIndexChanged() const
{
    return static_cast<bool>(m_alertSignalIndex);
}

template <class T_Index>
inline SharedPtr<T_Index> AlertSignalIndex<T_Index>::alertSignalIndex()
{
    if (!m_alertSignalIndex)
    {
        m_alertSignalIndex = DFL_MDIB_MAKE_SHARED<T_Index>(m_constRefAlertSignalIndex);
    }
    return m_alertSignalIndex;
}

struct AlertSignalIndices
{
        AlertSignalIndices(const AlertSignalIndex<AlertSignalIndexMap>& alertSigIndex);
        AlertSignalIndex<AlertSignalIndexMap> alertSignalIndex;
};

inline AlertSignalIndices::AlertSignalIndices(const AlertSignalIndex<AlertSignalIndexMap>& alertSigIndex) :
        alertSignalIndex(alertSigIndex)
{
}

/**
 * @brief This class handles the indices of alert signal handles.
 * @details The index is needed to resolve the alert signals of an alert condition.
 * @ingroup Mdib
 */
class AlertSignalIndexHandling
{
    public:

        /**
         * @name onInsertOne : responsible for insert of signals
         * @{
         */
        template<class T_Entity>
        static void onInsertOne(const NotNull<SharedPtr<T_Entity>>& /*entity*/,
                                TreeStoreTransactionContext& /*transactionContext*/)
        {
        }

        static void onInsertOne(const NotNull<SharedPtr<MdsAlertSignal>>& entity,
                                TreeStoreTransactionContext& transactionContext);

        static void onInsertOne(const NotNull<SharedPtr<VmdAlertSignal>>& entity,
                                TreeStoreTransactionContext& transactionContext);
        /** @} */

        /**
         * @name onUpdateOne : responsible for update of signals
         * @{
         */
        template<class T_Entity>
        static void onUpdateOne(const NotNull<SharedPtr<T_Entity>>& /* oldEntity */,
                                const NotNull<SharedPtr<T_Entity>>& /* newEntity */,
                                AlertSignalIndices& /*alertSignalIndices*/)
        {
        }
        static void onUpdateOne(const NotNull<SharedPtr<MdsAlertSignal>>& oldEntity,
                                const NotNull<SharedPtr<MdsAlertSignal>>& newEntity,
                                AlertSignalIndices& alertSignalIndices);

        static void onUpdateOne(const NotNull<SharedPtr<VmdAlertSignal>>& oldEntity,
                                const NotNull<SharedPtr<VmdAlertSignal>>& newEntity,
                                AlertSignalIndices& alertSignalIndices);


        /** @} */

        /**
         * @name onRemoveOne : responsible for remove of signals
         * @{
         */
        template<class T_Entity>
        static void onRemoveOne(const NotNull<SharedPtr<T_Entity>>& /*entity*/,
                                TreeStoreTransactionContext& /*transactionContext*/)
        {
        }

        static void onRemoveOne(const NotNull<SharedPtr<MdsAlertSignal>>& entity,
                                TreeStoreTransactionContext& transactionContext);

        static void onRemoveOne(const NotNull<SharedPtr<VmdAlertSignal>>& entity,
                                TreeStoreTransactionContext& transactionContext);
        /** @} */

    private:
        template<class T_Entity, class T_IndexMap>
        static void onInsertOneSignal(const NotNull<SharedPtr<T_Entity>>& entity, T_IndexMap& map);

        template<class T_Entity, class T_IndexMap>
        static void onUpdateOneSignal(const NotNull<SharedPtr<T_Entity>>& oldEntity,
                                      const NotNull<SharedPtr<T_Entity>>& newEntity,
                                      T_IndexMap& map);

        template<class T_Entity, class T_IndexMap>
        static void onRemoveOneSignal(const NotNull<SharedPtr<T_Entity>>& entity, T_IndexMap& map);
};


inline void AlertSignalIndexHandling::onInsertOne(const NotNull<SharedPtr<MdsAlertSignal>>& entity,
                                                  TreeStoreTransactionContext& transactionContext)
{
    onInsertOneSignal(entity, *(transactionContext.alertSignalIndex()));
}

inline void AlertSignalIndexHandling::onInsertOne(const NotNull<SharedPtr<VmdAlertSignal>>& entity,
                                                  TreeStoreTransactionContext& transactionContext)
{
    onInsertOneSignal(entity, *(transactionContext.alertSignalIndex()));
}

inline void AlertSignalIndexHandling::onUpdateOne(const NotNull<SharedPtr<MdsAlertSignal>>& oldEntity,
                                                  const NotNull<SharedPtr<MdsAlertSignal>>& newEntity,
                                                  AlertSignalIndices& alertSignalIndices)
{
    auto&& map = alertSignalIndices.alertSignalIndex.alertSignalIndex();
    onUpdateOneSignal(oldEntity, newEntity, *map);
}

inline void AlertSignalIndexHandling::onUpdateOne(const NotNull<SharedPtr<VmdAlertSignal>>& oldEntity,
                                                  const NotNull<SharedPtr<VmdAlertSignal>>& newEntity,
                                                  AlertSignalIndices& alertSignalIndices)
{
    auto&& map = alertSignalIndices.alertSignalIndex.alertSignalIndex();
    onUpdateOneSignal(oldEntity, newEntity, *map);
}

inline void AlertSignalIndexHandling::onRemoveOne(const NotNull<SharedPtr<MdsAlertSignal>>& entity,
                                                  TreeStoreTransactionContext& transactionContext)
{
    onRemoveOneSignal(entity, *transactionContext.alertSignalIndex());
}

inline void AlertSignalIndexHandling::onRemoveOne(const NotNull<SharedPtr<VmdAlertSignal>>& entity,
                                                  TreeStoreTransactionContext& transactionContext)
{
    onRemoveOneSignal(entity, *transactionContext.alertSignalIndex());
}

template<class T_Entity, class T_IndexMap>
inline void AlertSignalIndexHandling::onInsertOneSignal(const NotNull<SharedPtr<T_Entity>>& entity,
                                                        T_IndexMap& map)
{
    if (!entity->descriptor()->conditionSignaledHandle().isValid())
    {
        return;
    }

    typename T_IndexMap::value_type const value(
                entity->descriptor()->conditionSignaledHandle(),
                entity->handle().string()
                );
    map.insert(value);
}

template<class T_Entity, class T_IndexMap>
inline void AlertSignalIndexHandling::onUpdateOneSignal(const NotNull<SharedPtr<T_Entity>>& oldEntity,
                                                        const NotNull<SharedPtr<T_Entity>>& newEntity,
                                                        T_IndexMap& map)
{
    if (oldEntity->descriptorVersion() != newEntity->descriptorVersion() &&
            oldEntity->descriptor()->conditionSignaledHandle() != newEntity->descriptor()->conditionSignaledHandle())
    {
        onRemoveOneSignal(oldEntity, map);
        onInsertOneSignal(newEntity, map);
    }
}

template<class T_Entity, class T_IndexMap>
inline void AlertSignalIndexHandling::onRemoveOneSignal(const NotNull<SharedPtr<T_Entity>>& entity,
                                                        T_IndexMap& map)
{
    if (!entity->descriptor()->conditionSignaledHandle().isValid())
    {
        return;
    }
    auto r = map.equal_range(entity->descriptor()->conditionSignaledHandle());
    for (auto it = r.first; it != r.second; ++it)
    {
        if (it->second.string() == entity->handle().string())
        {
            map.erase(it);
            return;
        }
    }
}

}
}
}
