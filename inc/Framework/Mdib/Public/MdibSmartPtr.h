#pragma once

#include <memory>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Definition for a shared_ptr type, currently from std namespace.
 * @ingroup Mdib
 */
#define DFL_MDIB_SHARED_PTR \
        std::shared_ptr

/**
 * @brief Definition for a unique_ptr type, currently from std namespace.
 * @ingroup Mdib
 */
#define DFL_MDIB_UNIQUE_PTR \
        std::unique_ptr

/**
 * @brief Definition for a weak_ptr type, currently from std namespace.
 * @ingroup Mdib
 */
#define DFL_MDIB_WEAK_PTR \
        std::weak_ptr

/**
 * @brief Definition for a make_shared function, currently from std namespace.
 * @ingroup Mdib
 */
#define DFL_MDIB_MAKE_SHARED \
        std::make_shared

/**
 * @brief Definition for a make_unique function, currently from std namespace.
 * @ingroup Mdib
 */
#define DFL_MDIB_MAKE_UNIQUE \
        std::make_unique

/**
 * @brief Definition for a const_pointer_cast, currently from std namespace.
 * @ingroup Mdib
 */
#define DFL_MDIB_CONST_POINTER_CAST \
        std::const_pointer_cast

} /* namespace Mdib */
} /* namespace DFL */
