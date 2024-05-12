#pragma once

#include <S31/Sdc/Private/Device/WS-Eventing/WSEventingNotifyJob.h>
#include <S31/Sdc/Test/Public/Device/OutgoingMessageMock.h>
#include <S31/Sdc/Test/UnitTest/GsoapEprMock.h>
#include <S31/Utils/Test/Public/OutcomeMock.h>

#include <memory>

namespace S31Test::Sdc::UnitTest
{

class WsEventingNotifyJobFactory
{
    public:
        static std::unique_ptr<S31::Sdc::Impl::WSEventingNotifyJob> createDummyJob();
};

inline std::unique_ptr<S31::Sdc::Impl::WSEventingNotifyJob> WsEventingNotifyJobFactory::createDummyJob()
{
    auto outcomeMock = std::make_shared<S31::Utils::Test::OutcomeMock<S31::Sdc::Impl::WSEventingNotifyJobResult>>();
    auto handler = outcomeMock->makeIgnoreOutcomeHandler();
    auto message = DFL::asNotNull(std::make_shared<S31::Sdc::Test::OutgoingMessageMock>());
    auto epr = S31Test::Sdc::UnitTest::readSharedGsoapEpr(S31Test::Sdc::UnitTest::WsEventingNotifyTo_ComplexExample);
    auto job = std::make_unique<S31::Sdc::Impl::WSEventingNotifyJob>(
            handler,
            message,
            epr,
            S31::Sdc::Impl::SoapActionView{"action"},
            "subscriptionId",
            S31::Sdc::Impl::EncodingType::None);
    return job;
}

}
