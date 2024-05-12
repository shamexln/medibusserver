#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL::Crypto::Cipher::Symmetric
{
/**
 * @brief The data encrypted with this API should only be decryptable on the
 * same device as it has been encrypted.
 *
 * @snippet Crypto/Test/Unittest/Cipher/TestDeviceSpecific.cpp EncryptDecrypt
 *
 * It uses a platform dependent default encryption algorithm or the one that has
 * been injected via @ref DFL::Crypto::Registry::encryptDecrypt.
 *
 * - If Windows is detected DPAPI is used.
 * - On all other platforms an exception is thrown by default
 *   (since DFL has no secure default for these).
 *   Use @ref DFL::Crypto::Registry::encryptDecrypt to inject an algorithm that
 *   fits your requirements.
 *
 * @note If your application is based on S16 a cryptographical secure cipher is
 * used which is provided by the hardware.
 *
 * @note Depending on the concrete OS and/or the provided hardware
 * there might be better cipher capabilities available than the one provided
 * here. These better algorithms can be injected into this crypto lib via
 * @ref DFL::Crypto::Registry::encryptDecrypt.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP DeviceSpecific
{
public:
    /**
     * @brief Device specific encrypter.
     */
    class DFL_CRYPTO_EXPIMP Encrypter
    {
    public:
        /**
         * @brief Setup internal context.
         */
        void init();
        /**
         * @brief Adds the given bytes to the internal context.
         *
         * @pre init has been called.
         */
        void update(Encoding::BytesView bytes);
        /**
         * @brief Encrypts data.
         *
         * Uses encrypt function injected
         * via @ref DFL::Crypto::Registry::encryptDecrypt.
         *
         * @pre init and update have been called.
         *
         * @post The result can be obtained from the encrypted function.
         *
         * @throw std::runtime_error in case of an error.
         */
        void final();
        /**
         * @brief Returns the calculated encrypted data.
         *
         * @note
         * Calling this function clears the internal result, i. e. a second call
         * returns empty.
         */
        Encoding::Bytes encrypted();
    };
    /**
     * @brief Device specific encrypter.
     */
    class DFL_CRYPTO_EXPIMP Decrypter
    {
    public:
        /**
         * @brief Setup internal context.
         */
        void init();
        /**
         * @brief Adds the given bytes to the internal context.
         *
         * @pre init has been called.
         */
        void update(Encoding::BytesView bytes);
        /**
         * @brief Decrypts data.
         *
         * Uses decrypt function injected
         * via @ref DFL::Crypto::Registry::encryptDecrypt.
         *
         * @pre init and update have been called.
         *
         * @post The result can be obtained from the decrypted function.
         *
         * @throw std::runtime_error in case of an error.
         */
        void final();
        /**
         * @brief Returns the calculated decrypted data.
         *
         * @note
         * Calling this function clears the internal result, i. e. a second call
         * returns empty.
         */
        Encoding::Bytes decrypted();
    };
    /**
     * @brief Returns a reference to the encrypter.
     */
    Encrypter& encrypter();
    /**
     * @brief Returns a reference to the decrypter.
     */
    Decrypter& decrypter();

private:
    Encrypter m_encrypter{};
    Decrypter m_decrypter{};
};
}
