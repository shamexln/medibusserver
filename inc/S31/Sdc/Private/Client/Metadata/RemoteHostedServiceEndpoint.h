#pragma once

#include <S31/Sdc/Private/Client/Metadata/IRemoteHostedServiceEndpoint.h>

#include <Framework/Utils/Public/Uri.h>

#include <vector>

namespace S31::Sdc::Impl
{

/**
 * Implementation of IRemoteHostedServiceEndpoint.
 *
 * \ingroup S31SdcClientMetadata
 */
class RemoteHostedServiceEndpoint: public S31::Sdc::Impl::IRemoteHostedServiceEndpoint
{
    public:
        std::string getRemoteEndpointAddress() const override;
        bool empty() const override;

        void addRemoteAddress(const DFL::Net::Uri& address);

    private:
        std::string m_remoteAdresses;
};

}
