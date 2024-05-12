#pragma once

#include <S31/Sdc/Public/Client/RemoteDevicesProvider.h>

namespace S31::Osf
{
/**
 * @brief Client interface that is intended to send audio-pause activate requests to all connected devices.
 *
 * @details Listens to new devices and maintains a list of online/offline devices.
 * Any call to GlobalAudioPauseClient::activateRemoteAudioPause() invokes
 * an audio-pause activation at all connected, online remote devices.
 *
 *
 * @ingroup S31OsfClient
 */
class S31_CORE_EXPIMP GlobalAudioPauseClient
{
    public:
        /**
         * @brief Instantiates GlobalAudioPauseClient Object with the remote device provider
         * @param remoteDevicesProvider to register the remote devices observer
         *
         */
        explicit GlobalAudioPauseClient(Sdc::RemoteDevicesProvider& remoteDevicesProvider);
        /**
         * @brief Sends an activate request to all remote devices in internal remote devices map
         * @returns list of \ref S31::SetService::ClientTransaction - result of each invocation operation
         */
        std::vector<DFL::NotNull<std::shared_ptr<SetService::ClientTransaction>>> activateRemoteAudioPause();

        /**
         * @brief Sends a deactivate request to all remote devices in internal remote devices map
         * @returns list of \ref S31::SetService::ClientTransaction - result of each invocation operation
         */
        std::vector<DFL::NotNull<std::shared_ptr<SetService::ClientTransaction>>> deactivateRemoteAudioPause();

    private:
        class RemoteDevicesObserverImpl;
        std::shared_ptr<RemoteDevicesObserverImpl> m_remoteDevicesObserverImpl;
};

}
