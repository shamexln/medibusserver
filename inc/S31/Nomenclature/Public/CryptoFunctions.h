#pragma once

#include <S31/Nomenclature/Public/Whitelist.h>

#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/RoleAuthorizationList.h>
#include <Framework/Crypto/Public/RootCas.h>

#include <boost/optional/optional.hpp>

#include <functional>

/** @file CryptoFunctions.h
 *  Contains function types that provide objects of object types from the crypto store (or doing operations from such objects).
 *  These serve as configurations to omit using the crypto store directly.
 */

namespace S31::Nomenclature
{

/**
 * @brief Functions that provide root CAs.
 * @ingroup S31Nomenclature
 */
using ProvideRootCasFunction = std::function<DFL::Crypto::RootCas()>;

/**
 * @brief Functions that provide possibly a private key.
 * @ingroup S31Nomenclature
 */
using ProvidePrivateKeyFunction = std::function<boost::optional<DFL::Crypto::PrivateKey>()>;

/**
 * @brief Functions that provide the certificate chain.
 * @ingroup S31Nomenclature
 */
using ProvideCertificateChainFunction = std::function<DFL::Crypto::CertificateChain()>;

/**
 * @brief Functions that check a peer's name against a whitelist.
 * @ingroup S31Nomenclature
 */
using WhitelistCheckFunction = std::function<S31::Nomenclature::WhiteListingState(const std::string& value)>;

/**
 * @brief Functions that provide the certificate chain.
 * @ingroup S31Nomenclature
 */
using ProvideRoleAuthorizationListFunction = std::function<DFL::Crypto::RoleAuthorizationList()>;

}
