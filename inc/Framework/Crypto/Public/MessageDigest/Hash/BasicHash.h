#pragma once

#include <Framework/Crypto/Private/MessageDigest/Hash.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Hash
{
/**
 * @brief Provides a basic hashing algorithm.
 *
 * @tparam Algorithm OpenSSL algorithm that shall be used.
 *
 * @ingroup Crypto
 */
template <class Algorithm>
class BasicHash
{
public:
    /**
     * @brief Returns the used OpenSSL algorithm.
     *
     * @details needed by depending algorithms like Hmac
     */
    static Impl::Hash::Type algorithm()
    {
        return Algorithm::algorithm();
    }
    /**
     * @brief Setup internal context.
     *
     * @throw std::runtime_error in case of an error.
     */
    void init()
    {
        m_hash.init();
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
        m_hash.update(message);
    }
    /**
     * @brief Creates the final hash value.
     *
     * @pre init and update have been called.
     *
     * @post The result can be obtained from the hash function.
     *
     * @throw std::runtime_error in case of an error.
     */
    void final()
    {
        m_hash.final();
    }
    /**
     * @brief Returns the calculated hash value.
     *
     * @note
     * Calling this function clears the internal result, i. e. a second call
     * returns empty.
     */
    Encoding::Bytes hash() noexcept
    {
        return m_hash.hash();
    }

private:
    Impl::Hash m_hash{algorithm()};
};

}
}
}
}
