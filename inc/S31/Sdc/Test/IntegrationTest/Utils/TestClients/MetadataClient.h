#pragma once

#include <S31/Sdc/Private/Client/Metadata/GetDeviceMetadataJob.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>

namespace S31::Sdc::Impl::Test
{

/**
 * MetadataClient is a test helper to send transfer get requests.
 */
class MetadataClient : public Utils::OutcomeConsumer<MetadataClient, GetDeviceMetadataJobResult>,
                       public std::enable_shared_from_this<MetadataClient>
{
    public:
        Endpoint::HandlerPtr sendTransferGet(const Endpoint::Executor& endpoint, const EndpointReference& epr, const CallbackFunction& callback);
};
}
