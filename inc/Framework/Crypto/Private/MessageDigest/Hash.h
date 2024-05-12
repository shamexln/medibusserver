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
class DFL_CRYPTO_EXPIMP Hash
{
public:
    using Type = const EVP_MD*;

    Hash(Type algorithm);

    void init();
    void update(Encoding::BytesView message);
    void final();
    Encoding::Bytes hash() noexcept;

private:
    OpenSsl::EvpMdContextPtr m_context;
    Type m_algorithm{};
    Encoding::Bytes m_hash{};
};

struct DFL_CRYPTO_EXPIMP Sha1Algorithm
{
    static Hash::Type algorithm();
};

struct DFL_CRYPTO_EXPIMP Sha256Algorithm
{
    static Hash::Type algorithm();
};
}
}
}
