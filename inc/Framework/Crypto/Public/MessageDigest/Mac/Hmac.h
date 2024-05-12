#pragma once

#include <Framework/Crypto/Private/Algorithm.h>
#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/MessageDigest/Hash.h>
#include <Framework/Crypto/Private/MessageDigest/Signature.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Mac
{
/**
 * @brief Represents a private key for usage with the Hmac algorithm.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP HmacKey
{
public:
    /**
     * @brief Creates a HmacKey from the given key.
     *
     * @throw std::runtime_error in case of an error.
     */
    explicit HmacKey(Encoding::BytesView key);
    /**
     * @brief Returns the underlying OpenSSL key.
     */
    const EVP_PKEY* pkey() const;

private:
    OpenSsl::EvpPkeyPtr m_pkey;
};

/**
 * @brief Provides message authentication codes for messages using HMAC.
 *
 * @tparam Hash hash function like Sha256.
 *
 * @details
 * For details on hash-based message authentication code (HMAC)
 * see https://en.wikipedia.org/wiki/HMAC
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestHmac.cpp initUpdateFinal
 *
 * @ingroup Crypto
 */
template <class Hash>
class Hmac
{
public:
    /**
     * @brief Type of hashing algorithm.
     */
    using HashType = Hash;
    /**
     * @brief Creates a HMAC algorithm using the given key.
     *
     * @throw std::runtime_error in case of an error.
     */
    explicit Hmac(const HmacKey& key)
        : m_mac{Hash::algorithm(), key.pkey()}
    {
    }
    /**
     * @brief Setup internal context.
     *
     * @throw std::runtime_error in case of an error.
     */
    void init()
    {
        m_mac.init();
    }
    /**
     * @brief Hashes message into the internal context.
     *
     * @pre init has been called.
     *
     * @throw std::runtime_error in case of an error.
     */
    void update(Encoding::BytesView message)
    {
        m_mac.update(message);
    }
    /**
     * @brief Signs the data.
     *
     * @pre init and update have been called.
     *
     * @post The result can be obtained from the mac function.
     *
     * @throw std::runtime_error in case of an error.
     */
    void final()
    {
        m_mac.final();
    }
    /**
     * @brief Returns the calculated MAC value.
     *
     * @note
     * Calling this function clears the internal result, i. e. a second call
     * returns empty.
     */
    Encoding::Bytes mac() noexcept
    {
        return m_mac.signature();
    }

private:
    Impl::Signature m_mac;
};

}
}
}
}
