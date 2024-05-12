#pragma once

namespace DFL
{
namespace Crypto
{
namespace Impl
{
template <class Enc, class Dec>
class EncDecCipher
{
public:
    using Encrypter = Enc;
    using Decrypter = Dec;

    Encrypter& encrypter()
    {
        return m_encrypter;
    }
    Decrypter& decrypter()
    {
        return m_decrypter;
    }

private:
    Encrypter m_encrypter{};
    Decrypter m_decrypter{};
};
}
}
}
