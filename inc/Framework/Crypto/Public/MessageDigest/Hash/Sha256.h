#pragma once

#include <Framework/Crypto/Private/Algorithm.h>
#include <Framework/Crypto/Private/MessageDigest/Hash.h>
#include <Framework/Crypto/Public/MessageDigest/Hash/BasicHash.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Hash
{
/**
 * @brief Provides hashing of bytes using SHA-256 algorithm.
 *
 * @details
 * - Generates hashes of length 256-bit
 * - For details on Secure Hash Algorithm 2 (SHA-2)
 *   see https://en.wikipedia.org/wiki/SHA-2
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestSha256.cpp initUpdateFinal
 *
 * @ingroup Crypto
 */
using Sha256 = BasicHash<Impl::Sha256Algorithm>;
}
}
}
}
