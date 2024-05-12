#pragma once

#include <Framework/Mdib/Private/MdibTreeStore.h>
#include <Framework/Mdib/Private/MdibEntityMapBuilder.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Private/MdibTreeStoreBase.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>

#include <memory>
#include <stdexcept>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief MDIB entity range with guaranteed order.
 * @ingroup Mdib
 */
template<class T_Entity>
using OrderedEntityRange = MdibEntityRange<T_Entity, std::vector<NotNull<SharedPtr<T_Entity>>>>;

/**
 * @brief Builder to create immutable \ref MdibTreeStore instances.
 * @ingroup Mdib
 */
template<class T_MdibDetails>
class MdibTreeStoreBuilder:
        public MdibTreeStoreBase<MdibEntityMapBuilder>,
        protected AlertSignalIndexHandling
{
    public:
        /**
         * @brief Use if multiple related insert/remove operations with different entity types are required.
         * @details Use \ref startTransaction() to get a %Transaction object. Use \ref commitTransaction()
         *          to commit data.
         * @ingroup Mdib
         */
        class Transaction
        {
            friend MdibTreeStoreBuilder<T_MdibDetails>;

            public:
                explicit Transaction(NotNull<SharedPtr<TreeStoreTransactionContext>>&& transactionContext);

                ~Transaction() = default;
                Transaction(Transaction&&) noexcept = default;
                Transaction& operator=(Transaction&&) noexcept = default;

                Transaction() = delete;
                Transaction(const Transaction&) = delete;
                Transaction& operator=(const Transaction&) = delete;

            private:
                NotNull<SharedPtr<TreeStoreTransactionContext>> m_transactionContext;

                TreeStoreTransactionContext& context();
        };

        using Self = MdibTreeStoreBuilder<T_MdibDetails>;
        MdibTreeStoreBuilder() = default;
        explicit MdibTreeStoreBuilder(const MdibTreeStore& mdibTreeStore);
        operator MdibTreeStore() const
        {
            return toMdibTreeStore();
        }

        MdibTreeStore toMdibTreeStore() const;

        MdibTreeStoreBuilder(const MdibTreeStoreBuilder& rhs) = default;
        MdibTreeStoreBuilder& operator=(const MdibTreeStoreBuilder& rhs);

        /**
         * @brief Call to start a transaction.
         * @details \attention While one transaction is open, do not start another one. This will throw an exception.
         */
        Transaction startTransaction();

        /**
         * @brief Submit data gathered during transaction.
         */
        void commitTransaction(Transaction&& transaction);

        /**
         * @brief Insert entity - descriptor and state at the same time.
         */
        template<class T_Entity>
        MdibTreeStoreResult<T_Entity> insert(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief Insert entity - descriptor and state at the same time.
         */
        template<class T_Entity>
        MdibTreeStoreResult<T_Entity> insert(const OrderedEntityRange<T_Entity>& entities);

        /**
         * @brief Update existing entity - descriptor and state
         * @details Only difference is consistency check - this function fails in local MDIBs if the entity does not exist
         */
        template<class T_Entity>
        MdibTreeStoreResult<T_Entity> update(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief entities Only updates the state from the given entity.
         */
        template<class T_Entity>
        MdibTreeStoreResult<T_Entity> updateStateOnly(const MdibEntityRange<T_Entity>& entities);

        /**
         * @brief Remove given entities from the store
         */
        template<class T_Entity>
        MdibTreeStoreResult<T_Entity> remove(const MdibEntityRange<T_Entity>& entities);

    private:
        using Status = MdibTreeStoreStatus;

        struct Entities: public DFL::Mdib::Entities<DFL_MDIB_ENTITY_ALL>
        {
        };

        // copy map from transaction to tree store if used
        class CopyInitializedMapsVisitor
        {
            public:
                template<class T_Entity>
                void visitEntity(MdibEntityMapBuilder& mapBuilder,
                                 TreeStoreTransactionContext::MdibEntityMap& mdibEntityMap,
                                 TreeStoreTransactionContext::InitFlags& initFlags);
        };

        std::weak_ptr<TreeStoreTransactionContext> m_transactionContext;

        NotNull<SharedPtr<TreeStoreTransactionContext>> createTransactionContext() const;

        template<class T_Entity>
        SingleMap<T_Entity>& pickCurrentEntities(const SharedPtr<TreeStoreTransactionContext>& context, SingleMap<T_Entity>& entitiesFromBuilder);

        AlertSignalIndices createAlertSignalIndices(const SharedPtr<TreeStoreTransactionContext>& context) const;

        void commitAlertSignalIndices(const AlertSignalIndices& alertSignalIndices, const SharedPtr<TreeStoreTransactionContext>& context);

        template<class T_Entity>
        MdibTreeStoreStatus insertOne(const NotNull<SharedPtr<T_Entity>>& entity,
                                      TreeStoreTransactionContext& transactionContext,
                                      SingleMap<T_Entity>& affectedEntities);

        template<class T_Entity>
        MdibTreeStoreResult<T_Entity> updateMany(const MdibEntityRange<T_Entity>& entities, UpdateStrategy updateStrategy);

        template<class T_Entity, class T_Range>
        MdibTreeStoreResult<T_Entity> insertMany(const T_Range& entities);

        template<class T_Entity>
        MdibTreeStoreStatus updateOne(UpdateStrategy updateStrategy,
                                      const NotNull<SharedPtr<T_Entity>>& entity,
                                      SingleMap<T_Entity>& entities,
                                      SingleMap<T_Entity>& affectedEntities,
                                      AlertSignalIndices& alertSignalIndices,
                                      const PresenceIndex& presenceIndex);

        template<class T_Entity>
        MdibTreeStoreStatus removeOne(const NotNull<SharedPtr<T_Entity>>& entity,
                                      TreeStoreTransactionContext& transactionContext,
                                      SingleMap<T_Entity>& affectedEntities);

        template<class T_Entity>
        static void staticEntityCheck();
};

}
}
}
