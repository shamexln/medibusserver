#pragma once

#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Hash
{
/**
 * @brief Compares the given hashes.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestSha256.cpp hash
 *
 * @ingroup Crypto
 */
inline bool verify(
    Encoding::BytesView expectedHash,
    Encoding::BytesView actualHash)
{
    return expectedHash == actualHash;
}
}
}
}
}
