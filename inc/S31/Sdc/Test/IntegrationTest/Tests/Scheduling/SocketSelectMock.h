#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IncomingHttpRequest.h>
#include <S31/Sdc/Private/Common/SoapContextPool.h>
#include <S31/Sdc/Private/Common/SocketLayer/ISocketSelect.h>

#include <Framework/Utils/Public/NotNull.h>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief Mock implementation for SocketController to test the scheduling in front of it.
 */
class SocketSelectMock: public ISocketSelect
{
        class IncomingRequest : public IncomingHttpRequest
        {
            public:
                explicit IncomingRequest(DFL::NotNull<SoapPtr> soapPtr):
                        IncomingHttpRequest(std::move(soapPtr), std::shared_ptr<IWebService>(), {})
                {
                }

                std::string jobName() const override
                {
                    return "TestIncominGRequest";
                }

                void execute() override
                {
                    // nothing to do
                }
        };

    public:
        SocketSelectMock():
                m_soapPool(std::make_shared<SoapContextPool>())
        {
        }

        void abortAcceptSockets() override
        {
        }

        IncomingHttpRequestPtrs acceptSocketsWithHttp(DFL::Chrono::Milliseconds, S31::Sdc::MaxResultCount) override
        {
            return IncomingHttpRequestPtrs(std::make_unique<IncomingRequest>(m_soapPool->getSoapPtr()));
        }

        void acceptSocketsWithoutHttp(DFL::Chrono::Milliseconds) override
        {
        }

    private:
        std::shared_ptr<ISoapContextPool> m_soapPool;

};

}
