#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>

namespace DFL
{
namespace Mdib
{
namespace Test
{

/**
 * @brief Visitor to extract the untyped handle out of a child variant.
 * @ingroup Mdib
 */
struct GetHandleVisitor
{
        /// @brief Visitor operator that returns the handle of the given entity as untyped handle.
        template<class T_EntityPtr>
        DFL::Mdib::Handle operator()(const T_EntityPtr& entity) const
        {
            return toHandle(entity->handle());
        }
};

}
}
}
