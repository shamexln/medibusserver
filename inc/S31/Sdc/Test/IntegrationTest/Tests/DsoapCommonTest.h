#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

namespace S31
{
class CoreConfiguration;

namespace AsioDispatch
{
class ExecutorProvider;
class DefaultDispatcher;
}

namespace Sdc::Impl
{
class DpwsCommunicationNode;
class SocketController;
class OutgoingBlockingHttpRequest;
class NetworkInterfaceFilter;

namespace Test
{
class GetContextStatesJobOutcomeConsumer;
class WebServiceMock;
class SchedulingMock;

class DsoapCommonTest: public ::testing::Test
{
    public:
        SOAP_SOCKET runJob(const std::shared_ptr<OutgoingBlockingHttpRequest>& job) const;

    protected:
        void SetUp() override;
        void TearDown() override;

        std::unique_ptr<OutgoingBlockingHttpRequest> createGetContextStateJob(std::uint16_t deviceDestPort);
        void checkGetContextStateJobOutcomeError() const;
        static SOAP_SOCKET getDeviceIncomingSocketAndSendJob(const std::shared_ptr<SocketController>& deviceSocketController);

        std::shared_ptr<CoreConfiguration> m_deviceConf;
        std::shared_ptr<CoreConfiguration> m_clientConf;
        std::shared_ptr<CoreConfiguration> m_clientConf2;
        std::shared_ptr<WebServiceMock> m_webService;
        std::shared_ptr<SchedulingMock> m_deviceScheduler;
        std::shared_ptr<AsioDispatch::DefaultDispatcher> m_dispatcher;
        std::shared_ptr<NetworkInterfaceFilter> m_netIfFilter;
        std::shared_ptr<S31::Sdc::Impl::DpwsCommunicationNode> m_remoteNode;
        std::shared_ptr<GetContextStatesJobOutcomeConsumer> m_getContextStatesJobOutcomeConsumer;
};

}
}
}
