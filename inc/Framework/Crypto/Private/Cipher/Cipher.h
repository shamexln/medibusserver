#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

#include <string>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
class DFL_CRYPTO_EXPIMP Cipher
{
public:
    using Algorithm = const EVP_CIPHER*;
    using ContextPtr = OpenSsl::EvpCipherContextPtr::pointer;

    enum class Mode : int
    {
        decryption = 0,
        encryption = 1
    };

    explicit Cipher(Algorithm algorithm,
                    Encoding::BytesView key,
                    Encoding::BytesView iv,
                    Mode mode,
                    std::string name);

    void init();
    void update(Encoding::BytesView bytes);
    void final();
    Encoding::Bytes result();
    size_t keySize() const;
    size_t ivSize() const;
    size_t blockSize() const;
    Algorithm algorithm() const;
    ContextPtr context();

    void swap(Cipher& other) noexcept;

private:
    OpenSsl::EvpCipherContextPtr m_context;
    Algorithm m_algorithm{};
    Encoding::Bytes m_key{};
    Encoding::Bytes m_iv{};
    Mode m_mode{};
    Encoding::Bytes m_result{};
    std::string m_name{};
};

DFL_CRYPTO_EXPIMP void swap(Cipher& a, Cipher& b) noexcept;

struct DFL_CRYPTO_EXPIMP Aes256CbcAlgorithm
{
    static Cipher::Algorithm algorithm();
    static std::string name();
};

struct DFL_CRYPTO_EXPIMP Aes128GcmAlgorithm
{
    static Cipher::Algorithm algorithm();
    static std::string name();
};
}
}
}
