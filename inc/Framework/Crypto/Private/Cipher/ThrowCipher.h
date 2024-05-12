#pragma once

#include <Framework/Crypto/Private/Cipher/EncDecCipher.h>

#include <Framework/Crypto/Public/Cipher/Decrypt.h>
#include <Framework/Crypto/Public/Cipher/Encrypt.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

#include <stdexcept>
#include <string>
#include <utility>

namespace DFL
{
namespace Encoding
{
class BytesView;
}
namespace Crypto
{
namespace Impl
{
inline std::string throwCipherMessage()
{
    return "encrypt/decrypt not set, use "
           "DFL::Crypto::Registry::encryptDecrypt::set for setting";
}

template <class Exception>
class ThrowEncrypter
{
public:
    static void init()
    {
        throw Exception{throwCipherMessage()};
    }
    static void update(Encoding::BytesView /*bytes*/)
    {
        throw Exception{throwCipherMessage()};
    }
    static void final()
    {
        throw Exception{throwCipherMessage()};
    }
    static Encoding::Bytes encrypted()
    {
        throw Exception{throwCipherMessage()};
    }
};

template <class Exception>
class ThrowDecrypter
{
public:
    static void init()
    {
        throw Exception{throwCipherMessage()};
    }
    static void update(Encoding::BytesView /*bytes*/)
    {
        throw Exception{throwCipherMessage()};
    }
    static void final()
    {
        throw Exception{throwCipherMessage()};
    }
    static Encoding::Bytes decrypted()
    {
        throw Exception{throwCipherMessage()};
    }
};

template <class Exception>
using ThrowCipher =
    EncDecCipher<ThrowEncrypter<Exception>, ThrowDecrypter<Exception>>;
}
}
}
