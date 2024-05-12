#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Sdc/Private/Client/Metadata/DeviceMetadata.h>
#include <S31/Sdc/Private/Common/Endpoint/EndpointUrl.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/S31CoreExImp.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * \brief Result of @ref GetDeviceMetadataJob.
 *
 * \ingroup S31SdcClientMetadata
 */
struct GetDeviceMetadataJobResult
{
       DeviceMetadata metadata;
       S31::Nomenclature::Credentials credentials;
};

/**
 * \brief Retrieves the DPWS metadata of a remote device.
 *
 * \ingroup S31SdcClientMetadata
 */
class S31_CORE_EXPIMP GetDeviceMetadataJob: public OutgoingBlockingHttpRequestWithOutcome<GetDeviceMetadataJobResult>
{
    public:
        GetDeviceMetadataJob(const OutcomeHandlerPtr& handler,
                             const Endpoint::Url& transportAddress,
                             EndpointReference soapAddress);

        // used in test, therefore public
        using Utils::OutcomeProvider<GetDeviceMetadataJobResult>::setOutcomeResult;
        using Utils::OutcomeProvider<GetDeviceMetadataJobResult>::setOutcomeError;

        void processRequest() override;
        std::string jobName() const override;

    private:
        Endpoint::Url m_transportAddress;
        EndpointReference m_soapAddress;
};

}
