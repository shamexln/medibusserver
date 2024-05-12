#pragma once

#include <Framework/Crypto/Private/Cipher/EncDecCipher.h>
#include <Framework/Crypto/Private/Cipher/FuncCipher.h>

namespace DFLTest
{
namespace Crypto
{
namespace UnitTest
{
class NoEncrypter : public ::DFL::Crypto::Impl::FuncCipher::Encrypter
{
public:
    NoEncrypter();
};

class NoDecrypter : public ::DFL::Crypto::Impl::FuncCipher::Decrypter
{
public:
    NoDecrypter();
};

using NoCipher = ::DFL::Crypto::Impl::EncDecCipher<NoEncrypter, NoDecrypter>;
}
}
}
