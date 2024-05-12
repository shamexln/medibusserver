#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/Key.h>

namespace S31::Nomenclature
{

/**
 * @brief Component ID to request a certificate in the @ref DFL::Crypto::Store.
 *
 * @details In the DFL::Crypto::Store::requestCertificateFor() a component ID has to be specified.
 * This id is visible in the Remote Access Interface (RAI) in the certificate table.
 * By design the S31 component key 305 (0x131) is used for SDC certificates in the DFL crypto store.
 *
 * @ingroup S31Nomenclature
 */

S31_CORE_EXPIMP const DFL::Component::Key& sdcCertificateId();

}
