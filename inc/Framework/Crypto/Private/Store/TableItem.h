#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/RoleAuthorizationList.h>
#include <Framework/Crypto/Public/RootCas.h>
#include <Framework/Crypto/Public/Whitelist.h>

#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Utils/Public/Key.h>
#include <Framework/Utils/Public/Oids.h>

#include <boost/optional/optional.hpp>

namespace DFL::Crypto
{
class TableItem;
}
namespace DFL::Crypto::Impl
{
class DFL_CRYPTO_EXPIMP TableItem
{
public:
    Component::Key m_compKey{};
    boost::optional<PrivateKey> m_currentPrivateKey{};
    boost::optional<PrivateKey> m_nextPrivateKey{};
    boost::optional<CertificateChain> m_chain{};
    Whitelist m_whitelist{};
    boost::optional<Chrono::SystemClock::TimePoint> m_csrDeployedOn{};
    CommonName m_commonName{};
    Oids m_roles{};
    RootCas m_rootCas{};
    RoleAuthorizationList m_ral{};
};

class DFL_CRYPTO_EXPIMP ItemAccess
{
public:
    explicit ItemAccess(Crypto::TableItem* item);

    static const boost::optional<PrivateKey>& currentPrivateKey(
        const Crypto::TableItem& item);
    static const boost::optional<PrivateKey>& nextPrivateKey(
        const Crypto::TableItem& item);

    ItemAccess compKey(const Component::Key& k) &&;
    ItemAccess currentPrivateKey(const boost::optional<PrivateKey>& k) &&;
    ItemAccess nextPrivateKey(const boost::optional<PrivateKey>& k) &&;
    ItemAccess chain(const boost::optional<CertificateChain>& c) &&;
    ItemAccess whitelist(const Whitelist& wl) &&;
    ItemAccess csrDeployedOn(
        const boost::optional<Chrono::SystemClock::TimePoint>& tp) &&;
    ItemAccess commonName(const CommonName& cn) &&;
    ItemAccess roles(const Oids& r) &&;
    ItemAccess rootCas(const RootCas& r) &&;
    ItemAccess roleAuthorizationList(const RoleAuthorizationList& ral) &&;

private:
    Crypto::TableItem* m_item;
};

DFL_CRYPTO_EXPIMP bool operator==(const TableItem& lhs,
                                  const TableItem& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const TableItem& lhs,
                                  const TableItem& rhs) noexcept;
DFL_CRYPTO_EXPIMP void swap(TableItem& a, TableItem& b) noexcept;
}
