#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/Csr.h>
#include <Framework/Crypto/Public/RootCas.h>
#include <Framework/Crypto/Public/Table.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/Application/Identifier.h>
#include <Framework/Utils/Public/Key.h>
#include <Framework/Utils/Public/Oids.h>

namespace DFL::Crypto
{
class Certificate;
class CertificateChain;
class PrivateKey;
class RoleAuthorizationList;
class Whitelist;
}
namespace DFL::Crypto::Impl
{
class DFL_CRYPTO_EXPIMP Store
{
public:
    static Crypto::Table applicationIdentifier(
        const Crypto::Table& table,
        const Application::Identifier& id);
    static PrivateKey generateKey();
    static Chrono::Days maxCertificateLifetime();
    static Component::Key requester(const Crypto::Table& table,
                                    const CertificateChain& chain);
    static Crypto::Table certificateChain(const Crypto::Table& table,
                                          const Component::Key& requester,
                                          const CertificateChain& chain);
    static Crypto::Table removeCertificateChainFor(
        const Crypto::Table& table,
        const Component::Key& requester);
    static Crypto::Table csrDeployedFor(const Crypto::Table& table,
                                        const Component::Key& requester);
    static Crypto::Table removeKeyFor(const Crypto::Table& table,
                                      const Component::Key& requester);
    static Crypto::Csr generateCsrFor(const Crypto::Table& table,
                                      const Component::Key& requester);
    static Crypto::Table requestCertificateFor(const Crypto::Table& table,
                                               const Component::Key& requester,
                                               const CommonName& cn,
                                               const Oids& roles);
    static Crypto::Table whitelistFor(const Crypto::Table& table,
                                      const Component::Key& requester,
                                      const Whitelist& list);
    static Crypto::Table rootCasFor(const Crypto::Table& table,
                                    const Component::Key& requester,
                                    const RootCas& rootCas);
    static Crypto::Table roleAuthorizationListFor(
        const Crypto::Table& table,
        const Component::Key& requester,
        const RoleAuthorizationList& ral);
    static bool needsKey(const Crypto::Table& table,
                         const Component::Key& requester);
    static Crypto::Table distributeKey(const Crypto::Table& table,
                                       const Component::Key& requester,
                                       const PrivateKey& key);
};
}
