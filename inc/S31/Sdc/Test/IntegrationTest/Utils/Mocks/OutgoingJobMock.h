#pragma once

#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequest.h>

namespace S31::Sdc::Impl::Test
{

class OutgoingJobMock: public OutgoingBlockingHttpRequest
{
    public:
        OutgoingJobMock(const std::string& transportAddr) :
            OutgoingBlockingHttpRequest(transportAddr, RequiredPeerRoles{DFL::Oids{}})
        {
        }

        void processRequest() override
        {
            // get the soapPtr to ensure a fetched soapPtr in the base class
            getInjectedSoapHandleOrGetNewFromPool();
        }

        std::string jobName() const override
        {
            return "OutgoingJobMock";
        }

    protected:
        void postProcessRequest() override
        {}
};

}
