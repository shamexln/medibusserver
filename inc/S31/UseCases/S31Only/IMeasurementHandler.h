#pragma once

#include <S31/S31CoreExImp.h>

namespace S31
{
/**
 * Interface to define common methods for access to measurements
 * specific subclasses in S31.X have to deal with native
 * platform specific implementations.
 *
 * \ingroup S31UseCases
 */
class S31_CORE_EXPIMP IMeasurementHandler
{
    public:
        virtual ~IMeasurementHandler() noexcept = default;

        /**
         * Starts the MeasurementHandler.
         */
        virtual void start() = 0;

        /**
         * Stops the MeasurementHandler.
         */
        virtual void stop() = 0;

};

} /* namespace S31 */
