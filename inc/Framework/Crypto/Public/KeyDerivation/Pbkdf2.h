#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/MessageDigest/Hash.h>
#include <Framework/Crypto/Public/MessageDigest/Hash/Sha1.h>
#include <Framework/Crypto/Public/MessageDigest/Hash/Sha256.h>
#include <Framework/Crypto/Public/MessageDigest/Mac/Hmac.h>
#include <Framework/Crypto/Public/OpenSsl.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <boost/numeric/conversion/cast.hpp>

#include <stdexcept>
#include <string>
#include <type_traits>

namespace DFL
{
namespace Crypto
{
namespace KeyDerivation
{
struct IterationsTag;
struct KeySizeTag;
/**
 * @brief Represents the number of iterations used in key derivation.
 *
 * @ingroup Crypto
 */
using Iterations = StrongTypedef<size_t,
                                 IterationsTag,
                                 Skill::TotallyOrdered,
                                 Skill::Streamable>;
/**
 * @brief Represents the size of the derived key in bytes.
 *
 * @ingroup Crypto
 */
using KeySize =
    StrongTypedef<size_t, KeySizeTag, Skill::TotallyOrdered, Skill::Streamable>;

/**
 * @brief Provides key derivation based on PBKDF2.
 *
 * @details
 * For details on Password-Based Key Derivation Function 2 (PBKDF2),
 * see https://en.wikipedia.org/wiki/PBKDF2
 *
 * The number of iterations can be specified to adjust the security and the
 * performance of this algorithm.
 *
 * @tparam PseudorandomFunc pseudorandom function like Hmac<Sha1> or
 * Hmac<Sha256>.
 *
 * @snippet Crypto/Test/UnitTest/KeyDerivation/TestPbkdf2.cpp testVector1
 *
 * @ingroup Crypto
 */
template <class PseudorandomFunc>
class Pbkdf2
{
public:
    /**
     * @brief Creates a PBKDF2 algorithm with the given iterations and keySize.
     */
    Pbkdf2(Iterations iterations, KeySize keySize)
        : m_iterations{iterations}
        , m_keySize{keySize}
        , m_algorithm{PseudorandomFunc::HashType::algorithm()}
    {
        using MessageDigest::Hash::Sha1;
        using MessageDigest::Hash::Sha256;
        using MessageDigest::Mac::Hmac;

        static_assert(
            std::is_same<Hmac<Sha1>, PseudorandomFunc>::value ||
                std::is_same<Hmac<Sha256>, PseudorandomFunc>::value,
            "Only Pbkdf2<Hmac<Sha1>> and Pbkdf2<Hmac<Sha256>> are supported!");
    }

    /**
     * @brief Returns a derived key from the given password and salt.
     *
     * @throw std::runtime_error in case of an error.
     */
    Encoding::Bytes operator()(Encoding::BytesView password,
                               Encoding::BytesView salt) const
    {
        Encoding::Bytes derivedKey(m_keySize.get());

        try
        {
            if (OpenSsl::pkcs5PbKdf2Hmac(
                    reinterpret_cast<const char*>(password.data()),
                    boost::numeric_cast<int>(password.size()),
                    salt.data(),
                    boost::numeric_cast<int>(salt.size()),
                    boost::numeric_cast<int>(m_iterations.get()),
                    m_algorithm,
                    boost::numeric_cast<int>(derivedKey.size()),
                    derivedKey.data()) != 1)
            {
                throw std::runtime_error{
                    std::string{"OpenSsl::pkcs5PbKdf2Hmac failed, "} +
                    OpenSsl::getError()};
            }
        }
        catch (const boost::bad_numeric_cast& e)
        {
            throw std::runtime_error{std::string{"Pbkdf2 failed, "} + e.what()};
        }

        return derivedKey;
    }

private:
    Iterations m_iterations;
    KeySize m_keySize;
    Impl::Hash::Type m_algorithm;
};
}
}
}
