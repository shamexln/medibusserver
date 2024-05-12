#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Convert.h>
#include <Framework/Crypto/Public/DistinguishedName.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Utils/Public/Oids.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Crypto
{
class AttributeTypeAndValue;
class PemString;
class PrivateKey;
class PublicKey;
/**
 * @brief Represents a [certificate signing request]
 * (https://en.wikipedia.org/wiki/Certificate_signing_request).
 *
 * A CSR is a message send to a certificate authority. It answers with a
 * certificate which then can be used to establish an SSL connection.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Csr
{
public:
    /**
     * @brief Type of the internal handle.
     */
    using Type = const ::X509_REQ*;
    /**
     * @brief Creates an empty CSR.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp DefaultCtor
     */
    Csr() noexcept;
    /**
     * @brief Creates a CSR ready to be send to a certificate authority.
     *
     * - Version is set to X509_V1
     * - dn is used as subject name
     * - roles are written in the extended key usage field
     * - CSR is signed with privateKey
     *
     * @throw std::runtime_error in case any of the setter fail.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp keyWithDistinguishedNameCtor
     */
    Csr(const PrivateKey& privateKey,
        const DistinguishedName& dn,
        const Oids& roles = Oids{});
    /**
     * @brief Creates a csr from given pem-string.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp pemCtor
     */
    explicit Csr(const PemString& pemStr);
    /**
     * @brief CopyCtor.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp copyOps
     */
    Csr(const Csr& other);
    /**
     * @brief Move constructor
     */
    Csr(Csr&&) = default;
    /**
     * @brief CopyAssign.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp copyOps
     */
    Csr& operator=(const Csr& other);
    /**
     * @brief Move assignment operator
     */
    Csr& operator=(Csr&&) = default;
    /**
     * @brief Exchanges the contents of the CSR with those of other.
     */
    void swap(Csr& other) noexcept;
    /**
     * @brief Returns a reference to the internal handle.
     *
     * Can be used when there is the need to interface directly with the
     * underlying ssl library. The lifetime of this handle is managed by
     * this object.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp pemCtor
     */
    Type csr() const;
    /**
     * @brief Returns the csr subject's distinguished name.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp subject
     */
    DistinguishedName subject() const;
    /**
     * @brief Returns the version number.
     *
     * @note
     * this is defined by standards (X.509 et al) to be one less than the
     * certificate version. So a version 3 certificate will return 2 and
     * a version 1 certificate will return 0.
     */
    long version() const;
    /**
     * @brief Returns extended key usage as container of OIDs.
     *
     * @snippet Crypto/Test/UnitTest/TestCsr.cpp keyWithDistinguishedNameCtor
     */
    Oids extendedKeyUsageOids() const;

private:
    void setVersion(long version) const;
    void addAttributes(const DistinguishedName& dn) const;
    void setPublicKey(const PublicKey& publicKey) const;
    void setExtendedKeyUsage(const Oids& roles) const;
    void signRequest(const PrivateKey& privateKey) const;
    void createFrom(const PemString& pem);

    OpenSsl::X509ReqPtr m_csr;
};

/**
 * @brief Exchanges the given CSRs.
 */
DFL_CRYPTO_EXPIMP void swap(Csr& a, Csr& b) noexcept;

/**
 * @brief Two CSRs are considered equal if their pem-string representations
 * are equal.
 *
 * @throw Whatever Convert::toPem(const Csr&) throws
 *
 * @snippet Crypto/Test/UnitTest/TestCsr.cpp compareOps
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const Csr& lhs, const Csr& rhs);
DFL_CRYPTO_EXPIMP bool operator!=(const Csr& lhs, const Csr& rhs);
/** @} */
}
}
