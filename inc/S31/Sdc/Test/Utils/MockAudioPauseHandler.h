#pragma once

#include <S31/Osf/Public/Client/GlobalAudioPauseClient.h>
#include <S31/Osf/Public/Device/GlobalAudioPauseDevice.h>
#include <S31/Osf/Public/Device/GlobalAudioPauseEnums.h>
#include <S31/Safety/Public/DualChannelComparator.h>
#include <S31/Safety/Public/DualChannelFactory.h>
#include <S31/Sdc/Public/Client/RemoteDevicesProvider.h>
#include <S31/Sdc/Public/Discovery/DiscoveryProvider.h>
#include <S31/Sdc/Test/Utils/MockAudioPauseDualChannel.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <S31/SetService/Public/Device/SynchronousDeviceTransaction.h>

#include <Framework/Log/Public/Log.h>

#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>

namespace S31
{
struct S31_CORE_IT_UTIL_EXPIMP AudioPauseServiceInfo
{
        AudioPauseServiceInfo();
        S31::Osf::AudioPauseStatus currentValue;
};

/*!
 * \brief Mock implementation of an audio-pause handler used by the unit test instance
 */
class MockAudioPauseHandler: public std::enable_shared_from_this<MockAudioPauseHandler>
{
    public:
        MockAudioPauseHandler(DFL::NotNull<std::shared_ptr<S31::SetService::InvocationCallbackRegistry>> invocationCallbackRegistry,
                              DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> mdibAccess,
                              const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevicesProvider>>& nodeProvider);
        virtual ~MockAudioPauseHandler();

        virtual void start();
        virtual void stop();

        void globalAudioPauseSetCallback(SetService::SynchronousDeviceTransaction& deviceTransaction, const DFL::Mdib::Handle& operationHandle);
        void globalAudioPauseCancelCallback(SetService::SynchronousDeviceTransaction& deviceTransaction, const DFL::Mdib::Handle& operationHandle);

    private:
        void updateAudioPauseInMdib(const S31::Osf::AudioPauseStatus& apStatus);
        template<class T_Entity, class T_ChildEntity>
        void checkAndUpdateSystemSignalActivations(const DFL::NotNull<std::shared_ptr<T_Entity>>& entity,
                                                   DFL::Mdib::MdibChangeSet& changeSet,
                                                   const S31::Osf::AudioPauseStatus& apStatus);

        bool isManifestationAudible(const DFL::Mdib::AlertSignalManifestation& manifestation);
        bool isActivationStateUpdatable(const DFL::Mdib::AlertActivation& activationState, const DFL::Mdib::AlertActivation& activationStateUpdate);
        mutable std::mutex m_mutex;
        mutable std::condition_variable m_condition;
        AudioPauseServiceInfo apInfo;
        DFL::NotNull<std::shared_ptr<S31::SetService::InvocationCallbackRegistry>> m_invocationCallbackRegistry;
        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_localMdibAccess;
        std::shared_ptr<S31::Osf::GlobalAudioPauseDevice> m_globalAudioPauseDevice;
        std::shared_ptr<S31::Osf::GlobalAudioPauseClient> m_globalAudioPauseClient;
        std::shared_ptr<S31::Sdc::RemoteDevicesSubject> m_communicationNodeSubject;
};

} /* namespace S31 */
