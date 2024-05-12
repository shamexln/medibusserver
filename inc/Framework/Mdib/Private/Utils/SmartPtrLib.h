#pragma once

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Mdib/Public/MdibSmartPtr.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <memory>

namespace DFL
{
namespace Mdib
{

/**
 * @brief DFL MDIB shared pointer creation.
 * @ingroup Mdib
 */
template<typename T, typename... Args>
inline NotNull<SharedPtr<T>> makeShared(Args&&... args)
{
    return asNotNull(DFL_MDIB_MAKE_SHARED<T>(std::forward<Args>(args)...));
}

/**
 * @brief DFL MDIB unique pointer creation.
 * @ingroup Mdib
 */
template<typename T, typename... Args>
inline NotNull<UniquePtr<T>> makeUnique(Args&&... args)
{
    return asNotNull(DFL_MDIB_MAKE_UNIQUE<T>(std::forward<Args>(args)...));
}

}
}
