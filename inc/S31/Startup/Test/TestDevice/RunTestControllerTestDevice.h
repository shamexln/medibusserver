#pragma once

#include <TestDevice/DeviceHandlerMock.h>

#include <S31/Osf/Public/Client/GlobalAudioPauseClient.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/SetService/Public/Device/DeviceTransaction.h>
#include <S31/UseCases/S31Only/ILocationHandler.h>
#include <S31/UseCases/S31Only/IMeasurementHandler.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Test
{
class NumericMetricMdibAccessTestHandler;
class NumericMetricHandlerMock;

//! implements a run test controller used by the S31_CoreItDevice (i.e. the network peer for the S31_it_Test_runner)
class RunTestControllerTestDevice: public S31::SetService::V3::MdsSetStringCallback
{
    public:
        RunTestControllerTestDevice(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> mdibAccess,
                                    std::shared_ptr<ILocationHandler> locationHandler,
                                    std::shared_ptr<DeviceHandlerMock> deviceHandler,
                                    std::shared_ptr<S31::Sdc::LocalDevice> device);

        void start();
        void stop();


        void callback(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                      const DFL::Locale::Utf8& payload,
                      S31::SetService::SynchronousDeviceTransaction& transaction) override;

        std::string getCurrentTest();

    private:
        void initMdib();
        void deinitMdib();
        void enableOperations();

        /**
         * \brief Takes a set operation's requested value and dispatches it to any run-tests.
         *
         * @param value The set operation's requested value.
         */
        void dispatchRunTestValue(const std::string& value);

        /**
         * \name Set location
         * \brief Detects location related run-test calls and sets the device's location appropriately.
         *
         * Possible values:
         * - SET_LOCATION1
         * - SET_LOCATION2
         * - SET_LOCATION=<VALUE> with <VALUE> as a specific bed identifier to set
         *
         * @param value The set operation's requested value.
         */
        ///@{
        void setLocation(const std::string& value);
        void setLocationInvalid(const std::string& value);
        ///@}

        /**
         * invokes MDIB related run tests
         */
        void setMdib(const std::string& value);

        static void sendAbortSignal();

        void setCommunicationNodeInfo(const std::string& v);

        void setMetaData (const std::string& v);

        void setMdsType(const std::string& v);

        void initRTSA(const std::string& v);

        void modifyRTSA(const std::string& v);

        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_mdibAccess;
        std::shared_ptr<NumericMetricHandlerMock> m_numericMetricHandler;
        std::shared_ptr<ILocationHandler> m_locationHandler;
        std::shared_ptr<DeviceHandlerMock> m_deviceHandler;
        std::shared_ptr<Sdc::LocalDevice> m_device;
        std::string m_currentTest;
};

} /* namespace S31::Test */
