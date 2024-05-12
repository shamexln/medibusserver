#pragma once

#include <Framework/Utils/Public/TypesafeEnum.h>

/**
 * @ingroup Utils
 * @{
 *
 * @file
 * @brief Declares and defines typesafe tri-state enum values by using the
 * DFL_TYPESAFE_ENUM macro from TypesafeEnum.h.
 */
namespace DFL
{

DFL_TYPESAFE_ENUM(TriState,
                  (Off)
                  (On)
                  (Undefined)
                 )

}
/** @} */
