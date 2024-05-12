#pragma once

#include <Framework/Crypto/Private/Registry.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/Certificates.h>
#include <Framework/Crypto/Public/Convert.h>
#include <Framework/Crypto/Public/Csr.h>
#include <Framework/Crypto/Public/PemString.h>
#include <Framework/Crypto/Public/PublicKey.h>
#include <Framework/Crypto/Public/Store.h>
#include <Framework/Crypto/Public/Table.h>
#include <Framework/Crypto/Test/Public/TestrootCaSignedCertificate.h>

#include <Framework/Utils/Public/Key.h>

#include <boost/optional/optional.hpp>

#include <string>

namespace DFL
{
namespace Crypto
{
namespace Test
{
namespace Store
{
/**
 * @brief Removes all file persistent objects.
 *
 * @ingroup Crypto
 */
inline bool removePersistence()
{
    return Crypto::Impl::Registry::removePersistence();
}

/**
 * @brief Inserts a testroot CA signed certificate into the store for user
 * identified by given component Key and common name.
 *
 * @ingroup Crypto
 */
inline bool insertDeviceTestCertificate(const Component::Key& compKey,
                                        CommonName commonName)
{
    try
    {
        if (!Crypto::Store::table()[compKey])
        {
            if (!Crypto::Store::requestCertificateFor(compKey, commonName))
            {
                return false;
            }
        }
        {
            const auto optTableItem = Crypto::Store::table()[compKey];
            if (!optTableItem)
            {
                return false;
            }
            if (optTableItem->chain())
            {
                // certificate chain already exists -> no default overwrite
                return false;
            }
        }
        if (!Crypto::Store::generateKeys())
        {
            return false;
        }
        std::string errMsg{};
        const auto csr = Crypto::Store::generateCsrFor(compKey, errMsg);
        if (!csr)
        {
            return false;
        }
        const auto cert = createTestrootCaSignedLeafCertificate(
            csr->subject().commonName().value(),
            PublicKey{*csr});
        return Crypto::Store::certificateChain(
            CertificateChain{Certificates{cert}});
    }
    catch (...)
    {
        return false;
    }
}
}
}
}
}
