#pragma once

#include <Framework/Crypto/Test/Private/FakeCipher.h>
#include <Framework/Crypto/Test/Private/MockDeviceSpecific.h>

#include <utility>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief
 * Exchanges the cipher used in Crypto::Store with a given cipher.
 *
 * @details
 * After destroying the instance, the previous cipher will be restored.
 *
 * @note
 * Do not call @ref DFL::Crypto::Environment::init after creating an instance.
 * Otherwise the default services will be used again!
 *
 * @snippet Crypto/Test/UnitTest/TestUtils/TestMockDeviceSpecific.cpp exchange
 *
 * @ingroup Crypto
 */
class MockDeviceSpecific : private Impl::MockDeviceSpecific
{

public:
    /**
     * @brief Injects a fake cipher.
     */
    MockDeviceSpecific()
        : Impl::MockDeviceSpecific{Impl::FakeCipher{}}
    {
    }
    /**
     * @brief Injects given cipher.
     */
    template <class Cipher>
    explicit MockDeviceSpecific(Cipher cipher)
        : Impl::MockDeviceSpecific{std::move(cipher)}
    {
    }
};
}
}
}
