#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

namespace DFL
{
namespace Mdib
{
class RemoteMdibAccess;

/// @brief Definition of smart pointer RemoteMdibAccessSharedPtr
/// @ingroup Mdib
using RemoteMdibAccessSharedPtr = SharedPtr<RemoteMdibAccess>;

/// @brief Definition of smart pointer ConstRemoteMdibAccessSharedPtr
/// @ingroup Mdib
using ConstRemoteMdibAccessSharedPtr = SharedPtr<const RemoteMdibAccess>;

/// @brief Definition of smart pointer RemoteMdibAccessUniquePtr
/// @ingroup Mdib
using RemoteMdibAccessUniquePtr = UniquePtr<RemoteMdibAccess>;

/// @brief Definition of smart pointer ConstRemoteMdibAccessUniquePtr
/// @ingroup Mdib
using ConstRemoteMdibAccessUniquePtr = UniquePtr<const RemoteMdibAccess>;

/// @brief Definition of smart pointer RemoteMdibAccessWeakPtr
/// @ingroup Mdib
using RemoteMdibAccessWeakPtr = WeakPtr<RemoteMdibAccess>;

/// @brief Definition of smart pointer ConstRemoteMdibAccessWeakPtr
/// @ingroup Mdib
using ConstRemoteMdibAccessWeakPtr = WeakPtr<const RemoteMdibAccess>;

} /* namespace Mdib */
} /* namespace DFL */
