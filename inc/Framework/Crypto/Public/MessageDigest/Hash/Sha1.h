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
 * @brief Provides hashing of bytes using SHA-1 algorithm.
 *
 * @details
 * - Generates hashes of length 160-bit
 * - For details on Secure Hash Algorithm 1 (SHA-1)
 *   see https://en.wikipedia.org/wiki/SHA-1
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestSha1.cpp initUpdateFinal
 *
 * @ingroup Crypto
 */
using Sha1 = BasicHash<Impl::Sha1Algorithm>;
}
}
}
}
