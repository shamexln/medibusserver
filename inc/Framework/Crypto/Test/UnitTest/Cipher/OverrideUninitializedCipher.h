#pragma once

#include <Framework/Config/Public/Config.h>
#if defined(DFL_CONFIG_OS_WIN32)
#include <Framework/Crypto/Private/Cipher/Dpapi.h>
#else
#include <Framework/Crypto/Test/Private/FakeCipher.h>
#endif
#include <Framework/Crypto/Private/Cipher/EncDecCipher.h>

namespace DFLTest
{
namespace Crypto
{
namespace UnitTest
{
#if defined(DFL_CONFIG_OS_WIN32)
using OverrideUnitializedEncrypter = ::DFL::Crypto::Impl::DpapiEncrypter;
using OverrideUnitializedDecrypter = ::DFL::Crypto::Impl::DpapiDecrypter;
#else
using OverrideUnitializedEncrypter =
    ::DFL::Crypto::Test::Impl::FakeCipher::Encrypter;
using OverrideUnitializedDecrypter =
    ::DFL::Crypto::Test::Impl::FakeCipher::Decrypter;
#endif
using OverrideUninitializedCipher =
    ::DFL::Crypto::Impl::EncDecCipher<OverrideUnitializedEncrypter,
                                    OverrideUnitializedDecrypter>;
}
}
}
