#pragma once

#include <Framework/Mdib/Public/MdibSmartPtr.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief DFL MDIB shared pointer type.
 * @ingroup Mdib
 */
template<class T>
using SharedPtr = std::shared_ptr<T>;

/**
 * @brief DFL MDIB weak pointer type.
 * @ingroup Mdib
 */
template<class T>
using WeakPtr = std::weak_ptr<T>;

/**
 * @brief DFL MDIB unique pointer type.
 * @ingroup Mdib
 */
template<class T>
using UniquePtr = std::unique_ptr<T>;

}
}
