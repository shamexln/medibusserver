#pragma once

#include <Framework/Crypto/Private/Store/KnownRootCas.h>
#include <Framework/Crypto/Public/Certificate.h>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief Provides access to known root cas.
 *
 * These root cas are typically used in the context of tests or samples.
 *
 * @ingroup Crypto
 */
class KnownRootCas
{
public:
    /**
     * @brief This is the root ca for all draeger devices within the SDC
     * context.
     */
    static Certificate draegerDevice();
    /**
     * @brief This is the test root ca for all draeger SDC devices.
     *
     * This root allows devices to accept certificates which are not signed by
     * the signing authority. Thus the process of creating signed certificates
     * is reduced. On the other hand the private key of this root is known. By
     * no means should this root ever be used in production.
     */
    static Certificate draegerTest();
    /**
     * @brief This is the staging root ca.
     *
     * When testing the API between draeger and the signing authority
     * certificates are signed with this staging root ca.
     */
    static Certificate staging();
};
inline Certificate KnownRootCas::draegerDevice()
{
    return DFL::Crypto::Impl::KnownRootCas::deviceRootCa();
}

inline Certificate KnownRootCas::draegerTest()
{
    return DFL::Crypto::Impl::KnownRootCas::testRootCa();
}

inline Certificate KnownRootCas::staging()
{
    return DFL::Crypto::Impl::KnownRootCas::stagingRootCa();
}
}
}
}
