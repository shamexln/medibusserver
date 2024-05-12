#pragma once

#include <TestDevice/AudioPauseHandlerMock.h>

#include <S31/Sdc/S31Only/CommandLineOptions.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>
#include <S31/Startup/S31Only/IS31App.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31
{
class S31CoreFactory;

namespace Test
{
class TestDeviceFactory;
class RunTestControllerTestDevice;

class TestDevice
{
    public:
        TestDevice(int arc, const char* argv[], const CommandLineOptions& additionalOptions);
        ~TestDevice();

        void start();
        void stop();

        void waitForDie();

    protected:
        void addAdditionalOptions(const CommandLineOptions& additionalOptions);
        void createMdib();

    private:
        int m_deviceInstance = 0;
        CommandLineOptions m_options;
        std::shared_ptr<S31::Test::TestDeviceFactory> m_s31Factory;
        std::shared_ptr<S31CoreFactory> m_coreFactory;
        std::shared_ptr<S31::IS31App> m_app;
        std::shared_ptr<S31::Test::RunTestControllerTestDevice> m_testController;
        std::shared_ptr<SetService::InvocationCallbackRegistry> m_invocationCallbackRegistry;
        std::shared_ptr<S31::Test::AudioPauseHandlerMock> m_audioPauseHandler;
};

}
} /* namespace S31 */
