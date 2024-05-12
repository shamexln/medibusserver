#pragma once

#include <Framework/Encoding/Public/Byte.h>

#include <vector>

namespace DFL
{
namespace Encoding
{
/**
 * @brief Holds a contiguous sequence of raw bytes.
 *
 * @ingroup Encoding
 */
using Bytes = std::vector<Byte>;
}
}
