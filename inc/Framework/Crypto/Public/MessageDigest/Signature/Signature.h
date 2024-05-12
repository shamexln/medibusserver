#pragma once

#include <Framework/Crypto/Private/Algorithm.h>
#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/MessageDigest/Signature.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>
#include <Framework/Crypto/Public/PrivateKey.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace MessageDigest
{
namespace Signature
{
/**
 * @brief
 * Provides digital signatures of bytes using a private key.
 *
 * @tparam Hash hash function like Sha256.
 *
 * @details
 * For details on digital signatures
 * see https://en.wikipedia.org/wiki/Digital_signature
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp sigSetup
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp sigUpdate
 *
 * @ingroup Crypto
 */
template <class Hash>
class Signature
{
public:
    /**
     * @brief Creates a digital signature algorithm using the given privateKey.
     *
     * @throw std::runtime_error in case of an error.
     */
    explicit Signature(const PrivateKey& privateKey)
        : m_signature{Hash::algorithm(), privateKey.privateKey()}
    {
    }
    /**
     * @brief Setup internal context.
     *
     * @throw std::runtime_error in case of an error.
     */
    void init()
    {
        m_signature.init();
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
        m_signature.update(message);
    }
    /**
     * @brief Signs the data.
     *
     * @pre init and update have been called.
     *
     * @post The result can be obtained from the signature function.
     *
     * @throw std::runtime_error in case of an error.
     */
    void final()
    {
        m_signature.final();
    }
    /**
     * @brief Returns the calculated digital signature.
     *
     * @note
     * Calling this function clears the internal result, i. e. a second call
     * returns empty.
     */
    Encoding::Bytes signature() noexcept
    {
        return m_signature.signature();
    }

private:
    Impl::Signature m_signature;
};

}
}
}
}
