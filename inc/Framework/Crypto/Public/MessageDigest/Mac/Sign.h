#pragma once

#include <Framework/Crypto/Private/Algorithm.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Mac
{
/**
 * @brief
 * Creates a MAC for the given message using the given mac algorithm.
 *
 * @throw Whatever the used mac algoritm may throw.
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestHmac.cpp sign
 *
 * @ingroup Crypto
 */
template <class Mac>
inline Encoding::Bytes sign(
    Mac& mac,
    Encoding::BytesView message)
{
    Impl::apply(mac, message);
    return mac.mac();
}
}
}
}
}
