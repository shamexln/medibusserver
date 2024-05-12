#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Public/Model/Handle.h>

#include <algorithm>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/// @brief Insert the entities from the range into the map (of course: map's key == entity's handle)
/// @ingroup Mdib
template<class T_Entity>
inline void insert(std::map<DFL::Mdib::BasicHandle<T_Entity>, NotNull<SharedPtr<T_Entity>>>& destinationMap,
              const MdibEntityRange<T_Entity>& sourceRange)
{
    std::for_each(sourceRange.begin(), sourceRange.end(),
        [&] (const NotNull<SharedPtr<T_Entity>> &e)
        {
            destinationMap.insert(std::make_pair(e->handle(), e));
        });
}

}
}
}
