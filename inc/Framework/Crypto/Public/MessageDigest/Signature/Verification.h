#pragma once

#include <Framework/Crypto/Private/Algorithm.h>
#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/MessageDigest/Signature.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>
#include <Framework/Crypto/Public/PublicKey.h>

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
 * @brief Verifies digital signatures using a public key.
 *
 * @tparam Hash hash function like Sha256.
 *
 * @details
 * For details on digital signatures
 * see https://en.wikipedia.org/wiki/Digital_signature
 *
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp verSetup
 * @snippet Crypto/Test/UnitTest/MessageDigest/TestRsaSignature.cpp verUpdate
 *
 * @ingroup Crypto
 */
template <class Hash>
class Verification
{
public:
    /**
     * @brief
     * Creates a verfier for digital signatures using the given publicKey.
     *
     * @throw std::runtime_error in case of an error.
     */
    explicit Verification(const PublicKey& publicKey)
        : m_verification{Hash::algorithm(), publicKey.publicKey()}
    {
    }
    /**
     * @brief Sets the expected signature values.
     */
    void signature(Encoding::BytesView expectedSignature)
    {
        m_verification.signature(expectedSignature);
    }
    /**
     * @brief Setup internal context.
     *
     * @pre signature has been called.
     *
     * @throw std::runtime_error in case of an error.
     */
    void init()
    {
        m_verification.init();
    }
    /**
     * @brief Hashes message into the internal context.
     *
     * @pre signature and init have been called.
     *
     * @throw std::runtime_error in case of an error.
     */
    void update(Encoding::BytesView message)
    {
        m_verification.update(message);
    }
    /**
     * @brief Verifies the expected signature against the calculated signature.
     *
     * @pre signature, init and update have been called.
     *
     * @post The result can be obtained from the passed function.
     *
     * @throw std::runtime_error in case of an error.
     */
    void final()
    {
        m_verification.final();
    }
    /**
     * @brief Returns true if the expected signature equals the calculated signature.
     *
     * @pre signature, init, update and final have been called.
     */
    bool passed() const noexcept
    {
        return m_verification.passed();
    }

private:
    Impl::Verification m_verification;
};

}
}
}
}
