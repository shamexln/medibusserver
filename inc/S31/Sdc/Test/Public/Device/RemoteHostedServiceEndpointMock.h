#pragma once

#include <S31/Sdc/Private/Client/Metadata/IRemoteHostedServiceEndpoint.h>

namespace S31::Sdc::Impl::Test
{

/**
 * mock for remote hosted services.
 */
class RemoteHostedServiceEndpointMock: public S31::Sdc::Impl::IRemoteHostedServiceEndpoint
{
    public:
        RemoteHostedServiceEndpointMock() :
                epr("http://localhost/")
        {
        }

        RemoteHostedServiceEndpointMock(const std::string& endpointRef):
            epr(endpointRef)
        {
        }

        virtual std::string getRemoteEndpointAddress() const override
        {
            return epr;
        }
        virtual bool empty() const override
        {
            return false;
        }

    private:
        std::string epr;
};

}
