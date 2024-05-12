#pragma once

#include <S31/Nomenclature/Public/SdcCertificateId.h>

#include <Framework/Config/Public/Attributes.h>

DFL_HEADER_DEPRECATED("use <S31/Nomenclature/Public/SdcCertificateId.h> instead")

namespace S31::Sdc
{

/**
 * @brief Component ID to request a certificate in the @ref DFL::Crypto::Store.
 * @ingroup S31SdcCommon
 * @deprecated use @ref S31::Nomenclature::sdcCertificateId() instead.
*/
[[deprecated("use S31::Nomenclature::sdcCertificateId() instead")]]
inline const DFL::Component::Key& sdcCertificateId()
{
    return S31::Nomenclature::sdcCertificateId();
}

}
