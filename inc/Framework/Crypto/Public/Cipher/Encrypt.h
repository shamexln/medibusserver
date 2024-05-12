#pragma once

#include <Framework/Crypto/Private/Algorithm.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL::Crypto::Cipher
{
/**
 * @brief
 * Returns an encrypted version for the given message using the given encrypter
 * algorithm.
 *
 * @throw Whatever the used encrypter algoritm may throw.
 *
 * @snippet Crypto/Test/UnitTest/Cipher/TestAes.cpp encrypt
 *
 * @ingroup Crypto
 */
template <class Encrypter>
inline Encoding::Bytes encrypt(Encrypter& encrypter,
                               Encoding::BytesView message)
{
    Crypto::Impl::apply(encrypter, message);
    return encrypter.encrypted();
}
}
