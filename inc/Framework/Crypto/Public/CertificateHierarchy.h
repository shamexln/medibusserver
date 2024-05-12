#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

namespace DFL
{
namespace Crypto
{
class Certificate;

namespace CertificateHierarchy
{
/**
 * @brief Returns true, if cert is a root CA
 */
DFL_CRYPTO_EXPIMP bool isRootCa(const Certificate& cert);
/**
 * @brief Returns true, if cert is an intermediate CA
 */
DFL_CRYPTO_EXPIMP bool isIntermediateCa(const Certificate& cert);
/**
 * @brief Returns true, if cert is a leaf certificate
 */
DFL_CRYPTO_EXPIMP bool isLeafCert(const Certificate& cert);
/**
 * @brief Returns true, if order number of c1 is less than c2.
 *
 * Ascending order numbers:
 * 1. Leaf certificate
 * 2. Intermediate CA
 * 3. Root CA
 */
DFL_CRYPTO_EXPIMP bool compareOrderNumber(const Certificate& c1,
                                          const Certificate& c2);
}
}
}
