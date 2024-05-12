#pragma once

#include <memory>

namespace S31::Sdc
{

class Mdib;

/**
 * @brief Shared pointer shortcut for \ref Mdib.
 * @ingroup S31SdcCommon
 */
using MdibSharedPtr = std::shared_ptr<Mdib>;

/**
 * @brief Unique pointer shortcut for \ref Mdib.
 * @ingroup S31SdcCommon
 */
using MdibUniquePtr = std::unique_ptr<Mdib>;

/**
 * @brief Weak pointer shortcut for \ref Mdib.
 * @ingroup S31SdcCommon
 */
using MdibWeakPtr = std::weak_ptr<Mdib>;

}
