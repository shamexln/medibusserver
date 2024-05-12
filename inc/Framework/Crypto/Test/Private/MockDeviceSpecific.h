#pragma once

#include <Framework/Crypto/Private/Cipher/Decrypter.h>
#include <Framework/Crypto/Private/Cipher/Encrypter.h>
#include <Framework/Crypto/Private/Registry.h>
#include <Framework/Crypto/Public/Registry.h>

#include <utility>

namespace DFL
{
namespace Crypto
{
namespace Test
{
namespace Impl
{
class MockDeviceSpecific
{
private:
    using ImplRegistry = ::DFL::Crypto::Impl::Registry;

public:
    template <class Cipher>
    MockDeviceSpecific(Cipher cipher)
        : m_savedEncrypter{std::move(ImplRegistry::encrypter())}
        , m_savedDecrypter{std::move(ImplRegistry::decrypter())}

    {
        ::DFL::Crypto::Registry::encryptDecrypt(std::move(cipher));
    }

    ~MockDeviceSpecific()
    {
        try
        {
            ImplRegistry::encrypter(std::move(m_savedEncrypter));
            ImplRegistry::decrypter(std::move(m_savedDecrypter));
        }
        catch (...)
        {
        }
    }

private:
    ::DFL::Crypto::Impl::Encrypter m_savedEncrypter;
    ::DFL::Crypto::Impl::Decrypter m_savedDecrypter;
};
}
}
}
}
