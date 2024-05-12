#pragma once

#include <Framework/Crypto/Private/Algorithm.h>
#include <Framework/Crypto/Private/MessageDigest/Hash.h>

#include <Framework/Encoding/Public/Bytes.h>
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
 * @brief Returns a hash for the given message using the given hash algorithm.
 *
 * @throw Whatever the used hash algoritm may throw.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestSha256.cpp hash
 *
 * @ingroup Crypto
 */
template <class Hash>
inline Encoding::Bytes hash(
    Hash& hash,
    Encoding::BytesView message)
{
    Impl::apply(hash, message);
    return hash.hash();
}

}
}
}
}
