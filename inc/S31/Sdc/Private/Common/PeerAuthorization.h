#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Utils/Public/Errors.h>

#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <optional>

namespace S31::Sdc::Impl::PeerAuthorization
{
/**
 * @brief   Checks whether the peer is authorized for communication.
 * @details The following requirements have to be met in order for this check to succeed.
 *          - The ssl context of the connection has to be enhanced with application data.
 *          In particular, the soap context is expected to be retrievable from the ssl context.
 *          If that is not the case, the check fails.
 *          - A certificate of the peer has to be available.
 *          The peer certificate may e.g. not be available, if the peer has not provided a certificate
 *          or if the certificate has otherwise been freed.
 *          - The EKU of the peer's certificate has the necessary roles for Sdc communication.
 *          The required roles are:
 *          SdcServiceProvider or SdcServiceConsumer.
 *          - The whitelist is not empty and the common name of the peer is in the whitelist or all peers are whitelisted.
 *          In case any of the above check fails, a Service Log Message specific to that check is written except if the soap context is not present.
 * @return true iff all of the requirements are fulfilled, false otherwise.
 * @ingroup S31SdcCommon
 */
bool peerIsAuthorizedForCommunication(X509_STORE_CTX* store);

/**
 * @brief   Checks whether the peer is authorized for Sdc communication.
 * @details The following requirements have to be met in order for this check to succeed.
 *          - The EKU of the peer's certificate has the necessary roles for Sdc communication.
 *          The required roles are:
 *          SdcServiceProvider or SdcServiceConsumer.
 *          - The whitelist is not empty and the common name of the peer is in the whitelist or all peers are whitelisted.
 * @return An optional error message describing any failure encountered.
 * @ingroup S31SdcCommon
 */
std::optional<Utils::Error> verifySdcPeerCredentials(const Nomenclature::Credentials& credentials);

}
