#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

namespace DFL
{
namespace Mdib
{
class MdibAccess;

/// @brief Definition of smart pointer MdibAccessSharedPtr
/// @ingroup Mdib
using MdibAccessSharedPtr = SharedPtr<MdibAccess>;

/// @brief Definition of smart pointer ConstMdibAccessSharedPtr
/// @ingroup Mdib
using ConstMdibAccessSharedPtr = SharedPtr<const MdibAccess>;

/// @brief Definition of smart pointer MdibAccessUniquePtr
/// @ingroup Mdib
using MdibAccessUniquePtr = UniquePtr<MdibAccess>;

/// @brief Definition of smart pointer ConstMdibAccessUniquePtr
/// @ingroup Mdib
using ConstMdibAccessUniquePtr = UniquePtr<const MdibAccess>;

/// @brief Definition of smart pointer MdibAccessWeakPtr
/// @ingroup Mdib
using MdibAccessWeakPtr = WeakPtr<MdibAccess>;

/// @brief Definition of smart pointer ConstMdibAccessWeakPtr
/// @ingroup Mdib
using ConstMdibAccessWeakPtr = WeakPtr<const MdibAccess>;

} /* namespace Mdib */
} /* namespace DFL */
