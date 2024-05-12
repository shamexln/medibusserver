#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

#include <functional>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
class DFL_CRYPTO_EXPIMP FuncEncrypter
{
public:
    using Func = std::function<Encoding::Bytes(const Encoding::Bytes&)>;

    explicit FuncEncrypter(Func e);
    void init();
    void update(Encoding::BytesView bytes);
    void final();
    Encoding::Bytes encrypted();

private:
    Func m_encrypt;
    Encoding::Bytes m_data{};
};

class DFL_CRYPTO_EXPIMP FuncDecrypter
{
public:
    using Func = std::function<Encoding::Bytes(const Encoding::Bytes&)>;

    explicit FuncDecrypter(Func d);
    void init();
    void update(Encoding::BytesView bytes);
    void final();
    Encoding::Bytes decrypted();

private:
    Func m_decrypt;
    Encoding::Bytes m_data{};
};

class DFL_CRYPTO_EXPIMP FuncCipher
{
public:
    using EncryptFunc = FuncEncrypter::Func;
    using DecryptFunc = FuncDecrypter::Func;
    using Encrypter = FuncEncrypter;
    using Decrypter = FuncDecrypter;

    FuncCipher(EncryptFunc e, DecryptFunc d);
    Encrypter& encrypter();
    Decrypter& decrypter();

private:
    Encrypter m_encrypter;
    Decrypter m_decrypter;
};
}
}
}
