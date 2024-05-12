#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Type of a cryptographic key.
 *
 * @ingroup Crypto
 */
enum class KeyType
{
    Unknown,
    RSA,
    EC
};

DFL_ENUM_CLASS_STREAM_OPERATOR(KeyType, (Unknown)(RSA)(EC))
}
}
