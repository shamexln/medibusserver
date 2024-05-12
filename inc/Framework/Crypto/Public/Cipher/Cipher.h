#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Buffer.h>

#include <Framework/Config/Public/Attributes.h>

namespace DFL
{
namespace Crypto
{
namespace Cipher
{
/**
 * @brief DEPRECATED Use a cipher from namespace DFL::Crypto::Cipher::Symmetric
 * instead.
 *
 * @deprecated Use a cipher from namespace DFL::Crypto::Cipher::Symmetric
 * instead.
 *
 * @ingroup Crypto
 */
class DFL_ATTRIBUTE_DEPRECATED(
    "use one from namespace DFL::Crypto::Cipher::Symmetric::*")
    DFL_CRYPTO_EXPIMP Cipher
{
public:
    virtual ~Cipher() = default;
    /**
     * @brief DEPRECATED
     */
    virtual Buffer encrypt(const Buffer& decryptedBuffer) const = 0;
    /**
     * @brief DEPRECATED
     */
    virtual Buffer decrypt(const Buffer& encryptedBuffer) const = 0;
};
}
}
}
