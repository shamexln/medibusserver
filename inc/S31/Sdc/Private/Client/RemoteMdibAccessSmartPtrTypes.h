#pragma once

#include <memory>

namespace S31::Sdc::Impl
{
class RemoteMdibAccess;

/**
 * @brief Shared pointer shortcut for \ref RemoteMdibAccess.
 * @ingroup S31SdcDevice
 */
using RemoteMdibAccessSharedPtr = std::shared_ptr<RemoteMdibAccess>;

/**
 * @brief Unique pointer shortcut for \ref RemoteMdibAccess.
 * @ingroup S31SdcDevice
 */
using RemoteMdibAccessUniquePtr = std::unique_ptr<RemoteMdibAccess>;

/**
 * @brief Weak pointer shortcut for \ref RemoteMdibAccess.
 * @ingroup S31SdcDevice
 */
using RemoteMdibAccessWeakPtr = std::weak_ptr<RemoteMdibAccess>;

}
