#pragma once

#include <Framework/Mdib/Private/MdibTreeStoreBuilder.h>
#include <Framework/Mdib/Private/WriteResult.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/WriteResult.h>

#include <Framework/Utils/Public/StrongTypedef.h>

#include <stdexcept>
#include <type_traits>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
enum class RemovedEntities
{
    Yes,
    No
};

enum class UpdatedEntities
{
    Yes,
    No
};

enum class InsertedEntities
{
    Yes,
    No
};

template<class... T1>
bool hasEntities(const MdibChangeSet& changes, RemovedEntities removed, UpdatedEntities updated, InsertedEntities inserted, typename std::enable_if<sizeof...(T1) == 0>::type* = nullptr);

template<class T1, class... T2>
bool hasEntities(const MdibChangeSet& changes, RemovedEntities removed, UpdatedEntities updated, InsertedEntities inserted);

/**
 * @brief Helper class to apply operations on a set of objects that is obtained by template parameters.
 * @ingroup Mdib
 */
template<class T_MdibDetails>
class MdibAccessHelper
{
    public:

        template<class... T1>
        static WriteResult updateStates(const MdibChangeSet& changes,
                                       MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                       MdibChangeSet& changeSetResult,
                                       typename std::enable_if<sizeof...(T1) == 0>::type* = nullptr);

        template<class T1, class... T2>
        static WriteResult updateStates(const MdibChangeSet& changes,
                                       MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                       MdibChangeSet& changeSetResult);

        template<class... T1>
        static WriteResult insertEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult,
                                             OrderedHandleRange::IteratorType& orderIt,
                                             const OrderedHandleRange::IteratorType& orderEnd,
                                             typename std::enable_if<sizeof...(T1) == 0>::type* = nullptr);
        template<class T1, class... T2>
        static WriteResult insertEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult,
                                             OrderedHandleRange::IteratorType& orderIt,
                                             const OrderedHandleRange::IteratorType& orderEnd);

        template<class... T1>
        static WriteResult insertEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult,
                                             typename std::enable_if<sizeof...(T1) == 0>::type* = nullptr);
        template<class T1, class... T2>
        static WriteResult insertEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult);

        template<class... T1>
        static WriteResult updateEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult,
                                             typename std::enable_if<sizeof...(T1) == 0>::type* = nullptr);
        template<class T1, class... T2>
        static WriteResult updateEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult);

        template<class... T1>
        static WriteResult removeEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult,
                                             typename std::enable_if<sizeof...(T1) == 0>::type* = nullptr);
        template<class T1, class... T2>
        static WriteResult removeEntities(const MdibChangeSet& changes,
                                             MdibTreeStoreBuilder<T_MdibDetails>& tsBuilder,
                                             MdibChangeSet& changeSetResult);

    private:
        static WriteResult accumulate(
            WriteResult first,
            WriteResult second);
        static MdibAccessHelperWriteStatus fromTreeStoreStatus(MdibTreeStoreStatus treeStoreStatus);
};

}
}
}
