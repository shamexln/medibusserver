#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

#include <cstddef>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
class DFL_CRYPTO_EXPIMP Signature
{
public:
    using Type = const EVP_MD*;

    explicit Signature(Type algorithm, const EVP_PKEY* pkey);

    void init();
    void update(Encoding::BytesView message);
    void final();
    Encoding::Bytes signature() noexcept;

private:
    std::size_t maxSignatureSize() const;

    OpenSsl::EvpMdContextPtr m_context;
    Type m_algorithm{};
    const EVP_PKEY* m_pkey{};
    Encoding::Bytes m_signature{};
};

class DFL_CRYPTO_EXPIMP Verification
{
public:
    using Type = const EVP_MD*;

    explicit Verification(Type algorithm, const EVP_PKEY* pkey);

    void signature(Encoding::BytesView sig);
    void init();
    void update(Encoding::BytesView message);
    void final();
    bool passed() const noexcept;

private:
    OpenSsl::EvpMdContextPtr m_context;
    Type m_algorithm{};
    const EVP_PKEY* m_pkey{};
    Encoding::Bytes m_signature{};
    bool m_passed{false};
};

// In order to be invulnerable against timing attacks,
// a constant time equals must be used for comparison of MAC values
// https://codahale.com/a-lesson-in-timing-attacks/
// https://wiki.openssl.org/index.php/EVP_Signing_and_Verifying
DFL_CRYPTO_EXPIMP bool constantTimeEquals(Encoding::BytesView lhs,
                                          Encoding::BytesView rhs) noexcept;
}
}
}
