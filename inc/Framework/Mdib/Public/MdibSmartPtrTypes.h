#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

namespace DFL
{
namespace Mdib
{
class Mdib;

/// @brief Definition of smart pointer MdibSharedPtr
/// @ingroup Mdib
using MdibSharedPtr = SharedPtr<Mdib>;

/// @brief Definition of smart pointer ConstMdibSharedPtr
/// @ingroup Mdib
using ConstMdibSharedPtr = SharedPtr<const Mdib>;

/// @brief Definition of smart pointer MdibUniquePtr
/// @ingroup Mdib
using MdibUniquePtr = UniquePtr<Mdib>;

/// @brief Definition of smart pointer ConstMdibUniquePtr
/// @ingroup Mdib
using ConstMdibUniquePtr = UniquePtr<const Mdib>;

/// @brief Definition of smart pointer MdibWeakPtr
/// @ingroup Mdib
using MdibWeakPtr = WeakPtr<Mdib>;

/// @brief Definition of smart pointer ConstMdibWeakPtr
/// @ingroup Mdib
using ConstMdibWeakPtr = WeakPtr<const Mdib>;

} /* namespace Mdib */
} /* namespace DFL */
