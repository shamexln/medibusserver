#pragma once

#include <S31/UseCases/S31Only/utils/S31Service.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>

namespace S31
{
namespace Sdc
{
class RemoteDevicesSubject;
}

class IMeasurementHandler;

/**
 * Main class for measurement functionality.
 *
 * Takes care of transmitting measurement data between network and local repository.
 *
 * \ingroup S31UseCases
 */
class MeasurementService: public S31Service
{
        DFL_NOT_COPYABLE(MeasurementService)
    public:
        explicit MeasurementService(DFL::NotNull<std::shared_ptr<IMeasurementHandler>> handler);
        ~MeasurementService() override;

        void start() override;
        void stop() override;

        std::string getName() override;

    private:
        bool running{false};

        DFL::NotNull<std::shared_ptr<IMeasurementHandler>> measurementHandler;

};

}
