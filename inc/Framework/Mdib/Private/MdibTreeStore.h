#pragma once

#include <Framework/Mdib/Private/MdibEntityMap.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Private/MdibTreeStoreBase.h>

#include <functional>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Immutable MDIB tree that provides tree information and handle-based access.
 * @details Moreover it holds indices for fast handle selection.
 * @ingroup Mdib
 */
class MdibTreeStore: public MdibTreeStoreBase<MdibEntityMap>
{
    DFL_MDIB_IMMUTABLE(MdibTreeStore)

    public:
        MdibTreeStore() = default;
        MdibTreeStore(const MdibEntityMap& entityMap,
                      const MdibEntityMap& removedEntityMap,
                      const DFL::NotNull<SharedPtr<const ParentIndex>>& parentIndex,
                      const DFL::NotNull<SharedPtr<const PresenceIndex>>& presenceIndex,
                      const DFL::NotNull<SharedPtr<const AlertSignalIndexMap>>& alertSignalIndex);


};

inline MdibTreeStore::MdibTreeStore(const MdibEntityMap& entityMap,
                                    const MdibEntityMap& removedEntityMap,
                                    const DFL::NotNull<SharedPtr<const ParentIndex>>& parentIndex,
                                    const DFL::NotNull<SharedPtr<const PresenceIndex>>& presenceIndex,
                                    const DFL::NotNull<SharedPtr<const AlertSignalIndexMap>>& alertSignalIndex) :
    MdibTreeStoreBase(entityMap, removedEntityMap, parentIndex, presenceIndex, alertSignalIndex)
{
}

}
}
}
