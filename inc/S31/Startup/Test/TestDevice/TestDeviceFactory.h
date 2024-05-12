#pragma once

#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Test
{
class AudioPauseHandlerMock;
class ColorSchemeHandlerMock;
class WaveformProvider;

/**
 * Device Factory for tests (module tests)
 */
class TestDeviceFactory
{
    public:
        TestDeviceFactory();

        void setLocalMdibAccess(const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess);

        std::shared_ptr<S31::Test::ColorSchemeHandlerMock> provideColorSchemeHandler();
        std::shared_ptr<S31::Test::AudioPauseHandlerMock> provideAudioPauseHandler();

        void setInvocationCallbackRegistry(const std::shared_ptr<S31::SetService::InvocationCallbackRegistry>& invocationCallbackRegistry);

    private:
        DFL::Mdib::LocalMdibAccessSharedPtr m_localMdibAccess;
        std::shared_ptr<S31::Test::ColorSchemeHandlerMock> m_colorSchemeHandler;
        std::shared_ptr<S31::Test::AudioPauseHandlerMock> m_audioPauseHandler;
        std::shared_ptr<S31::SetService::InvocationCallbackRegistry> m_invocationCallbackRegistry;

};

}
