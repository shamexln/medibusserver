#pragma once

#include <S31/Sdc/Public/Common/CompressionConfiguration.h>
#include <S31/Sdc/Public/Common/DpwsDeviceMetadata.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/Oids.h>

namespace S31::Sdc
{

/**
 * @brief Container for all DPWS (as well as WS-Discovery) related data.
 * @details
 * The DPWS related data is separated from the medical data in @ref S31::Sdc::MedicalDeviceData due to its different
 * scope. The DPWS data is related to SOAP web services, while the medical data is the domain model around the BICEPS
 * %Mdib with its localized texts and historic data (previous %Mdib versions)
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP MedicalDpwsData
{
public:
    /**
     * @brief Construct a new medical DPWS data container.
     *
     * @param endpointReference The BICEPS device's persistent identifier (e.g.,
     * urn:uuid:a99d2381-3a45-4bc2-98a2-bac92f021f2f) used for WS-Discovery.
     * @param initialMetadataVersion The initial version for WS-Discovery MetadataVersion.
     * @param metadata The DPWS metadata in the discovery.
     * @param shallCompressReport Specify whether WS-Eventing notification shall be compressed when requested by a
     * WS-Eventing client in the subscription request.
     * @param keyPurposes Set of requirements an SDC participant is complying with.
     */
    MedicalDpwsData(
            EndpointReference        endpointReference,
            MetadataVersion          initialMetadataVersion,
            DpwsDeviceMetadata       metadata,
            CompressionConfiguration shallCompressReport = CompressionConfiguration::NoCompression,
            DFL::Oids                keyPurposes         = {});

    const EndpointReference& epr() const noexcept;

    bool compressReports() const noexcept;

    CompressionConfiguration compressionConfiguration() const noexcept;

    MetadataVersion initialMetadataVersion() const noexcept;
    void            metadataVersion(MetadataVersion newVersion);

    const DpwsDeviceMetadata& metadata() const noexcept;
    void metadata(const DpwsDeviceMetadata& metadata);

    const DFL::Oids& keyPurposes() const noexcept;

private:
    EndpointReference        m_endpointReference;
    MetadataVersion          m_initialMetadataVersion;
    DpwsDeviceMetadata       m_metadata;
    CompressionConfiguration m_shallCompressReport;
    DFL::Oids                m_keyPurposes;
};
}  // namespace S31::Sdc
