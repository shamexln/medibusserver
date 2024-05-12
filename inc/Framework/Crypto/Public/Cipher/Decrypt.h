#pragma once

#include <Framework/Crypto/Private/Algorithm.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL::Crypto::Cipher
{
/**
 * @brief
 * Returns a decrypted version of the given encrypted bytes using the given
 * decrypter algorithm.
 *
 * @throw Whatever the used decrypter algoritm may throw.
 *
 * @snippet Crypto/Test/UnitTest/Cipher/TestAes.cpp decrypt
 *
 * @ingroup Crypto
 */
template <class Decrypter>
inline Encoding::Bytes decrypt(Decrypter& decrypter,
                               Encoding::BytesView encrypted)
{
    Crypto::Impl::apply(decrypter, encrypted);
    return decrypter.decrypted();
}
}
