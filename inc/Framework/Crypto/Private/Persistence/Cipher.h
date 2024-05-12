#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Cipher/Symmetric/DeviceSpecific.h>

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
class CipherException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class DFL_CRYPTO_EXPIMP Cipher
{
public:
    Encoding::Bytes encrypt(Encoding::BytesView message);
    Encoding::Bytes decrypt(Encoding::BytesView encrypted);

private:
    Crypto::Cipher::Symmetric::DeviceSpecific m_cipher{};
};
}
}
}
}
