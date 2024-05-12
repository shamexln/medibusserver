#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Certificate.h>

#include <Framework/Utils/Public/ConstContainer.h>

#include <vector>

namespace DFL
{
namespace Crypto
{
class PemString;

/**
 * @brief Type of certificates.
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Certificates
    : public Utils::ConstContainer<std::vector<Certificate>>
{
public:
    using Utils::ConstContainer<std::vector<Certificate>>::ConstContainer;

    /**
     * @brief Creates empty certificates.
     */
    Certificates() = default;
    /**
     * @brief Creates certificates from certificates contained in given
     * pem-string.
     *
     * @snippet Crypto/Test/UnitTest/TestCertificates.cpp pemCtor
     */
    explicit Certificates(const PemString& pem);
};
}
}
