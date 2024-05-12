#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Certificate.h>

#include <vector>

namespace DFL
{
namespace Crypto
{
class Certificates;
class PemString;
/**
 * @brief Tag type for providing leaf certificate.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
 *
 * @ingroup Crypto
 */
struct LeafInclusiveTag
{
};
/**
 * @brief Tag type for leaving out leaf certificate.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
 *
 * @ingroup Crypto
 */
struct LeafExclusiveTag
{
};
/**
 * @brief Instance of tag for providing leaf certificate.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
 *
 * @ingroup Crypto
 */
const LeafInclusiveTag leafInclusive;
/**
 * @brief Instance of tag for leaving out leaf certificate.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
 *
 * @ingroup Crypto
 */
const LeafExclusiveTag leafExclusive;
/**
 * @brief Holds the certificate chain containing leaf and intermediate
 * certificates.
 * @details
 * From https://knowledge.digicert.com/solution/SO16297.html
 * > A certificate chain is an ordered list of certificates, containing an SSL/TLS %Certificate
 * > and %Certificate Authority (CA) %Certificates, that enable the receiver to verify that the
 * > sender and all CA's are trustworthy.
 *
 * > The chain or path begins with the SSL/TLS certificate, and each certificate in the chain
 * > is signed by the entity identified by the next certificate in the chain.
 *
 * Note that a certificate chain does not contain the root certificate (supposed to be known to
 * the peer/verifier) and that the top most intermediate certificate is expected to be signed
 * by a known root.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP CertificateChain
{
private:
    using underlying_type = std::vector<Certificate>;

public:
    /**
     * @name STL compliant container aliases
     * @{
     */
    using value_type = typename underlying_type::value_type;
    using const_reference = typename underlying_type::const_reference;
    using reference = typename underlying_type::reference;
    using const_iterator = typename underlying_type::const_iterator;
    using iterator = typename underlying_type::iterator;
    using difference_type = typename underlying_type::difference_type;
    using size_type = typename underlying_type::size_type;
    /** @} */
    /**
     * @brief Creates an empty chain.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp defaultCtor
     */
    CertificateChain() = default;
    /**
     * @brief Creates a chain of certificates from given pem-string.
     *
     * Root CAs are removed and leaf certificates are being sorted in front of
     * the intermediate ones.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp pemCtor
     */
    explicit CertificateChain(const PemString& pem);
    /**
     * @brief Creates a chain of certificates from certs.
     *
     * Root CAs are removed and at most one leaf certificate is being
     * sorted in front of the intermediate ones.
     *
     * If there is more than one leaf certificate then an exception is thrown.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp certsCtor
     */
    explicit CertificateChain(const Certificates& certs);
    /**
     * @brief True if no certificate is in chain.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp pemCtor
     */
    bool empty() const;
    /**
     * @brief Returns the number of all certificates in chain.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp pemCtor
     */
    size_type size() const;
    /**
     * @brief Returns iterator to begin of chain inclusive leaf certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator begin(LeafInclusiveTag) const;
    /**
     * @brief Returns iterator to begin of chain exclusive leaf certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator begin(LeafExclusiveTag) const;
    /**
     * @brief Returns iterator to begin of chain inclusive leaf certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator begin() const;
    /**
     * @brief Returns iterator to the end of the chain.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator end() const;
    /**
     * @brief Returns iterator to begin of chain inclusive leaf certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator cbegin(LeafInclusiveTag) const;
    /**
     * @brief Returns iterator to begin of chain exclusive leaf certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator cbegin(LeafExclusiveTag) const;
    /**
     * @brief Returns iterator to begin of chain inclusive leaf certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator cbegin() const;
    /**
     * @brief Returns iterator to the end of the chain.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp beginEnd
     */
    const_iterator cend() const;
    /**
     * @brief Returns the leaf certificate from chain.
     *
     * If more than one leaf certificate is within chain the first one appearing
     * in the pem string is returned.
     *
     * @throw std::runtime_error if called on an empty chain.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp pemCtor
     */
    const Certificate& leafCert() const;

private:
    underlying_type m_chain{};
    difference_type m_noOfLeafs{};
};
/**
 * @brief True if two chains contain the same certificates in the same order
 * otherwise false
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp compareOps
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const CertificateChain& lhs,
                                  const CertificateChain& rhs);
DFL_CRYPTO_EXPIMP bool operator!=(const CertificateChain& lhs,
                                  const CertificateChain& rhs);
/** @} */
}
}
