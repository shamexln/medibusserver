#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/KeyType.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>
#include <Framework/Crypto/Public/PemString.h>

#include <Framework/Encoding/Public/BytesView.h>

#include <memory>

namespace DFL
{
namespace Crypto
{
class DerFormat;
class BigNumber;

namespace Impl
{
class DFL_CRYPTO_EXPIMP EvpPkey
{
public:
    static EvpPkey createPublicKey(const ::EVP_PKEY* pkey);
    static EvpPkey createPublicKey(const PemString& pem);
    static EvpPkey createPrivateKey(const PemString& pem);
    static EvpPkey createPublicKey(const DerFormat& der);
    static EvpPkey createPrivateKey(const DerFormat& der);
    static EvpPkey generateRsaPrivateKey();
    static EvpPkey generateEcPrivateKey();
    static EvpPkey createEcPublicKey(Encoding::BytesView x,
                                     Encoding::BytesView y);
    static EvpPkey createEcPublicKey(const BigNumber& x, const BigNumber& y);

    EvpPkey() noexcept;
    explicit EvpPkey(OpenSsl::EvpPkeyPtr pkey);
    explicit EvpPkey(const ::X509* x509);
    explicit EvpPkey(const ::X509_REQ* req);

    EvpPkey(const EvpPkey& other);
    EvpPkey& operator=(const EvpPkey& other);

    EvpPkey(EvpPkey&&) = default;
    EvpPkey& operator=(EvpPkey&&) = default;

    void swap(EvpPkey& other) noexcept;
    bool equals(const EvpPkey& other) const noexcept;

    ::EVP_PKEY* pkey() const noexcept;

    KeyType type() const noexcept;

private:
    OpenSsl::EvpPkeyPtr m_pkey;
};

DFL_CRYPTO_EXPIMP void swap(EvpPkey& a, EvpPkey& b) noexcept;
DFL_CRYPTO_EXPIMP bool operator==(const EvpPkey& lhs,
                                  const EvpPkey& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const EvpPkey& lhs,
                                  const EvpPkey& rhs) noexcept;
}
}
}
