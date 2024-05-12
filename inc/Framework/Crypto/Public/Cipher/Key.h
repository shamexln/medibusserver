#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Utils/Public/Buffer.h>

namespace DFL
{
namespace Crypto
{
namespace Cipher
{
/**
 * @brief An immutable cipher key of fixed length.
 * @tparam Size of key in bits
 * @ingroup Crypto
 */
template<std::size_t bits>
class Key : public ::DFL::Buffer<(bits / 8)>
{
public:
    using ::DFL::Buffer<(bits / 8)>::Buffer;
    static_assert(bits % 8 == 0, "number of bits has to be divisible by 8");
    static constexpr auto Bits = bits; ///< Size of key in bits
};
}
}
}
