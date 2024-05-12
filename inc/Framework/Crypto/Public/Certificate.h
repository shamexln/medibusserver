#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Convert.h>
#include <Framework/Crypto/Public/DerFormat.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/PemString.h>

#include <Framework/Chrono/Public/ZonedTime.h>
#include <Framework/Encoding/Public/Bytes.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>

#include <memory>
#include <string>

namespace DFL
{
class Oids;
namespace Crypto
{
class Csr;
class PrivateKey;
class DistinguishedName;
/**
 * @brief Represents an X509 certificate.
 *
 * @details
 * The functionality is provided by the \c \::X509* type from OpenSSL.
 * This class has the ownership of such a handle. Either such handle is created
 * on construction or it is passed to a constructor. In any case this class is
 * responsible for freeing the created/given resource.
 *
 * Access to the wrapped handle is provided but it should never be freed by the
 * caller.
 *
 * The only way to release this type from owning the handle is by calling
 * release(). Then and only then the caller is responsible for freeing the
 * handle.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Certificate
{
public:
    /**
     * @brief Type of fingerprint.
     */
    using Fingerprint = Encoding::Bytes;
    /**
     * @brief Immutable type of underlying OpenSSL certificate.
     */
    using Type = const ::X509*;
    /**
     * @brief Mutable type of underlying OpenSSL certificate.
     */
    using MutableType = ::X509*;
    /**
     * @brief Creates an empty certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificate.cpp DefaultCtor
     */
    Certificate() noexcept;
    /**
     * @brief Creates a certificate from an OpenSSL certificate.
     *
     * The ownership will be transferred from x509 to this certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificate.cpp X509Ptr
     */
    explicit Certificate(OpenSsl::X509Ptr x509) noexcept;
    /**
     * @brief Creates a certificate from an OpenSSL raw certificate.
     *
     * The ownership will be transferred from x509 to this certificate.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificate.cpp X509RawPtr
     */
    explicit Certificate(MutableType x509) noexcept;
    /**
     * @brief Creates a certificate from a PEM string.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificate.cpp pemCtor
     */
    explicit Certificate(const PemString& pem);
    /**
     * @brief Creates a certificate from DER data.
     *
     * @throw std::runtime_error in case of an error.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificate.cpp derCtor
     */
    explicit Certificate(const DerFormat& der);
    /**
     * @brief Copy constructor
     * @throw std::runtime_error in case of an error.
     */
    Certificate(const Certificate& other);
    /**
     * @brief Move constructor
     */
    Certificate(Certificate&&) = default;
    /**
     * @brief Copy assignment operator
     * @throw std::runtime_error in case of an error.
     */
    Certificate& operator=(const Certificate& other);
    /**
     * @brief Move assignment operator
     */
    Certificate& operator=(Certificate&&) = default;
    /**
     * @brief Exchanges the contents of the certificate with those of other.
     */
    void swap(Certificate& other) noexcept;
    /**
     * @brief Compares other certificate with this certificate.
     */
    bool equals(const Certificate& other) const noexcept;
    /**
     * @brief Returns the certificate issuer's distinguished name.
     */
    DistinguishedName issuer() const;
    /**
     * @brief Returns the certificate subject's distinguished name.
     */
    DistinguishedName subject() const;
    /**
     * @brief Returns the timepoint the certificate is valid from.
     */
    Chrono::ZonedTime validFrom() const;
    /**
     * @brief Returns the timepoint the certificate expires.
     */
    Chrono::ZonedTime validUntil() const;
    /**
     * @brief Returns the CA flag from the v3 basic constraints
     */
    bool ca() const;
    /**
     * @brief Returns vector of extended key usages from the certificate.
     */
    Oids extendedKeyUsageOids() const;
    /**
     * @brief Returns a SHA-256 fingerprint of the certificate.
     *
     * Fingerprints are used to reference X.509 certificates. In case these
     * references are just for information purposes MD5 or SHA-1 are sufficient.
     * But since they are used for security purposes (e.g. lookup roles of a
     * root ca in the root authorization list) a secure hash algorithm has to
     * be used. Thus this method creates SHA-256 fingerprints of the
     * certificate.
     *
     * @throw std::runtime_error in case of an error.
     */
    Fingerprint fingerprint() const;
    /**
     * @brief Returns the underlying OpenSSL certificate.
     */
    Type certificate() const noexcept;
    /**
     * @brief Returns the underlying OpenSSL certificate.
     */
    MutableType certificate() noexcept;
    /**
     * @brief Releases the ownership of the managed OpenSSL handle if any.
     *
     * The caller takes ownership and thus is responsible for freeing the
     * handle. Afterwards this object behaves exactly the same as a default
     * constructed one.
     * @snippet Crypto/Test/UnitTest/TestCertificate.cpp Release
     *
     * Releasing the handle can be useful when interfacing with OpenSSL. For
     * example, if you get a handle which is owned by OpenSSL but you want to
     * use the comfortable API of this class.
     * @snippet Crypto/Sample/Sample.cpp OpenSSLOwns
     */
    [[maybe_unused]] MutableType release() noexcept;

private:
    void createFrom(const PemString& pem);
    void createFrom(const DerFormat& der);

    friend class boost::serialization::access;

    template <class Archive>
    void save(Archive& ar, const unsigned int /*version*/) const
    {
        const PemString pem = Convert::toPem(*this);
        ar& boost::serialization::make_nvp("Pem", pem);
    }

    template <class Archive>
    void load(Archive& ar, const unsigned int /*version*/)
    {
        PemString pem;
        ar& boost::serialization::make_nvp("Pem", pem);
        createFrom(pem);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    OpenSsl::X509Ptr m_cert;
};
/**
 * @brief Exchanges the given certificates.
 */
DFL_CRYPTO_EXPIMP void swap(Certificate& a, Certificate& b) noexcept;
/**
 * @brief Compares two certificates.
 *
 * Two certificates are equal if the hashes of both are equal.
 * Otherwise they are not equal.
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const Certificate& lhs,
                                  const Certificate& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const Certificate& lhs,
                                  const Certificate& rhs) noexcept;
/** @} */
}
}

BOOST_CLASS_VERSION(::DFL::Crypto::Certificate, 0)
