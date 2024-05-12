#pragma once

#include <Framework/Crypto/Private/Registry.h>
#include <Framework/Crypto/Public/PublicKey.h>

#include <Framework/Utils/Public/StateSaver.h>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief
 * Exchanges the public key used for role authorization list (RAL) verification
 * with a given public key.
 *
 * @snippet Crypto/Test/UnitTest/TestUtils/TestMockRalPublicKey.cpp stateSaving
 *
 * @ingroup Crypto
 */
class MockRalPublicKey
{
public:
    /**
     * @brief
     * Saves the current RAL public key and installs the given public key.
     */
    explicit MockRalPublicKey(const PublicKey& publicKey)
        : m_stateSaver{Crypto::Impl::Registry::ralPublicKey(),
                       [](const PublicKey& pk) {
                           Crypto::Impl::Registry::ralPublicKey(pk);
                       }}
    {
        Crypto::Impl::Registry::ralPublicKey(publicKey);
    }

private:
    StateSaver<PublicKey> m_stateSaver;
};
}
}
}
