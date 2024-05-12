#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>

namespace DFL
{
namespace Crypto
{
class DistinguishedNameBuilder;
/**
 * @brief Represents a simple form of a distinguished name.
 *
 * @details See [RFC 4514](https://www.ietf.org/rfc/rfc4514.txt)
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP DistinguishedName
{
public:
    /**
     * @brief Creates an empty distinguished name, same as default constructed
     * one.
     *
     * @snippet Crypto/Test/UnitTest/TestDistinguishedName.cpp EmptyDn
     */
    static DistinguishedNameBuilder emptyDn();
    /**
     * @brief Initializes distinguished name piece by piece.
     *
     * @snippet Crypto/Test/UnitTest/TestDistinguishedName.cpp CreateDn
     */
    static DistinguishedNameBuilder createDn();
    /**
     * @brief Creates an empty distinguished name.
     *
     * @snippet Crypto/Test/UnitTest/TestDistinguishedName.cpp DefaultCtor
     */
    DistinguishedName() = default;
    /**
     * @brief Creates a distinguished name from the given parameter.
     *
     * @snippet Crypto/Test/UnitTest/TestDistinguishedName.cpp FullCtor
     */
    DistinguishedName(CountryName c,
                      StateOrProvinceName st,
                      LocalityName l,
                      OrganizationName o,
                      OrganizationalUnitName ou,
                      CommonName cn,
                      UserId uid = UserId{});

    /**
     * @brief Returns the country name.
     */
    const CountryName& countryName() const;
    /**
     * @brief Returns the state or province name.
     */
    const StateOrProvinceName& stateOrProvinceName() const;
    /**
     * @brief Returns the locality name.
     */
    const LocalityName& localityName() const;
    /**
     * @brief Returns the organization name.
     */
    const OrganizationName& organizationName() const;
    /**
     * @brief Returns the organizational unit name.
     */
    const OrganizationalUnitName& organizationalUnitName() const;
    /**
     * @brief Returns the common name.
     */
    const CommonName& commonName() const;
    /**
     * @brief Returns the userid.
     */
    const UserId& userId() const;
    /**
     * @brief Exchanges the contents of distinguished name with those of other.
     */
    void swap(DistinguishedName& other) noexcept;

private:
    CountryName m_countryName{};
    StateOrProvinceName m_stateOrProvinceName{};
    LocalityName m_localityName{};
    OrganizationName m_organizationName{};
    OrganizationalUnitName m_organizationalUnitName{};
    CommonName m_commonName{};
    UserId m_userId{};

    friend DistinguishedNameBuilder;
};
/**
 * @brief Compares two distinguished names.
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const DistinguishedName& lhs,
                                  const DistinguishedName& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const DistinguishedName& lhs,
                                  const DistinguishedName& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given distinguished names.
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(DistinguishedName& a,
                            DistinguishedName& b) noexcept;

/**
 * @brief Initializes each field of a distinguished name in separation.
 *
 * @snippet Crypto/Test/UnitTest/TestDistinguishedName.cpp CreateDn
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP DistinguishedNameBuilder
{
public:
    /**
     * @name Attribute setter
     * @{
     */
    DistinguishedNameBuilder& country(std::string c);
    DistinguishedNameBuilder& stateOrProvince(std::string st);
    DistinguishedNameBuilder& locality(std::string l);
    DistinguishedNameBuilder& organization(std::string o);
    DistinguishedNameBuilder& organizationalUnit(std::string ou);
    DistinguishedNameBuilder& commonName(std::string cn);
    DistinguishedNameBuilder& userId(std::string uid);
    /** @} */
    /**
     * @brief Return distinguished name with the set attributes.
     * @{
     */
    operator DistinguishedName() const&;
    operator DistinguishedName() &&;
    /** @} */
private:
    DistinguishedName m_dn{};
};
}
}
