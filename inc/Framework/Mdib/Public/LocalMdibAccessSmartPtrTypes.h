#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

namespace DFL
{
namespace Mdib
{
class LocalMdibAccess;

/// @brief Definition of smart pointer LocalMdibAccessSharedPtr
/// @ingroup Mdib
using LocalMdibAccessSharedPtr = SharedPtr<LocalMdibAccess>;

/// @brief Definition of smart pointer ConstLocalMdibAccessSharedPtr
/// @ingroup Mdib
using ConstLocalMdibAccessSharedPtr = SharedPtr<const LocalMdibAccess>;

/// @brief Definition of smart pointer LocalMdibAccessUniquePtr
/// @ingroup Mdib
using LocalMdibAccessUniquePtr = UniquePtr<LocalMdibAccess>;

/// @brief Definition of smart pointer ConstLocalMdibAccessUniquePtr
/// @ingroup Mdib
using ConstLocalMdibAccessUniquePtr = UniquePtr<const LocalMdibAccess>;

/// @brief Definition of smart pointer LocalMdibAccessWeakPtr
/// @ingroup Mdib
using LocalMdibAccessWeakPtr = WeakPtr<LocalMdibAccess>;

/// @brief Definition of smart pointer ConstLocalMdibAccessWeakPtr
/// @ingroup Mdib
using ConstLocalMdibAccessWeakPtr = WeakPtr<const LocalMdibAccess>;

} /* namespace Mdib */
} /* namespace DFL */
