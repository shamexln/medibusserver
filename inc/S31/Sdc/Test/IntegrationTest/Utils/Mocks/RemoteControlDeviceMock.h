#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Device/DsoapDevice/Services/BicepsCombinedService.h>
#include <S31/Sdc/Private/Device/IOutgoingMessage.h>
#include <S31/Sdc/Private/Device/SetService/DsoapDeviceTransactionFactory.h>
#include <S31/Sdc/Public/Device/LocalMdibAccess.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/BicepsTestFunctions.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/BicepsTestFunctionsHelper.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/BicepsTestTypes.h>
#include <S31/Sdc/Test/UnitTest/Private/Device/WS-Eventing/SubscriberInfoMock.h>
#include <S31/Sdc/Test/Utils/MdibAccessProvider.h>
#include <S31/SetService/Public/Device/InvocationCallbacks.h>
#include <S31/SetService/Public/Device/ScoControllerFactory.h>
#include <S31/SetService/Test/Public/Device/InvocationCallbackMock.h>
#include <S31/Utils/Test/Public/BoostTimer.h>

#include <gtest/gtest.h>

class LocalEventingStub: public S31::Sdc::Impl::ILocalEventing
{
    public:
        bool hasEventListenerForAction(std::string_view) const override
        {
            return true;
        }
        bool hasEventListenerForAnyAction() const override
        {
            return true;
        }
        void fireEvent(DFL::NotNull<std::unique_ptr<S31::Sdc::Impl::IOutgoingMessage>> /*event*/) override
        {
        }
        void setDiscoveryLocationScopes(const std::vector<std::string>&) override
        {
        }
        void setDiscoveryMdsInfoScopes(const std::vector<std::string>&) override
        {
        }
        void componentReportDeliveryStarting(const DFL::Mdib::MdibVersion&) override
        {
        }
        void componentReportDeliveryCompleted(const DFL::Mdib::MdibVersion&) noexcept override
        {
        }
};

class RemoteControlDeviceMock
{
    public:
        RemoteControlDeviceMock(DFL::NotNull<S31::Sdc::LocalMdibAccessSharedPtr> localMdibAccess,
                                DFL::NotNull<std::shared_ptr<S31::SetService::ScoController>> scoController,
                                std::shared_ptr<S31::Sdc::Impl::SubscriberInfo> subscriberInfo) :
                m_localMdibAccess(std::move(localMdibAccess)),
                m_scoController(std::move(scoController)),
                m_subscriberInfo(std::move(subscriberInfo))
        {
        }

        [[nodiscard]] DFL::NotNull<std::shared_ptr<S31::SetService::InvocationCallbackRegistry>>
        invocationCallbackRegistry() const
        {
            return m_scoController->invocationCallbackRegistry();
        }

        void dispatchRequest(std::istream& requestStream) const
        {
            // set up gSOAP input and output streams
            std::ostringstream responseStream;
            auto soapPtr = S31Test::Sdc::newSoapPtr(requestStream, responseStream);

            auto service = S31::Sdc::Impl::BicepsCombinedService(
                    m_localMdibAccess.get(),
                    m_localMdibAccess->dualChannelFactoryManager(),
                    m_scoController.get(),
                    m_subscriberInfo);

            soap_begin_serve(soapPtr.get().get());
            int error = service.dispatch(soapPtr.get().get());

            if (error != 0 && error != SOAP_STOP)
            {
                ADD_FAILURE() << "Unexpected soap error=" << error;
                throw std::runtime_error("Unexpected soap error");
            }
        }


        static RemoteControlDeviceMock setupRemoteControlDeviceMock(std::istream& mdibStream)
        {
            // create a LocalMdibAccess from the MDIB input file
            DFL::NotNull<S31::Sdc::LocalMdibAccessSharedPtr> localMdibAccess = S31::Sdc::Test::MdibAccessProvider::createFromStream(mdibStream);

            // Setup a ScoController to process the request
            auto timerFactory = DFL::asNotNull(std::make_shared<S31::Utils::Test::BoostTimerFactory>());
            DFL::NotNull<std::shared_ptr<S31::SetService::ScoController>> scoController =
                    S31::SetService::ScoControllerFactory::create(
                            timerFactory,
                            localMdibAccess,
                            DFL::asNotNull(std::make_shared<S31::Sdc::Impl::DsoapDeviceTransactionFactory>(
                                    DFL::asNotNull(std::make_shared<LocalEventingStub>()), localMdibAccess)));

            auto subscriberInfo = std::make_shared<S31::Sdc::Impl::Test::SubscriberInfoMock>();

            return {localMdibAccess, scoController, subscriberInfo};
        }

    private:
        DFL::NotNull<S31::Sdc::LocalMdibAccessSharedPtr> m_localMdibAccess;
        DFL::NotNull<std::shared_ptr<S31::SetService::ScoController>> m_scoController;
        std::shared_ptr<S31::Sdc::Impl::SubscriberInfo> m_subscriberInfo;
};
