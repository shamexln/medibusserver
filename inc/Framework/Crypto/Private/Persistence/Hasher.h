#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

#include <stdexcept>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
namespace Persistence
{
class HasherException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class DFL_CRYPTO_EXPIMP Hasher
{
public:
    static Encoding::Bytes load(Encoding::BytesView bytes);
    static Encoding::Bytes save(Encoding::BytesView bytes);
};
}
}
}
}
