#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Buffer.h>
#include <Framework/Crypto/Public/Cipher/Cipher.h>
#include <Framework/Crypto/Public/Cipher/Iv.h>
#include <Framework/Crypto/Public/Cipher/Key.h>

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Encoding/Public/Bytes.h>

namespace DFL
{
namespace Crypto
{
namespace Cipher
{
/**
 * @brief DEPRECATED
 *
 * Use DFL::Crypto::Cipher::Symmetric::Aes256Cbc instead.
 *
 * @ingroup Crypto
 */
class DFL_ATTRIBUTE_DEPRECATED("DFL::Crypto::Cipher::Symmetric::Aes256Cbc")
    DFL_CRYPTO_EXPIMP Aes256Cbc : public Cipher
{
public:
    using Key = ::DFL::Crypto::Cipher::Key<256>; ///< DEPRECATED
    using Iv = ::DFL::Crypto::Cipher::Iv<128>;   ///< DEPRECATED

    /**
     * @brief DEPRECATED
     */
    Aes256Cbc(const Key& key, const Iv& iv);
    /**
     * @brief DEPRECATED
     */
    Buffer encrypt(const Buffer& decryptedBuffer) const override;
    /**
     * @brief DEPRECATED
     */
    Buffer decrypt(const Buffer& encryptedBuffer) const override;

private:
    Encoding::Bytes m_key;
    Encoding::Bytes m_iv;
};
}
}
}
