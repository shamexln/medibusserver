#pragma once

#include <S31/S31CoreExImp.h>

#include <memory>

namespace DFL::Mdib
{
class LocationContextState;
}

namespace S31
{

/**
 * The ILocationHandler interface declares the feature set of the location
 * worker in the specific device implementation.
 *
 * \ingroup S31UseCases
 */
class S31_CORE_EXPIMP ILocationHandler
{
    public:
        virtual ~ILocationHandler() noexcept = default;

        /**
         * start the location handler.
         */
        virtual void start() = 0;

        /**
         * stops the location handler.
         */
        virtual void stop() = 0;

        /**
         * Set the location for the device.
         *
         * @param locationContextState the locationContextState to use for the device
         */
        virtual void setLocation(const DFL::Mdib::LocationContextState& locationContextState) = 0;

};

}
