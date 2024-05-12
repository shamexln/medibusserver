#pragma once

#include <Framework/Crypto/Private/Cipher/Cipher.h>
#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL::Crypto::Cipher::Symmetric
{
/**
 * @brief Provides encryption/decryption of bytes based on AES-256 in CBC mode.
 *
 * @details
 * - For details on Advanced Encryption Standard (AES),
 *   see https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
 * - For details on Block Chaining (CBC),
 *   see https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @snippet Crypto/Sample/Sample.cpp Aes256Cbc
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Aes256Cbc
{
public:
    /**
     * @brief Provides a encrypter algorithm.
     *
     * @ingroup Crypto
     */
    class DFL_CRYPTO_EXPIMP Encrypter
    {
    public:
        /**
         * @brief Creates an encrypter with the given key and iv.
         *
         * @throw std::runtime_error in case of an error.
         */
        explicit Encrypter(Encoding::BytesView key, Encoding::BytesView iv);
        /**
         * @brief Setup internal context.
         *
         * @throw std::runtime_error in case of an error.
         */
        void init();
        /**
         * @brief Adds the given bytes to the internal context.
         *
         * @pre init has been called.
         *
         * @throw std::runtime_error in case of an error.
         */
        void update(Encoding::BytesView bytes);
        /**
         * @brief Creates the encrypted data.
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

    private:
        Impl::Cipher m_cipher;
    };
    /**
     * @brief Provides a decrypter algorithm.
     *
     * @ingroup Crypto
     */
    class DFL_CRYPTO_EXPIMP Decrypter
    {
    public:
        /**
         * @brief Creates a decrypter with the given key and iv.
         *
         * @throw std::runtime_error in case of an error.
         */
        explicit Decrypter(Encoding::BytesView key, Encoding::BytesView iv);
        /**
         * @brief Setup internal context.
         *
         * @throw std::runtime_error in case of an error.
         */
        void init();
        /**
         * @brief Adds the given bytes to the internal context.
         *
         * @pre init has been called.
         *
         * @throw std::runtime_error in case of an error.
         */
        void update(Encoding::BytesView bytes);
        /**
         * @brief Creates the decrypted data.
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

    private:
        Impl::Cipher m_cipher;
    };
    /**
     * @brief Creates a cipher with the given key and iv.
     *
     * @throw whatever the ctors of Encrypter and Decrypter may throw.
     */
    explicit Aes256Cbc(Encoding::BytesView key, Encoding::BytesView iv);
    /**
     * @brief Returns a reference to the encrypter.
     */
    Encrypter& encrypter();
    /**
     * @brief Returns a reference to the decrypter.
     */
    Decrypter& decrypter();

private:
    Encrypter m_encrypter;
    Decrypter m_decrypter;
};
}
