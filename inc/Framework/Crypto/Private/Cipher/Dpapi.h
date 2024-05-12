#pragma once

#include <Framework/Config/Public/Config.h>
#if defined(DFL_CONFIG_OS_WIN32)

#include <Framework/Crypto/Private/Cipher/EncDecCipher.h>
#include <Framework/Crypto/Private/Cipher/FuncCipher.h>
#include <Framework/Crypto/Private/ExpImp.h>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
/*
 * Holds functions for encrypting/decrypting buffers using the Windows DPAPI.
 *
 * Warning:
 * If hibernation is used these functions do not work.
 * Well they will work for about three months and then the crypto keys will get
 * renewed and if hibernation kicks in the new key is lost and encrypted data
 * can nolonger be decrypted.
 *
 * Note: Requires crypt32.[lib,dll]
 */

class DFL_CRYPTO_EXPIMP DpapiEncrypter : public FuncCipher::Encrypter
{
public:
    DpapiEncrypter();
};

class DFL_CRYPTO_EXPIMP DpapiDecrypter : public FuncCipher::Decrypter
{
public:
    DpapiDecrypter();
};

using Dpapi = EncDecCipher<DpapiEncrypter, DpapiDecrypter>;
}
}
}

#endif
