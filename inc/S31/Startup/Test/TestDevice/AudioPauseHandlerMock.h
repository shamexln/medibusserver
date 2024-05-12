#pragma once

#include <S31/Osf/Public/Device/GlobalAudioPauseDevice.h>
#include <S31/Sdc/Public/Device/LocalMdibAccessSmartPtrTypes.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>

#include <memory>

namespace S31
{
namespace SetService
{
class DeviceTransaction;
}
namespace Test
{

/*!
 * \brief Mock implementation of an audio-pause handler used by the test device instance
 */
class AudioPauseHandlerMock
{
    public:
        AudioPauseHandlerMock(const DFL::NotNull<std::shared_ptr<S31::SetService::InvocationCallbackRegistry> >& invocationCallbackRegistry,
                              const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& mdibAccess);
        virtual ~AudioPauseHandlerMock();

        virtual void start();

        virtual void stop();

    private:
        std::shared_ptr<S31::Osf::GlobalAudioPauseDevice> m_globalAudioPauseDevice;
        DFL::NotNull<std::shared_ptr<S31::SetService::InvocationCallbackRegistry>> m_invocationCallbackRegistry;
        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_localMdibAccess;
};

}
}
