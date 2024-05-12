#pragma once

#include <memory>

namespace S31::Sdc
{

class LocalMdibAccess;

/**
 * @brief Shared pointer shortcut for \ref LocalMdibAccess.
 * @ingroup S31SdcDevice
 */
using LocalMdibAccessSharedPtr = std::shared_ptr<LocalMdibAccess>;

/**
 * @brief Unique pointer shortcut for \ref LocalMdibAccess.
 * @ingroup S31SdcDevice
 */
using LocalMdibAccessUniquePtr = std::unique_ptr<LocalMdibAccess>;

/**
 * @brief Weak pointer shortcut for \ref LocalMdibAccess.
 * @ingroup S31SdcDevice
 */
using LocalMdibAccessWeakPtr = std::weak_ptr<LocalMdibAccess>;

}
