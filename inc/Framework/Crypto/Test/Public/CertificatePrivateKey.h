#pragma once

#include <Framework/Crypto/Private/Store/Store.h>
#include <Framework/Crypto/Public/PrivateKey.h>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief Generates a private key of same type as used in DFL::Crypto::Store.
 *
 * @ingroup Crypto
 */
inline PrivateKey generateCertificatePrivateKey()
{
    return Crypto::Impl::Store::generateKey();
}
}
}
}
