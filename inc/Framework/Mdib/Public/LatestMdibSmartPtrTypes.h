#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

namespace DFL::Mdib
{
class LatestMdib;

/// @brief Definition of smart pointer LatestMdibSharedPtr
/// @ingroup Mdib
using LatestMdibSharedPtr = SharedPtr<LatestMdib>;

/// @brief Definition of smart pointer ConstLatestMdibSharedPtr
/// @ingroup Mdib
using ConstLatestMdibSharedPtr = SharedPtr<const LatestMdib>;

/// @brief Definition of smart pointer LatestMdibUniquePtr
/// @ingroup Mdib
using LatestMdibUniquePtr = UniquePtr<LatestMdib>;

/// @brief Definition of smart pointer ConstLatestMdibUniquePtr
/// @ingroup Mdib
using ConstLatestMdibUniquePtr = UniquePtr<const LatestMdib>;

/// @brief Definition of smart pointer LatestMdibWeakPtr
/// @ingroup Mdib
using LatestMdibWeakPtr = WeakPtr<LatestMdib>;

/// @brief Definition of smart pointer ConstLatestMdibWeakPtr
/// @ingroup Mdib
using ConstLatestMdibWeakPtr = WeakPtr<const LatestMdib>;

}
