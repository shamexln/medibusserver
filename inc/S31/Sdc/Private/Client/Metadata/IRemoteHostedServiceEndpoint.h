#pragma once

#include <string>

namespace S31::Sdc::Impl
{

/**
 * Interface for a remote service endpoint.
 *
 * \ingroup S31SdcClientMetadata
 */
class IRemoteHostedServiceEndpoint
{
    public:
        virtual ~IRemoteHostedServiceEndpoint() = default;

        virtual std::string getRemoteEndpointAddress() const = 0;
        virtual bool empty() const = 0;

};

}
