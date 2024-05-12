#pragma once

#include <S31/UseCases/S31Only/IWaveformHandler.h>
#include <S31/UseCases/S31Only/utils/S31Service.h>

#include <memory>
#include <mutex>
#include <string>

namespace S31
{
namespace Sdc
{
class RemoteDevicesSubject;
}

/**
 * Main class for the waveform use case service.
 *
 * The waveform service initializes the system for incoming and outgoing
 * waveforms. It uses the mdib accessor for waveforms to receive and send
 * waveform updates.
 *
 * \ingroup S31UseCases
 */
class WaveformService: public S31Service
{
    public:
        explicit WaveformService(std::shared_ptr<IWaveformHandler> handler);

        void start() override;
        void stop() override;

        std::string getName() override;
    private:
        bool                                       m_isRunning{false};
        std::mutex                                 m_stateMutex;
        std::shared_ptr<IWaveformHandler>          m_waveformHandler;
};

}
