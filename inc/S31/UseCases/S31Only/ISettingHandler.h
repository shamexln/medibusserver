#pragma once

#include <S31/S31CoreExImp.h>

namespace S31
{
/**
 * Interface for the device specific settings handling.
 *
 * The S31.Core setting use case service uses this handler to trigger
 * the device specific processing of settings to allow reading.
 *
 * \ingroup S31UseCases
 */
class S31_CORE_EXPIMP ISettingHandler
{
    public:

        virtual ~ISettingHandler() noexcept = default;

        /**
          * Starts the settings handling.
          */
        virtual void start() = 0;

        /**
          * Stops the settings handling.
          */
        virtual void stop() = 0;

};

} /* namespace S31 */
