#pragma once

namespace S31::Sdc
{

class MdibAccess;

/**
 * @brief Shared pointer shortcut for \ref MdibAccess.
 * @ingroup S31SdcCommon
 */
using MdibAccessSharedPtr = std::shared_ptr<MdibAccess>;

/**
 * @brief Unique pointer shortcut for \ref MdibAccess.
 * @ingroup S31SdcCommon
 */
using MdibAccessUniquePtr = std::unique_ptr<MdibAccess>;

/**
 * @brief Weak pointer shortcut for \ref MdibAccess.
 * @ingroup S31SdcCommon
 */
using MdibAccessWeakPtr = std::weak_ptr<MdibAccess>;

}
