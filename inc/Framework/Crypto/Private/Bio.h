#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

namespace DFL
{
namespace Crypto
{
class PemString;
}
}

namespace DFL
{
namespace Crypto
{
namespace Impl
{

class DFL_CRYPTO_EXPIMP Bio
{
public:
    Bio();
    explicit Bio(const PemString& pemString);

    ::BIO* bio() const;
    PemString pem() const;

private:
    OpenSsl::BioPtr m_bio;
};

}
}
}
