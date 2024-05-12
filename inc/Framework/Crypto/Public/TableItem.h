#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Store/TableItem.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/CertificateChainSerialize.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/PrivateKeySerialize.h>
#include <Framework/Crypto/Public/RoleAuthorizationList.h>
#include <Framework/Crypto/Public/RoleAuthorizationListSerialize.h>
#include <Framework/Crypto/Public/RootCas.h>
#include <Framework/Crypto/Public/RootCasSerialize.h>
#include <Framework/Crypto/Public/Whitelist.h>
#include <Framework/Crypto/Public/WhitelistSerialize.h>

#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/SystemTimeSerialize.h>
#include <Framework/Utils/Public/Key.h>
#include <Framework/Utils/Public/KeySerialize.h>
#include <Framework/Utils/Public/Oids.h>
#include <Framework/Utils/Public/OidsSerialize.h>

#include <boost/optional/optional.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Holds the private keys, certificate chain and whitelist
 * for a specific component-key.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP TableItem
{
    friend ::DFL::Crypto::Impl::ItemAccess;

public:
    /**
     * @brief Type holding either a private key or none.
     */
    using OptionalPrivateKey = boost::optional<PrivateKey>;
    /**
     * @brief Type holding either a certificate chain or none.
     */
    using OptionalCertificateChain = boost::optional<CertificateChain>;
    /**
     * @brief Type of the time point when csr was deployed.
     */
    using OptionalSystemTime = boost::optional<Chrono::SystemClock::TimePoint>;
    /**
     * @brief Return the component key.
     */
    const Component::Key& compKey() const noexcept;
    /**
     * @brief Returns the current private key.
     */
    const OptionalPrivateKey& currentPrivateKey() const noexcept;
    /**
     * @brief Returns the certificate chain.
     */
    const OptionalCertificateChain& chain() const noexcept;
    /**
     * @brief Returns the whitelist.
     */
    const Whitelist& whitelist() const noexcept;
    /**
     * @brief Returns the time point when csr was deployed to be send to
     * the certificate authority.
     */
    const OptionalSystemTime& csrDeployedOn() const noexcept;
    /**
     * @brief Returns the common name.
     */
    const CommonName& commonName() const noexcept;
    /**
     * @brief Returns the desired roles.
     */
    const Oids& roles() const noexcept;
    /**
     * @brief Returns the root CAs.
     */
    const RootCas& rootCas() const noexcept;
    /**
     * @brief Returns the role authorization list.
     */
    const RoleAuthorizationList& roleAuthorizationList() const noexcept;
    /**
     * @brief Returns true if other is equal to *this, otherwise false.
     */
    bool equals(const TableItem& other) const noexcept;
    /**
     * @brief Exchanges the contents of table item with those of other.
     *
     * @snippet Crypto/Test/UnitTest/TestTableItem.cpp swap
     */
    void swap(TableItem& other) noexcept;

private:
    Impl::TableItem m_implItem{};

    friend class boost::serialization::access;

    template <class Archive>
    void save(Archive& ar, const unsigned int /*version*/) const
    {
        ar& boost::serialization::make_nvp("ComponentKey",
                                           m_implItem.m_compKey);
        ar& boost::serialization::make_nvp("PrivateKey",
                                           m_implItem.m_currentPrivateKey);
        ar& boost::serialization::make_nvp("NextPrivateKey",
                                           m_implItem.m_nextPrivateKey);
        ar& boost::serialization::make_nvp("Chain", m_implItem.m_chain);
        ar& boost::serialization::make_nvp("Whitelist", m_implItem.m_whitelist);
        ar& boost::serialization::make_nvp("CsrDeployedOn",
                                           m_implItem.m_csrDeployedOn);
        ar& boost::serialization::make_nvp("CommonName",
                                           m_implItem.m_commonName);
        ar& boost::serialization::make_nvp("Roles", m_implItem.m_roles);
        ar& boost::serialization::make_nvp("RootCas", m_implItem.m_rootCas);
        ar& boost::serialization::make_nvp("RoleAuthorizationList",
                                           m_implItem.m_ral);
    }

    template <class Archive>
    void load(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::make_nvp("ComponentKey",
                                           m_implItem.m_compKey);
        ar& boost::serialization::make_nvp("PrivateKey",
                                           m_implItem.m_currentPrivateKey);
        ar& boost::serialization::make_nvp("NextPrivateKey",
                                           m_implItem.m_nextPrivateKey);
        ar& boost::serialization::make_nvp("Chain", m_implItem.m_chain);
        ar& boost::serialization::make_nvp("Whitelist", m_implItem.m_whitelist);
        ar& boost::serialization::make_nvp("CsrDeployedOn",
                                           m_implItem.m_csrDeployedOn);
        if (version >= 1)
        {
            ar& boost::serialization::make_nvp("CommonName",
                                               m_implItem.m_commonName);
        }
        if (version >= 2)
        {
            ar& boost::serialization::make_nvp("Roles", m_implItem.m_roles);
            ar& boost::serialization::make_nvp("RootCas", m_implItem.m_rootCas);
            ar& boost::serialization::make_nvp("RoleAuthorizationList",
                                               m_implItem.m_ral);
        }
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};
/**
 * @brief Compares two table items.
 *
 * @snippet Crypto/Test/UnitTest/TestTableItem.cpp equalityComparable
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const TableItem& lhs,
                                  const TableItem& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const TableItem& lhs,
                                  const TableItem& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given table items.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(TableItem& a, TableItem& b) noexcept;
}
}

BOOST_CLASS_VERSION(::DFL::Crypto::TableItem, 2)
