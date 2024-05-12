#pragma once

#include <Framework/Crypto/Private/Cipher/EncDecCipher.h>
#include <Framework/Crypto/Public/Cipher/Symmetric/Aes256Cbc.h>

#include <Framework/Encoding/Public/Bytes.h>

namespace DFL
{
namespace Crypto
{
namespace Test
{
namespace Impl
{
inline Encoding::Bytes fakeKey()
{
    // using brace init would activate the init-list ctor
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return Encoding::Bytes(32, 0);
}

inline Encoding::Bytes fakeIv()
{
    // using brace init would activate the init-list ctor
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return Encoding::Bytes(16, 0);
}

class FakeEncrypter : public Cipher::Symmetric::Aes256Cbc::Encrypter
{
public:
    FakeEncrypter()
        : Cipher::Symmetric::Aes256Cbc::Encrypter{fakeKey(), fakeIv()}
    {
    }
};

class FakeDecrypter : public Cipher::Symmetric::Aes256Cbc::Decrypter
{
public:
    FakeDecrypter()
        : Cipher::Symmetric::Aes256Cbc::Decrypter{fakeKey(), fakeIv()}
    {
    }
};

using FakeCipher = Crypto::Impl::EncDecCipher<FakeEncrypter, FakeDecrypter>;
}
}
}
}
