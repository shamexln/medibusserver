#pragma once

#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>

namespace S31::Osf
{
/**
 * @brief Function wrapper for the Global audio pause set and cancel callbacks.
 *
 * @ingroup S31OsfDevice
 */
using AudioPauseCallbackFunction = std::function<void(SetService::SynchronousDeviceTransaction&, const DFL::Mdib::Handle&)>;

/**
 * @brief Struct to hold the set and cancel audio pause callbacks
 *
 * @ingroup S31OsfDevice
 */
struct AudioPauseCallback
{
        AudioPauseCallbackFunction setGlobalAudioPause;
        AudioPauseCallbackFunction cancelGlobalAudioPause;
};

/**
 * @brief Device side interface that is responsible for registering callbacks for set and cancel audio-pause.
 *
 * @ingroup S31OsfDevice
 */
class S31_CORE_EXPIMP GlobalAudioPauseDevice
{
public:
        /**
         * @brief Instantiates GlobalAudioPauseDevice object with set and cancel callbacks, invocationCallbackRegistry and local mdib access.
         * @details initializes Mdib with audio pause specific data and registers the received set and cancel callbacks.
         *
         * @param audioPauseCallback struct \ref S31::Osf::AudioPauseCallback holds the callback functions for set and cancel operations
         * @param invocationCallbackRegistry to register the device side call back for the activate operation
         * @param mdibAccess local Mdib access
         */
        GlobalAudioPauseDevice(const AudioPauseCallback& audioPauseCallback,
                               const DFL::NotNull<std::shared_ptr<SetService::InvocationCallbackRegistry>>& invocationCallbackRegistry,
                               const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& mdibAccess);

        /**
         * @brief destructor unregisters the set and cancel callbacks and sets \ref DFL::Mdib::OperatingMode of Set and Cancel Audio Pause Activate Operations to Disabled
         */
        ~GlobalAudioPauseDevice() noexcept = default;

    private:
        class Impl;
        DFL::NotNull<std::shared_ptr<Impl>> m_impl;

};

}
