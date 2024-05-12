#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
namespace Persistence
{
DFL_CRYPTO_EXPIMP Encoding::Bytes constructHashedBuffer(
    Encoding::BytesView payload);
DFL_CRYPTO_EXPIMP void checkHashedBuffer(Encoding::BytesView hashedBuffer);
DFL_CRYPTO_EXPIMP Encoding::Bytes extractPayload(
    Encoding::BytesView hashedBuffer);

class DFL_CRYPTO_EXPIMP HasherBytesParser
{
public:
    explicit HasherBytesParser(Encoding::BytesView);
    HasherBytesParser(Encoding::Bytes&&) = delete;

    Encoding::BytesView entire;
    Encoding::BytesView payload;
    Encoding::BytesView hash;
    Encoding::BytesView magic;
    Encoding::BytesView version;
    Encoding::BytesView header;
};

DFL_CRYPTO_EXPIMP bool operator==(const HasherBytesParser& lhs,
                                  const HasherBytesParser& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const HasherBytesParser& lhs,
                                  const HasherBytesParser& rhs) noexcept;
}
}
}
}
