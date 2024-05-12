#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Registry.h>
#include <Framework/Crypto/Public/Buffer.h>
#include <Framework/Crypto/Public/CipherFuncTypes.h>
#include <Framework/Crypto/Public/RandSourceFuncType.h>

#include <Framework/Crypto/Private/Log.h>

#include <utility>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Holds all hooks needed by the crypto library.
 *
 * @note This class shall only be used by platform integrators.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Registry
{
public:
    /**
     * @brief Forwarding typedef to @ref DFL::Crypto::Buffer.
     */
    using CryptoBuffer = Buffer;
    /**
     * @brief Type of hook for encryption.
     */
    using Encrypt = EncryptFunc;
    /**
     * @brief Type of hook for decryption.
     */
    using Decrypt = DecryptFunc;
    /**
     * @brief Type of hook for random source.
     */
    using RandSource = RandSourceFunc;
    /**
     * @brief Resets all hooks to default.
     *
     * Afterwards
     * - @ref DFL::Crypto::OpenSslUrng is used as a random source.
     * - DPAPI is used for encryption/decryption on Windows.
     * - an exception is thrown for encryption/decryption on any other platform.
     *
     * @snippet Crypto/Test/UnitTest/TestCryptoRegistry.cpp encryptDecryptHook
     * @snippet Crypto/Test/UnitTest/TestCryptoRegistry.cpp randSourceHook
     */
    static void resetHookFuncs();
    /**
     * @brief Getter for random source.
     */
    static RandSource randSource();
    /**
     * @brief Setter for encryption and decryption hooks.
     *
     * The here provided functions are used by the
     * @ref DFL::Crypto::Cipher::Symmetric::DeviceSpecific cipher. Thus they
     * should be cyber secure and device specific.
     *
     * @note Given functions are only effective if both are not null.
     *
     * @snippet Crypto/Test/UnitTest/TestCryptoRegistry.cpp encryptDecryptHook
     */
    static void encryptDecrypt(Encrypt encryptFunc, Decrypt decryptFunc);
    /**
     * @brief Setter for encryption and decryption hooks.
     *
     * The here provided functions are used by the
     * @ref DFL::Crypto::Cipher::Symmetric::DeviceSpecific cipher. Thus they
     * should be cyber secure and device specific.
     *
     * @snippet Crypto/Test/UnitTest/TestCryptoRegistry.cpp encryptDecryptCipher
     */
    template <class C>
    static void encryptDecrypt(C cipher)
    {
        DFL_CRYPTO_DEBUG_LOG_INFO(
            "default encrypt/decrypt hooks have been overwritten");
        Impl::Registry::encrypter(std::move(cipher.encrypter()));
        Impl::Registry::decrypter(std::move(cipher.decrypter()));
    }
    /**
     * @brief Sets the random source.
     *
     * The here provided function is used by the
     * @ref DFL::Crypto::RandomDevice. Thus it
     * should be a cyber secure random source.
     *
     * @note Given function is only effective if it is not null.
     *
     * @snippet Crypto/Test/UnitTest/TestCryptoRegistry.cpp randSourceHook
     */
    static void randSource(RandSource randSourceFunc);
};
}
}
