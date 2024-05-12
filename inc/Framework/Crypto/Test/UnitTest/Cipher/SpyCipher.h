#pragma once

#include <Framework/Crypto/Private/Cipher/FuncCipher.h>

#include <string>

namespace DFLTest
{
namespace Crypto
{
namespace UnitTest
{
class SpyEncrypter : public ::DFL::Crypto::Impl::FuncCipher::Encrypter
{
public:
    explicit SpyEncrypter(std::string& calls);
    static std::string encryptCall();
};

class SpyDecrypter : public ::DFL::Crypto::Impl::FuncCipher::Decrypter
{
public:
    explicit SpyDecrypter(std::string& calls);
    static std::string decryptCall();
};

class SpyCipher
{
public:
    using Encrypter = SpyEncrypter;
    using Decrypter = SpyDecrypter;

    explicit SpyCipher(std::string& calls);
    Encrypter& encrypter();
    Decrypter& decrypter();
    static std::string encryptCall();
    static std::string decryptCall();

private:
    Encrypter m_encrypter;
    Decrypter m_decrypter;
};
}
}
}
