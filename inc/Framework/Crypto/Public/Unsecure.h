#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Tag type for indicating unsecure functionality.
 *
 * @ingroup Crypto
 */
struct UnsecureTag {};
/**
 * @brief Instance of tag for indicating unsecure functionality.
 *
 * @ingroup Crypto
 */
const UnsecureTag unsecure;
}
}
