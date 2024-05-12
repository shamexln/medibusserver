#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/IDispatcher.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/Sdc/Test/Utils/TestDeviceConfiguration.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Oids.h>

#include <memory>

namespace S31::Sdc::Test
{
class DeviceSubscriptionInfoObserverMock;

/**
 * @brief Implementation of an SDC device that runs with dedicated thread pools and network sockets.
 */
class S31_CORE_IT_UTIL_EXPIMP TestDevice: public S31::Sdc::LocalDevice
{
    public:
        static TestDeviceConfiguration defaultConfiguration();
        static TestDeviceConfiguration configuration(EndpointReference epr);
        explicit TestDevice(TestDeviceConfiguration configuration = TestDevice::defaultConfiguration());

        // no copy
        TestDevice(const TestDevice& rhs) = delete;
        TestDevice& operator=(const TestDevice& rhs) = delete;

        // move
        TestDevice(TestDevice&& rhs) = default;
        TestDevice& operator=(TestDevice&& rhs) = default;
        ~TestDevice() override;

        [[nodiscard]] const S31::Sdc::EndpointReference& epr() const override;

        void dpwsDeviceMetadata(const DpwsDeviceMetadata& deviceInfo) override;

        void start() override;
        void stop() override;
        void stopDispatcher();
        [[nodiscard]] bool isRunning() const override;

        DFL::NotNull<std::shared_ptr<SetService::InvocationCallbackRegistry>> invocationCallbackRegistry() const override;

        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> localMdibAccess() const override;

        std::shared_ptr<History::Service> historyService() const override;

        std::shared_ptr<Localization::Device::LocalizedTextStore> localizedTextStore() const override;

        S31::Sdc::MedicalDeviceData& medicalDeviceData() override;

        const std::shared_ptr<DeviceSubscriptionInfoObserverMock>& registerSubscriptionInfoObserver() const;
        void unregisterSubscriptionInfoObserver() const;
        void registerSubscriptionInfoObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer) override;
        void unregisterSubscriptionInfoObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer) override;
        ClientSubscriptions subscriptions() const override;

        void onComponentReportCompleted(
                const DFL::Mdib::MdibVersion&                      version,
                std::function<void(const DFL::Mdib::MdibVersion&)> callback) override;

        void sendHello() override;

        std::shared_ptr<S31::Sdc::CommunicationEndpoint> communicationEndpoint() const;

        /**
         * @brief Set the device to the location.
         * @details Makes a new context with the location that is associated and validated.
         */
        void setLocation(DFL::Mdib::LocationDetail location);
    private:
        DFL::NotNull<std::shared_ptr<IDispatcher>> m_dispatcher;
        S31CoreFactory m_factory;
        std::shared_ptr<Sdc::LocalDevice> m_device;

        std::shared_ptr<DeviceSubscriptionInfoObserverMock> m_localDeviceSubscriptionInfoObserver;
};

}
