#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/RoleAuthorizationList.h>
#include <Framework/Crypto/Public/RootCas.h>
#include <Framework/Crypto/Public/Whitelist.h>

#include <boost/optional/optional.hpp>

namespace S31::Nomenclature
{

/**
 * @brief Returns the root certificates/root CAs to be used for SDC communication.
 * @ingroup S31Nomenclature
 */
S31_CORE_EXPIMP DFL::Crypto::RootCas sdcRootCas();

/**
 * @brief Returns the private key to be used for SDC communication.
 * @ingroup S31Nomenclature
 */
S31_CORE_EXPIMP boost::optional<DFL::Crypto::PrivateKey> sdcPrivateKey();

/**
 * @brief Returns the certificate chain for the this/subject's certificate, to be used for SDC communication.
 * @ingroup S31Nomenclature
 */
S31_CORE_EXPIMP DFL::Crypto::CertificateChain sdcCertificateChain();

/**
 * @brief Returns the whitelist to be used for SDC communication.
 * @ingroup S31Nomenclature
 */
S31_CORE_EXPIMP DFL::Crypto::Whitelist sdcWhitelist();

/**
 * @brief Returns the RAL used for SDC communication.
 * @ingroup S31Nomenclature
 */
S31_CORE_EXPIMP DFL::Crypto::RoleAuthorizationList sdcRoleAuthorizationList();

}
