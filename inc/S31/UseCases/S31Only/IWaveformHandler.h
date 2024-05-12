#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/S31CoreExImp.h>

#include <memory>
#include <string>

namespace S31
{

/**
 * @brief Interface for the platform worker implementation on S31.x devices.
 *
 * \ingroup S31UseCases
 */
class S31_CORE_EXPIMP IWaveformHandler
{
    public:
        virtual ~IWaveformHandler() noexcept = default;

        /**
         * Starts the waveform handling.
         */
        virtual void start() = 0;

        /**
         * Stops the waveform handling.
         */
        virtual void stop() = 0;
};

} /* namespace S31 */
